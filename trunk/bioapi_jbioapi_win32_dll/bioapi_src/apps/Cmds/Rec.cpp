/*-----------------------------------------------------------------------
 * File: REC.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// Rec.cpp: implementation of the CRec class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rec.h"
#include "Dir.h"
#include "CMDS.h"
#include <string.h>
#include "AppMemTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////

static const CSSM_DB_ATTRIBUTE_INFO * const s_pMdsAttrInfo[] =
{
	&s_MdsAttrInfo_ModuleId,
	&s_MdsAttrInfo_Manifest,
	&s_MdsAttrInfo_ModuleName,
	&s_MdsAttrInfo_Path,
	&s_MdsAttrInfo_Version,
	&s_MdsAttrInfo_Vendor,
	&s_MdsAttrInfo_Desc,
	&s_MdsAttrInfo_OID,	 //s_MdsAttrInfo_InterfaceGUID,
	&s_MdsAttrInfo_EmmVersion,
	&s_MdsAttrInfo_EmmVendor,
	&s_MdsAttrInfo_EmmType,
	&s_MdsAttrInfo_SSID,
	&s_MdsAttrInfo_ServiceType,
	&s_MdsAttrInfo_DynamicFlag,
//	&s_MdsAttrInfo_MultiThreadFlag,
	&s_MdsAttrInfo_ServiceMaskFlag,
	&s_MdsAttrInfo_ProductVersion,
	&s_MdsAttrInfo_ProductVendor,
	&s_MdsAttrInfo_CspType,
	&s_MdsAttrInfo_DlType,
	&s_MdsAttrInfo_CspFlags,
	&s_MdsAttrInfo_CspCustomFlags,
	&s_MdsAttrInfo_UseeTags,
	&s_MdsAttrInfo_UseeTag,
	&s_MdsAttrInfo_GroupId,
	&s_MdsAttrInfo_ContextType,
	&s_MdsAttrInfo_AlgType,
	&s_MdsAttrInfo_AttributeType,
	&s_MdsAttrInfo_AttributeValue,
	&s_MdsAttrInfo_Description,
	&s_MdsAttrInfo_ProductVendor,
	&s_MdsAttrInfo_ProductDesc,
	&s_MdsAttrInfo_ProductVersion,
	&s_MdsAttrInfo_ProductFlags,
	&s_MdsAttrInfo_CustomFlags,
	&s_MdsAttrInfo_StandardDesc,
	&s_MdsAttrInfo_StandardVersion,
	&s_MdsAttrInfo_QueryLimitsFlag,
	//&s_MdsAttrInfo_AuthMech,
	&s_MdsAttrInfo_ConjunctiveOps,
	&s_MdsAttrInfo_RelationalOps,
	&s_MdsAttrInfo_Protocol,
	&s_MdsAttrInfo_CertTypeFormat,
	&s_MdsAttrInfo_CrlTypeFormat,
//	&s_MdsAttrInfo_CertTemplate,
	&s_MdsAttrInfo_BundleTypeFormat,
	&s_MdsAttrInfo_XlationTypeFormat,
	&s_MdsAttrInfo_ProtocolDesc,
	&s_MdsAttrInfo_ProtocolFlags,
	&s_MdsAttrInfo_CertClassName,
	&s_MdsAttrInfo_RootCertificate,
	&s_MdsAttrInfo_RootCertTypeFormat,
	&s_MdsAttrInfo_OID,
	&s_MdsAttrInfo_Value,
	&s_MdsAttrInfo_ReaderDesc,
	&s_MdsAttrInfo_ReaderVendor,
	&s_MdsAttrInfo_ReaderVersion,
	&s_MdsAttrInfo_ReaderFirmwareVersion,
	&s_MdsAttrInfo_ReaderFlags,
	&s_MdsAttrInfo_ReaderCustomFlags,
	&s_MdsAttrInfo_ReaderSerialNumber,
	&s_MdsAttrInfo_SCDesc,
	&s_MdsAttrInfo_SCVendor,
	&s_MdsAttrInfo_SCVersion,
	&s_MdsAttrInfo_SCFirmwareVersion,
	&s_MdsAttrInfo_SCFlags,
	&s_MdsAttrInfo_SCCustomFlags,
	&s_MdsAttrInfo_SCSerialNumber,
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRec::CRec(CRecType * pRectType,
		   CSSM_DB_UNIQUE_RECORD_PTR recordId) :
	m_recordId( recordId ),
	m_pRecType( pRectType ),
	m_outputAttributeData( NULL )
{

}

CRec::~CRec()
{
	if ( m_recordId )
	{
		CDir *pDir = m_pRecType->m_pDir;
		CMDS *pMds = pDir->m_pMds;
		/*CSSM_RETURN crStatus = */
			pMds->FreeUniqueRecord( pDir->m_hDb, m_recordId );

		m_recordId = NULL;
	}
}

CString CRec::AttributeFormatString(int i) const
{
	ASSERTVALID();
	ASSERT(m_outputAttributeData[i].Info.AttributeFormat ==
		   CSSM_DB_ATTRIBUTE_FORMAT_STRING );

	if ( m_outputAttributeData[i].Value->Data == NULL )
	{
		return "<NULL>";
	}

	CString str;
	str.Format( "\"%s\"", m_outputAttributeData[i].Value->Data );
	return str;
}

CString CRec::AttributeFormatBlob(int i) const
{
	ASSERTVALID();
	ASSERT(m_outputAttributeData[i].Info.AttributeFormat ==
		   CSSM_DB_ATTRIBUTE_FORMAT_BLOB );

	if ( m_outputAttributeData[i].Value->Data == NULL )
	{
		return "<NULL>";
	}

	CString str;
	uint32 u32NumBytesToDisplay = 0;
	const uint32 u32MaxNumBytesToDisplay = 12;

	if ( s_bViewBlobAsString )
	{
		u32NumBytesToDisplay =
			__min(2*u32MaxNumBytesToDisplay, m_outputAttributeData[i].Value->Length);

		CString strTmp(
			(LPCTSTR) m_outputAttributeData[i].Value->Data,
			u32NumBytesToDisplay);

		str = strTmp + " ";
	}
	else
	{
		u32NumBytesToDisplay =
			__min(u32MaxNumBytesToDisplay, m_outputAttributeData[i].Value->Length);

		CString strTmp;

		for ( uint32 j = 0; j < u32NumBytesToDisplay; j++ )
		{
			uint8 u8Val = *((uint8 *) (m_outputAttributeData[i].Value->Data+j));
			strTmp.Format( "0x%.2X", u8Val );

			str += strTmp;
			str += " ";
		}
	}

	if ( m_outputAttributeData[i].Value->Length > u32NumBytesToDisplay )
	{
		str += "...";
	}

	return str;
}

CString CRec::AttributeFormatSint32(int i) const
{
	ASSERTVALID();
	ASSERT(m_outputAttributeData[i].Info.AttributeFormat ==
		   CSSM_DB_ATTRIBUTE_FORMAT_SINT32 );

	if ( m_outputAttributeData[i].Value->Data == NULL )
	{
		return "<NULL>";
	}

	CString str;
	sint32 s32Val = *((sint32 *) m_outputAttributeData[i].Value->Data);
	str.Format( "0x%.8X", s32Val );
	return str;
}


CString CRec::AttributeFormatUint32(int i) const
{
	ASSERTVALID();
	ASSERT(m_outputAttributeData[i].Info.AttributeFormat ==
		   CSSM_DB_ATTRIBUTE_FORMAT_UINT32 );

	if ( m_outputAttributeData[i].Value->Data == NULL )
	{
		return "<NULL>";
	}

	CString str;
	uint32 u32Val = *((uint32 *) m_outputAttributeData[i].Value->Data);
	str.Format( "0x%.8X", u32Val );
	return str;
}

CString CRec::AttributeFormatMultiUint32(int i) const
{
	ASSERTVALID();
	ASSERT(m_outputAttributeData[i].Info.AttributeFormat ==
		   CSSM_DB_ATTRIBUTE_FORMAT_MULTI_UINT32 );

	if ( m_outputAttributeData[i].Value->Data == NULL )
	{
		return "<NULL>";
	}

	CString str = "{ ";
	CString strTmp;
	for ( uint32 j = 0; j < m_outputAttributeData[i].Value->Length; j+=4 )
	{
		uint32 u32Val = *((uint32 *) (m_outputAttributeData[i].Value->Data+j));
		strTmp.Format( "0x%.8X", u32Val );

		str += strTmp;
		str += " ";
	}
	str += "}";

	return str;
}

CString CRec::operator [](int i) const
{
	ASSERTVALID();

	switch ( m_outputAttributeData[i].Info.AttributeFormat )
	{
	case CSSM_DB_ATTRIBUTE_FORMAT_STRING:
		return AttributeFormatString( i );
		break;

	case CSSM_DB_ATTRIBUTE_FORMAT_UINT32:
		return AttributeFormatUint32( i );
		break;

	case CSSM_DB_ATTRIBUTE_FORMAT_MULTI_UINT32:
		return AttributeFormatMultiUint32( i );
		break;

	case CSSM_DB_ATTRIBUTE_FORMAT_BLOB:
		return AttributeFormatBlob( i );
		break;

	case CSSM_DB_ATTRIBUTE_FORMAT_SINT32:
		return AttributeFormatSint32( i );
		break;


	default:
		return _T("Error: Unsupported attribute data" );
		break;
	} //switch
}

void CRec::Serialize( CArchive& archive )
{
	ASSERTVALID();
	// call base class function first
	// base class is CObject in this case
	CObject::Serialize( archive );

	// now do the stuff for our specific class
	if ( archive.IsStoring() )
	{
		archive.Write(
			&m_outputAttributes.DataRecordType,
			4);

		archive.Write(
			&m_outputAttributes.SemanticInformation,
			4);

		archive.Write(
			&m_outputAttributes.NumberOfAttributes,
			4);

		for ( uint32 i = 0; i < m_outputAttributes.NumberOfAttributes; i++ )
		{
			//store attribute name
			archive.Write(
				&m_outputAttributes.AttributeData[i].Info.AttributeNameFormat,
				4);
			ASSERT( m_outputAttributes.AttributeData[i].Info.AttributeNameFormat ==
					CSSM_DB_ATTRIBUTE_NAME_AS_STRING );

			//Need to fix this if you want to extend it to CSSM_DB_ATTRIBUTE_NAME_AS_OID
			//store attribute info
			//	store attribute info label
			DWORD dwAttrNameLength =
				strlen(m_outputAttributes.AttributeData[i].Info.Label.AttributeName) + 1;
			archive.Write(
				&dwAttrNameLength,
				4);
			archive.Write(
				m_outputAttributes.AttributeData[i].Info.Label.AttributeName,
				dwAttrNameLength);

			//store attribute value format
			archive.Write(
				&m_outputAttributes.AttributeData[i].Info.AttributeFormat,
				4);

			//store attribute value;
			archive.Write(
				&m_outputAttributes.AttributeData[i].Value->Length,
				4);
			if ( m_outputAttributes.AttributeData[i].Value->Length )
			{
				archive.Write(
					m_outputAttributes.AttributeData[i].Value->Data,
					m_outputAttributes.AttributeData[i].Value->Length);
			}
		}
	}
	else
	{
		archive.Read(
			&m_outputAttributes.DataRecordType,
			4);

		archive.Read(
			&m_outputAttributes.SemanticInformation,
			4);

		archive.Read(
			&m_outputAttributes.NumberOfAttributes,
			4);

		for ( uint32 i = 0; i < m_outputAttributes.NumberOfAttributes; i++ )
		{
			//retrieve attribute name
			//	retrieve attribute info label
			archive.Read(
				&m_outputAttributes.AttributeData[i].Info.AttributeNameFormat,
				4);
			ASSERT( m_outputAttributes.AttributeData[i].Info.AttributeNameFormat ==
					CSSM_DB_ATTRIBUTE_NAME_AS_STRING );

			//Need to fix this if you want to extend it to CSSM_DB_ATTRIBUTE_NAME_AS_OID
			DWORD dwAttrNameLength = 0;
			archive.Read(
				&dwAttrNameLength,
				4);

			ASSERT( dwAttrNameLength );

			//allocate memory for the attribute name
			m_outputAttributes.AttributeData[i].Info.Label.AttributeName =
				(char *) CMdsUtil_malloc( dwAttrNameLength, &CMdsUtil_AllocRef );
			if ( !m_outputAttributes.AttributeData[i].Info.Label.AttributeName )
			{
				AfxThrowMemoryException();
			}

			archive.Read(
				m_outputAttributes.AttributeData[i].Info.Label.AttributeName,
				dwAttrNameLength);

			//retrieve attribute value format
			archive.Read(
				&m_outputAttributes.AttributeData[i].Info.AttributeFormat,
				4);

			//retrieve attribute value;
			archive.Read(
				&m_outputAttributes.AttributeData[i].Value->Length,
				4);

			m_outputAttributes.AttributeData[i].Value->Data = NULL;
			if ( m_outputAttributes.AttributeData[i].Value->Length )
			{
				//allocate memory for the data
				m_outputAttributes.AttributeData[i].Value->Data =
					(uint8 *) CMdsUtil_malloc(
						m_outputAttributes.AttributeData[i].Value->Length,
						&CMdsUtil_AllocRef);
				if ( !m_outputAttributes.AttributeData[i].Value->Data )
				{
					AfxThrowMemoryException();
				}

				archive.Read(
					m_outputAttributes.AttributeData[i].Value->Data,
					m_outputAttributes.AttributeData[i].Value->Length);
			}

			//do some error checking and use static memory to represent name
			for ( int j = 0; j < sizeof(s_pMdsAttrInfo)/sizeof(CSSM_DB_ATTRIBUTE_INFO_PTR); j++ )
			{
				if (strcmp(
						s_pMdsAttrInfo[j]->Label.AttributeName,
						m_outputAttributes.AttributeData[i].Info.Label.AttributeName) == 0)
				{
					ASSERT(
						m_outputAttributes.AttributeData[i].Info.AttributeNameFormat ==
						s_pMdsAttrInfo[j]->AttributeNameFormat);

					ASSERT(
						m_outputAttributes.AttributeData[i].Info.AttributeFormat ==
						s_pMdsAttrInfo[j]->AttributeFormat);

					CMdsUtil_free(
						m_outputAttributes.AttributeData[i].Info.Label.AttributeName,
						&CMdsUtil_AllocRef);
					m_outputAttributes.AttributeData[i].Info = *s_pMdsAttrInfo[j];

					break;
				}
			}

			if ( j == sizeof(s_pMdsAttrInfo)/sizeof(CSSM_DB_ATTRIBUTE_INFO_PTR) )
			{
				AfxMessageBox( _T("Unsupported attribute name found in MDS file") );
			}
		}
	}
}

#ifdef _DEBUG
void CRec::AssertValid() const
{
	CObject::ASSERTVALID();
	ASSERT( m_pRecType );
	ASSERT( m_outputAttributeData );
}
#endif

//////////////////////////////////////////////////////////////////////
//Microsoft macro
IMPLEMENT_SERIAL( CRec, CObject, 1 )

//////////////////////////////////////////////////////////////////////
//Static Variable
BOOL CRec::s_bViewBlobAsString = FALSE;
