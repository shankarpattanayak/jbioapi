/*-----------------------------------------------------------------------
 * File: DIR.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// Dir.h: interface for the CDir class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIR_H__61118327_6C46_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_DIR_H__61118327_6C46_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRecType;

class CDir : public CObject
{
	friend class CMDS;
	friend class CRecType;

public:
	CString m_strDirName;
	CMDS * m_pMds;
	MDS_DB_HANDLE m_hDb;

	CSSM_RETURN Open( CMDS *pMds, LPCTSTR szDirName );
	CDir(CMDS * pMds, LPCTSTR szDirName);
	virtual ~CDir();

#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:
	CSSM_RETURN OpenDirectory();
	CSSM_RETURN CloseDirectory();
};

#endif // !defined(AFX_DIR_H__61118327_6C46_11D2_A091_00A0C90988EF__INCLUDED_)
