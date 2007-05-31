/*-----------------------------------------------------------------------
 * File: CMDS.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// CMDS.cpp: implementation of the CMDS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CMDS.h"
#include "Dir.h"
#include "AppMemTrack.h"
//#include "errMsgString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMDS::CMDS(const CSSM_GUID *pCallerGuid)
{
	m_memoryFunctions.malloc_func  = CMdsUtil_malloc;
	m_memoryFunctions.free_func	   = CMdsUtil_free;
	m_memoryFunctions.realloc_func = CMdsUtil_realloc;
	m_memoryFunctions.calloc_func  = CMdsUtil_calloc;
	m_memoryFunctions.AllocRef	   = &CMdsUtil_AllocRef;

/*	m_errorFuncs.SetError	= CMdsUtil_SetError;
	m_errorFuncs.GetError	= CMdsUtil_GetError;
	m_errorFuncs.ClearError = CMdsUtil_ClearError;
*/
	BOOL bStatus = MDS_Initialize(pCallerGuid);
	if ( bStatus == FALSE )
	{
		throw( "MDS_Initialize() failed" );
	}
}

CMDS::~CMDS()
{
	MDS_Terminate( );
	memset( &m_dlFunctions, 0, sizeof(MDS_FUNCS) );
}

//////////////////////////////////////////////////////////////////////
//Wrappers Around MDS_FUNCS Function Pointers
//////////////////////////////////////////////////////////////////////
CSSM_RETURN CMDS::DbOpen(const char *DbName,
						const CSSM_NET_ADDRESS *DbLocation,
						CSSM_DB_ACCESS_TYPE AccessRequest,
						const CSSM_ACCESS_CREDENTIALS *AccessCred,
						const void *OpenParameters,
						CSSM_DB_HANDLE *hMds)
/*
CSSM_DB_HANDLE CMDS::DbOpen(const char *DbName,
									const CSSM_NET_ADDRESS *DbLocation,
									const CSSM_DB_ACCESS_TYPE *AccessRequest,
									const CSSM_USER_AUTHENTICATION *UserAuthentication,
									const void *OpenParameters)
*/
{
	ASSERTVALID();

	return m_dlFunctions.DbOpen(
				m_hMds,
				DbName,
				DbLocation,
				AccessRequest,
				AccessCred,
				OpenParameters,
				hMds);
}

CSSM_RETURN CMDS::DbClose(MDS_DB_HANDLE MdsDbHandle)
{
	ASSERTVALID();

	return m_dlFunctions.DbClose( MdsDbHandle );
}

CSSM_RETURN CMDS::GetDbNames(CSSM_NAME_LIST_PTR *pNameList)
{
	ASSERTVALID();

	return m_dlFunctions.GetDbNames( m_hMds, pNameList );
}

CSSM_RETURN CMDS::GetDbNameFromHandle(MDS_DB_HANDLE MdsHandle, char** dbName)
{
	ASSERTVALID();

	return m_dlFunctions.GetDbNameFromHandle( MdsHandle,dbName);
}

CSSM_RETURN CMDS::FreeNameList(CSSM_NAME_LIST_PTR NameList)
{
	ASSERTVALID();

	return m_dlFunctions.FreeNameList( m_hMds, NameList );
}

CSSM_RETURN CMDS::DataInsert(MDS_DB_HANDLE MdsDbHandle,
												   CSSM_DB_RECORDTYPE RecordType,
												   const CSSM_DB_RECORD_ATTRIBUTE_DATA *Attributes,
												   const CSSM_DATA *Data,
												   CSSM_DB_UNIQUE_RECORD_PTR *UniqueId)
{
	ASSERTVALID();

	return m_dlFunctions.DataInsert(
				MdsDbHandle,
				RecordType,
				Attributes,
				Data,
				UniqueId);
}

CSSM_RETURN CMDS::DataDelete(MDS_DB_HANDLE MdsDbHandle,
							 const CSSM_DB_UNIQUE_RECORD *UniqueRecordIdentifier)
{
	ASSERTVALID();

	return m_dlFunctions.DataDelete( MdsDbHandle, UniqueRecordIdentifier );
}

CSSM_RETURN CMDS::DataModify(MDS_DB_HANDLE MdsDbHandle,
							 CSSM_DB_RECORDTYPE RecordType,
							 CSSM_DB_UNIQUE_RECORD_PTR	UniqueRecordIdentifier,
							 const CSSM_DB_RECORD_ATTRIBUTE_DATA *AttributesToBeModified,
							 const CSSM_DATA *DataToBeModified,
							 const CSSM_DB_MODIFY_MODE ModifyMode)
{
	ASSERTVALID();

	return m_dlFunctions.DataModify(
							MdsDbHandle,
							RecordType,
							UniqueRecordIdentifier,
							AttributesToBeModified,
							DataToBeModified,
							ModifyMode);
}

CSSM_RETURN CMDS::DataGetFirst(MDS_DB_HANDLE MdsDbHandle,
											 const CSSM_QUERY *Query,
											 CSSM_HANDLE_PTR  ResultsHandle,
											 CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
											 CSSM_DATA_PTR	Data,
											 CSSM_DB_UNIQUE_RECORD_PTR *UniqueID)
{
	ASSERTVALID();

	return m_dlFunctions.DataGetFirst(
				MdsDbHandle,
				Query,
				ResultsHandle,
				Attributes,
				Data,
				UniqueID);
}

CSSM_RETURN CMDS::DataGetNext(MDS_DB_HANDLE MdsDbHandle,
													CSSM_HANDLE ResultsHandle,
													CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
													CSSM_DATA_PTR Data,
											 CSSM_DB_UNIQUE_RECORD_PTR *UniqueID)
{
	ASSERTVALID();

	return m_dlFunctions.DataGetNext(
				MdsDbHandle,
				ResultsHandle,
				Attributes,
				Data,
				UniqueID);
}

CSSM_RETURN CMDS::DataAbortQuery(MDS_DB_HANDLE MdsDbHandle,
								 CSSM_HANDLE ResultsHandle)
{
	ASSERTVALID();

	return m_dlFunctions.DataAbortQuery( MdsDbHandle, ResultsHandle );
}

CSSM_RETURN CMDS::DataGetFromUniqueRecordId(MDS_DB_HANDLE MdsDbHandle,
											CSSM_DB_UNIQUE_RECORD_PTR UniqueRecord,
											CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
											CSSM_DATA_PTR  Data)
{
	ASSERTVALID();

	return m_dlFunctions.DataGetFromUniqueRecordId(
				MdsDbHandle,
				UniqueRecord,
				Attributes,
				Data);
}

CSSM_RETURN CMDS::FreeUniqueRecord(MDS_DB_HANDLE MdsDbHandle,
								   CSSM_DB_UNIQUE_RECORD_PTR UniqueRecord)
{
	ASSERTVALID();

	return m_dlFunctions.FreeUniqueRecord(
				MdsDbHandle,
				UniqueRecord);
}

CSSM_RETURN CMDS::MDS_Terminate()
{
	if ( !m_hMds )
	{
		return CSSM_OK;
	}

	return ::MDS_Terminate( m_hMds );
}

CSSM_RETURN CMDS::MDS_Initialize(const CSSM_GUID *pCallerGuid)
{
	 CSSM_RETURN ret =
		::MDS_Initialize(
			(BioAPI_UUID*)pCallerGuid,
			NULL, // manifest
			(BioAPI_MEMORY_FUNCS*)&m_memoryFunctions,
			&m_dlFunctions,
			&m_hMds);

	if (( m_hMds == 0 ) || (ret != CSSM_OK))
	{
		//REPORT_ERROR(ret,"initializing MDS");
		return FALSE;
	}

	return TRUE;
}

#ifdef _DEBUG
void CMDS::AssertValid() const
{
	CObject::ASSERTVALID();
	ASSERT( m_hMds );
}
#endif
