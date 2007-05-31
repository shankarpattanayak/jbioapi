/*-----------------------------------------------------------------------
 * File: FINDDLG.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// FindDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MdsEdit.h"
#include "FindDlg.h"
#include "AppMemTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindDlg dialog


CFindDlg::CFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDlg)
	m_strFind = _T("");
	m_bExamineAttrValue = FALSE;
	m_bExamineAttrName = FALSE;
	m_bMatchCase = FALSE;
	m_bMatchWholeStringOnly = FALSE;
	//}}AFX_DATA_INIT
}


void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDlg)
	DDX_Control(pDX, IDC_ATTRVALUE, m_cbExamineAttrValue);
	DDX_Control(pDX, IDC_ATTRNAME, m_cbExamineAttrName);
	DDX_Control(pDX, IDC_EDIT_FIND, m_editFind);
	DDX_Control(pDX, IDOK, m_buttonFind);
	DDX_Text(pDX, IDC_EDIT_FIND, m_strFind);
	DDX_Check(pDX, IDC_ATTRVALUE, m_bExamineAttrValue);
	DDX_Check(pDX, IDC_ATTRNAME, m_bExamineAttrName);
	DDX_Check(pDX, IDC_MATCHCASE, m_bMatchCase);
	DDX_Check(pDX, IDC_MATCHWHOLESTRINGONLY, m_bMatchWholeStringOnly);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDlg)
	ON_EN_CHANGE(IDC_EDIT_FIND, OnChangeEditFind)
	ON_BN_CLICKED(IDC_ATTRNAME, OnAttrName)
	ON_BN_CLICKED(IDC_ATTRVALUE, OnAttrValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindDlg message handlers

void CFindDlg::OnChangeEditFind()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	EnableOrDisableFindButton();
}

void CFindDlg::EnableOrDisableFindButton()
{
	TCHAR szBuffer[256];
	m_editFind.GetLine( 0, szBuffer, 256 );
	CString strLine = szBuffer;

	UINT uStateAttrName	 = m_cbExamineAttrName.GetState();
	UINT uStateAttrValue = m_cbExamineAttrValue.GetState();
	BOOL bDisable =
		(((uStateAttrName  & 0x0003) == 0) &&	//uncheck
		 ((uStateAttrValue & 0x0003) == 0)) ||	//uncheck
		(strLine == "");

	m_buttonFind.EnableWindow( !bDisable );
}

BOOL CFindDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	EnableOrDisableFindButton();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindDlg::OnAttrName()
{
	EnableOrDisableFindButton();
}

void CFindDlg::OnAttrValue()
{
	EnableOrDisableFindButton();
}
