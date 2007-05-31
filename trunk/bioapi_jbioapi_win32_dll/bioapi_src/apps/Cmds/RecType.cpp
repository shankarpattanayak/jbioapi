/*-----------------------------------------------------------------------
 * File: RECTYPE.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// RecType.cpp: implementation of the CRecType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dir.h"
#include "RecType.h"
#include "CMDS.h"
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

CRecType::CRecType(CDir *pDir, CSSM_DB_RECORDTYPE dwRecType, DWORD dwNumAttrs) :
	m_cbEndOfDataStore( CSSM_TRUE ),
	m_resultsHandle( 0 ),
	m_outputAttributeData( NULL ),
	m_pDir( pDir ),
	m_dwRecType( dwRecType ),
	m_dwNumAttrs( dwNumAttrs )
{
	memset( &m_cqQuery, 0, sizeof (CSSM_QUERY) );
}

CRecType::~CRecType()
{
	if ( m_pDir )
	{
		CMDS * pMds = m_pDir->m_pMds;

		if ( m_resultsHandle )
		{
			pMds->DataAbortQuery(
					m_pDir->m_hDb,
					m_resultsHandle);
			m_resultsHandle = 0;
		}
	}
}

CSSM_DB_UNIQUE_RECORD_PTR CRecType::FirstRecordId(CSSM_DB_RECORD_ATTRIBUTE_DATA & outputAttributes)
{
	ASSERTVALID();

	CMDS * pMds = m_pDir->m_pMds;

	if ( m_resultsHandle )
	{
		pMds->DataAbortQuery(
				m_pDir->m_hDb,
				m_resultsHandle);
		m_resultsHandle = 0;
	}


	CSSM_DB_UNIQUE_RECORD_PTR recordId = NULL;

	CSSM_RETURN ret =	pMds->DataGetFirst(
				m_pDir->m_hDb,
				&m_cqQuery,
				&m_resultsHandle,
				&outputAttributes,
				NULL,
				&recordId);

	if ((ret != CSSM_OK) &&
		(ret != CSSMERR_DL_ENDOFDATA))
	{
		//char buffer[128];
		//GetErrorMsgString(ret,buffer,sizeof(buffer));

		CString strMsg;
		strMsg.Format(
			_T("Error  occurred during DataGetFirst.  MDS may be corrupted"));

		AfxMessageBox( strMsg );


	}

	return recordId;
}

CSSM_DB_UNIQUE_RECORD_PTR CRecType::NextRecordId(CSSM_DB_RECORD_ATTRIBUTE_DATA & outputAttributes)
{
	ASSERTVALID();

	if ( m_resultsHandle == 0 )
	{
		return NULL;
	}

	CSSM_DB_UNIQUE_RECORD_PTR recordId = NULL;

	CMDS * pMds = m_pDir->m_pMds;

	CSSM_RETURN ret = pMds->DataGetNext(
				m_pDir->m_hDb,
				m_resultsHandle,
				&outputAttributes,
				NULL,
				&recordId);

	if ((ret != CSSM_OK) && (ret != CSSMERR_DL_ENDOFDATA))
	{
		//char buffer[128];
		//GetErrorMsgString(ret,buffer,sizeof(buffer));

		CString strMsg;
		strMsg.Format(
			_T("Error occurred during DataGetFirst.	 MDS may be corrupted"));

		AfxMessageBox( strMsg );

	}

	return recordId;
}

#ifdef _DEBUG
void CRecType::AssertValid() const
{
	CObject::ASSERTVALID();
	ASSERT( m_pDir );
	ASSERT( m_pDir->m_pMds );
	ASSERT( m_outputAttributeData );
}
#endif
