/*-----------------------------------------------------------------------
 * File: DIR.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// Dir.cpp: implementation of the CDir class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CMDS.h"
#include "Dir.h"
#include "AppMemTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDir::CDir(CMDS * pMds, LPCTSTR szDirName) :
	m_pMds( pMds),
	m_strDirName( szDirName )
{
	memset( &m_hDb, 0, sizeof(m_hDb) );
	OpenDirectory();
}

CDir::~CDir()
{
	CloseDirectory();
}

CSSM_RETURN CDir::OpenDirectory()
{
	ASSERTVALID();


	CSSM_DB_ACCESS_TYPE access =
		CSSM_DB_ACCESS_READ | CSSM_DB_ACCESS_WRITE;

	m_hDb.DLHandle = m_pMds->m_hMds;
	m_hDb.DBHandle = NULL;

	CSSM_RETURN ret =	m_pMds->DbOpen(
			m_strDirName,
			NULL,
			access,
			NULL,
			NULL,
			&m_hDb.DBHandle);

	return ret;
}

CSSM_RETURN CDir::CloseDirectory()
{
	ASSERTVALID();

	CSSM_RETURN crStatus = m_pMds->DbClose( m_hDb );

	if ( crStatus == CSSM_OK )
	{
		memset( &m_hDb, 0, sizeof(MDS_DB_HANDLE) );
	}

	return crStatus;
}

CSSM_RETURN CDir::Open(CMDS *pMds, LPCTSTR szDirName)
{
	ASSERTVALID();

	m_pMds = pMds;
	m_strDirName = szDirName;
	return OpenDirectory();
}

#ifdef _DEBUG
void CDir::AssertValid() const
{
	CObject::ASSERTVALID();
	ASSERT( m_pMds );
}
#endif
