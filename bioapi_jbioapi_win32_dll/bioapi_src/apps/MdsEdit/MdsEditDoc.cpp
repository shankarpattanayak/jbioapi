/*-----------------------------------------------------------------------
 * File: MDSEDITDOC.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// MdsEditDoc.cpp : implementation of the CMdsEditDoc class
//

#include "stdafx.h"
#include "MdsEdit.h"

#include "MdsEditDoc.h"
#include "CMDS.h"
#include "MainFrm.h"
#include "MdsEditView.h"
#include "AppMemTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdsEditDoc

IMPLEMENT_DYNCREATE(CMdsEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CMdsEditDoc, CDocument)
	//{{AFX_MSG_MAP(CMdsEditDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//	  DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMdsEditDoc construction/destruction

CMdsEditDoc::CMdsEditDoc()
{
	// fixme, pass app guid here
	m_pMds = new CMDS(NULL);
}

CMdsEditDoc::~CMdsEditDoc()
{
	delete m_pMds;
}

BOOL CMdsEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMdsEditDoc serialization

void CMdsEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMdsEditDoc diagnostics

#ifdef _DEBUG
void CMdsEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMdsEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMdsEditDoc commands

BOOL CMdsEditDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CString str;
	str.Format(
		_T("Do You Really Want to Import the Content of %s into MDS?"),
		lpszPathName);

	if ( AfxMessageBox( str, MB_YESNO ) != IDYES )
	{
		return FALSE;
	}

	m_strImportFile = lpszPathName;

	return TRUE;
}
