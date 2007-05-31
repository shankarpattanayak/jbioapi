/*-----------------------------------------------------------------------
 * File: MODIFYSTRINGDLG.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// ModifyStringDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MdsEdit.h"
#include "ModifyStringDlg.h"
#include "AppMemTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyStringDlg dialog


CModifyStringDlg::CModifyStringDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyStringDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyStringDlg)
	m_strAttrValue = _T("");
	m_strAttrName = _T("");
	m_bValueIsNULL = FALSE;
	//}}AFX_DATA_INIT
}


void CModifyStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyStringDlg)
	DDX_Control(pDX, IDC_EDIT_ATTRVALUE, m_editAttrValue);
	DDX_Control(pDX, IDC_CHECK_NULL, m_checkBoxValueIsNULL);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE, m_strAttrValue);
	DDX_Text(pDX, IDC_EDIT_ATTRNAME, m_strAttrName);
	DDX_Check(pDX, IDC_CHECK_NULL, m_bValueIsNULL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyStringDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyStringDlg)
	ON_BN_CLICKED(IDC_CHECK_NULL, OnCheckNull)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyStringDlg message handlers

void CModifyStringDlg::OnCheckNull()
{
	UINT uState = m_checkBoxValueIsNULL.GetState();
	switch ( uState & 0x0003 )
	{
	case 0: //unchecked
		m_editAttrValue.EnableWindow( TRUE );
		break;

	case 1: //checked
		m_editAttrValue.Clear();
		m_editAttrValue.EnableWindow( FALSE );
		break;

	default:
		TRACE("CModifyStringDlg::OnCheckNull:Unexpected Checkbox State\n");
		break;
	} //switch
}

BOOL CModifyStringDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editAttrValue.EnableWindow( m_bValueIsNULL == FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
