/*-----------------------------------------------------------------------
 * File: MDSEDITDOC.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// MdsEditDoc.h : interface of the CMdsEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDSEDITDOC_H__ED147A1F_6BBD_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_MDSEDITDOC_H__ED147A1F_6BBD_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CMDS.h>

class CMdsEditDoc : public CDocument
{
protected: // create from serialization only
	CMdsEditDoc();
	DECLARE_DYNCREATE(CMdsEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdsEditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strImportFile;
	CMDS *m_pMds;
	virtual ~CMdsEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMdsEditDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//	  DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDSEDITDOC_H__ED147A1F_6BBD_11D2_A091_00A0C90988EF__INCLUDED_)
