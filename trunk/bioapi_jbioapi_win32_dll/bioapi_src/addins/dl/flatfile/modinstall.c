/*-----------------------------------------------------------------------
 * File: MOD_INSTALL.C
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#include <sys/types.h>
#include <sys/stat.h>

//#include "geninc.h"
#include "cssm.h"
#include "cssmerr.h"
#include "cssmport.h"
#include "cssmlock.h"
#include "maf_config.h"
#include "maf_collectn.h"
#include "maf_util.h"
#include "mds.h"
#include "mds_schema.h"
#include "mds_util.h"
//#include "mds_util_type.h"
#include "intel/installdefs.h"

/* Number of MDS update operations that will be remembered by mds_util for
 * error clean-up during installation.
 */
#define DL_MDS_COMMIT_SIZE	150

static CSSM_RETURN __CleanMDS( MDSU_CONTEXT *pContext )
{
	CSSM_RETURN rv = CSSM_OK;
	MDSU_CDSA_COMMON_SCHEMA CommonTemplate;
	MDSU_CDSA_COMMON_SCHEMA CommonData;
	MDSU_CDSA_DL_PRIMARY_SCHEMA DLPrimaryTemplate;
	MDSU_CDSA_DL_PRIMARY_SCHEMA DLPrimaryData;
	MDSU_CDSA_DL_ENC_PRODUCT_SCHEMA DLEncProdTemplate;
	MDSU_CDSA_DL_ENC_PRODUCT_SCHEMA DLEncProdData;

	/* Execute a search on every DL record type to get a handle of all
	 * records and then delete them.
	 */
	/* Common Schema */
	CommonTemplate.ModuleID = MODULE_GUID;
	rv = MDSU_FindFirst( pContext,
						 &IfiMdsuCdsadirCommonSchema,
						 &CommonTemplate,
						 MDSU_COM_MODULE_ID,
						 &CommonData,
						 NULL );
	while ( rv == CSSM_OK )
	{
		if ( CommonData.Manifest.Data )
		{
			MDSU_free( pContext, CommonData.Manifest.Data );
		}

		rv = MDSU_FindNext( pContext,
							&CommonData,
							NULL );
	}
	if ( rv == CSSMERR_DL_ENDOFDATA )
	{
		/* DL Primary Schema */
		DLPrimaryTemplate.ModuleID = MODULE_GUID;
		rv = MDSU_FindFirst( pContext,
							 &IfiMdsuCdsadirDLPrimarySchema,
							 &DLPrimaryTemplate,
							 MDSU_DLP_MODULE_ID,
							 &DLPrimaryData,
							 NULL );
		while ( rv == CSSM_OK )
		{
			if ( DLPrimaryData.Manifest.Data )
			{
				MDSU_free( pContext, DLPrimaryData.Manifest.Data );
			}

			rv = MDSU_FindNext( pContext,
								&DLPrimaryData,
								NULL );
		}
		if ( rv == CSSMERR_DL_ENDOFDATA )
		{
			/* DL Encapsulated Product Schema */
			DLEncProdTemplate.ModuleID = MODULE_GUID;
			rv = MDSU_FindFirst( pContext,
								 &IfiMdsuCdsadirDLEncProductSchema,
								 &DLEncProdTemplate,
								 MDSU_DLEP_MODULE_ID,
								 &DLEncProdData,
								 NULL );
			while ( rv == CSSM_OK )
			{
				rv = MDSU_FindNext( pContext,
									&DLEncProdData,
									NULL );
			}
			if ( rv == CSSMERR_DL_ENDOFDATA )
			{
				/* Flush everything from the MDS */
				rv = MDSU_Revert( pContext );
			} /* CSP Encapsulated Product removed */
		} /* CSP Primary removed */
	} /* Common removed */

	/* Make sure nothing gets removed if there is an error */
	if ( ( rv != CSSMERR_DL_ENDOFDATA ) &&
		 ( rv != CSSM_OK ) )
	{
		MDSU_Commit( pContext );
	}

	return rv;
}

BioAPI_RETURN BioAPI INSTALL_ENTRY_NAME(
						const char *szModuleName,
						const char *szSearchPath,
						BioAPI_DATA *pCredential,
						INSTALL_ACTION Action,
						BioAPI_INSTALL_ERROR *pError )
{
	BioAPI_RETURN rv = BioAPI_OK;
	MDSU_CONTEXT MDSUContext;
	MDSU_CDSA_COMMON_SCHEMA Common;
	MDSU_CDSA_DL_PRIMARY_SCHEMA DLPrimary;
	MDSU_CDSA_DL_ENC_PRODUCT_SCHEMA DLEncProduct;


	/* Initialize the MDS update */
	if ( ( rv = MDSU_Init( &MDSUContext,
						   &Addin_APIMemFuncs,
						   &MODULE_GUID,
						   MDS_CDSA_DIRECTORY,
						   ( CSSM_DB_ACCESS_READ |
							 CSSM_DB_ACCESS_WRITE ),
						   DL_MDS_COMMIT_SIZE ) ) != CSSM_OK )
	{
		sprintf( pError->ErrorString, "MDS Error (Init): %X\n", rv );
		pError->ErrorCode = rv;
		return rv;
	}

	/* Place code to remove existing entries here */
	if ( ( rv = __CleanMDS( &MDSUContext ) ) != CSSM_OK )
	{
		sprintf( pError->ErrorString, "MDS Error (Clean): %X\n", rv );
		pError->ErrorCode = rv;
		MDSU_Term( &MDSUContext );
		return rv;
	}
	if ( Action == INSTALL_ACTION_UNINSTALL )
	{
		MDSU_Term( &MDSUContext );
		return rv;
	}

	/* Fill in the "easy" common schema structure */
	memcpy( &Common.ModuleID, &MODULE_GUID, sizeof(MODULE_GUID) );
	Common.Manifest = *pCredential;
	strcpy( Common.ModuleName, szModuleName );
	strcpy( Common.Path, szSearchPath );
	Common.CDSAVersion.Major = CSSM_MAJOR;
	Common.CDSAVersion.Minor = CSSM_MINOR;
	strcpy( Common.Desc, ADDIN_NAME );
	Common.DynamicFlag = CSSM_FALSE;
	Common.MultiThreadFlag = CSSM_FALSE;
	Common.ServiceMask = CSSM_SERVICE_DL;

	/* Insert the common schema record into the MDS */
	rv = MDSU_UpdateSchema( &MDSUContext,
							&IfiMdsuCdsadirCommonSchema,
							&Common,
							NULL );
	if ( rv != CSSM_OK )
	{
		sprintf( pError->ErrorString, "MDS Error (common-DL): %X\n", rv );
		pError->ErrorCode = rv;
		MDSU_Term( &MDSUContext );
		return rv;
	}

	/* Fill in the DL primary schema data */
	memcpy( &DLPrimary.ModuleID, &MODULE_GUID, sizeof(MODULE_GUID) );
	DLPrimary.SSID = ADDIN_DL_SUBSERVICE_ID;
	DLPrimary.Manifest.Data = NULL;
	DLPrimary.Manifest.Length = 0;
	strcpy( DLPrimary.ModuleName, szModuleName );
	DLPrimary.ProductVersion.Major = INTEL_FF_DSM_MAJOR_VER;
	DLPrimary.ProductVersion.Minor = INTEL_FF_DSM_MINOR_VER;
	strcpy( DLPrimary.Vendor, ADDIN_VENDOR_NAME );
	DLPrimary.DLType = CSSM_DL_FFS;
	DLPrimary.QueryLimitsFlag = CSSM_TRUE;
	memset(DLPrimary.SampleTypes, 0,
				sizeof(CSSM_SAMPLE_TYPE)*MDSU_MAX_VALUE_COUNT);
	DLPrimary.NumSampleTypes = 0;
	memset(DLPrimary.AclSubjectTypes, 0,
				  sizeof(CSSM_ACL_SUBJECT_TYPE)*MDSU_MAX_VALUE_COUNT);
	DLPrimary.NumAclSubjectTypes = 0;
	memset(DLPrimary.AclAuthTags, 0,
				sizeof(CSSM_ACL_AUTHORIZATION_TAG)*MDSU_MAX_VALUE_COUNT);
	DLPrimary.NumAclAuthTags = 0;
	DLPrimary.ConjunctiveOps[0] = CSSM_DB_NONE;
	DLPrimary.ConjunctiveOps[1] = CSSM_DB_AND;
	DLPrimary.ConjunctiveOps[2] = CSSM_DB_OR;
	DLPrimary.NumConjunctiveOps = 3;
	DLPrimary.RelationalOps[0] = CSSM_DB_EQUAL;
	DLPrimary.RelationalOps[1] = CSSM_DB_NOT_EQUAL;
	DLPrimary.NumRelationalOps = 2;

	/* Write the data to MDS */
	rv = MDSU_UpdateSchema( &MDSUContext,
							&IfiMdsuCdsadirDLPrimarySchema,
							&DLPrimary,
							NULL );
	if ( rv != CSSM_OK )
	{
		sprintf( pError->ErrorString, "MDS Error (DL Primary): %X\n", rv );
		pError->ErrorCode = rv;
		MDSU_Revert( &MDSUContext );
		MDSU_Term( &MDSUContext );
		return rv;
	}

	/* Fill in the DL encapsulated product schema data */
	memcpy( &DLEncProduct.ModuleID, &MODULE_GUID, sizeof(MODULE_GUID) );
	DLEncProduct.SSID = ADDIN_DL_SUBSERVICE_ID;
	strcpy( DLEncProduct.ProductDesc, "Intel FlatFile DL" );
	DLEncProduct.ProductVersion.Major = ADDIN_PRODUCT_VERSION_MAJOR;
	DLEncProduct.ProductVersion.Minor = ADDIN_PRODUCT_VERSION_MINOR;
	strcpy( DLEncProduct.ProductVendor, ADDIN_VENDOR_NAME );
	DLEncProduct.ProductFlags = 0;
	strcpy( DLEncProduct.StandardDesc, "Flatfile" );
	DLEncProduct.StandardVersion.Major = 0;
	DLEncProduct.StandardVersion.Minor = 0;
	DLEncProduct.Protocol = CSSM_NET_PROTO_NONE;
	DLEncProduct.RetrievalMode = 0;

	/* Write the data to MDS */
	rv = MDSU_UpdateSchema( &MDSUContext,
							&IfiMdsuCdsadirDLEncProductSchema,
							&DLEncProduct,
							NULL );
	if ( rv != CSSM_OK )
	{
		sprintf( pError->ErrorString, "MDS Error (DL Enc): %X\n", rv );
		pError->ErrorCode = rv;
		MDSU_Revert( &MDSUContext );
		MDSU_Term( &MDSUContext );
		return rv;
	}

	/* Commit the records */
	MDSU_Commit( &MDSUContext );

	/* Shut down the MDS connection */
	MDSU_Term( &MDSUContext );

	return BioAPI_OK;
}
