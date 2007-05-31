/*-----------------------------------------------------------------------
 * File: MODIFYMULTIUINT32DLG.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// ModifyMultiUint32Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MdsEdit.h"
#include "ModifyMultiUint32Dlg.h"
#include "AppMemTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyMultiUint32Dlg dialog


CModifyMultiUint32Dlg::CModifyMultiUint32Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyMultiUint32Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyMultiUint32Dlg)
	m_strAttrName = _T("");
	m_strAttrValue0 = _T("");
	m_strAttrValue1 = _T("");
	m_strAttrValue2 = _T("");
	m_strAttrValue3 = _T("");
	m_strAttrValue4 = _T("");
	m_strAttrValue5 = _T("");
	m_strAttrValue6 = _T("");
	m_strAttrValue7 = _T("");
	m_strAttrValue8 = _T("");
	m_strAttrValue9 = _T("");
	//}}AFX_DATA_INIT
}


void CModifyMultiUint32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyMultiUint32Dlg)
	DDX_Text(pDX, IDC_EDIT_ATTRNAME, m_strAttrName);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE0, m_strAttrValue0);
	DDV_MaxChars(pDX, m_strAttrValue0, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE1, m_strAttrValue1);
	DDV_MaxChars(pDX, m_strAttrValue1, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE2, m_strAttrValue2);
	DDV_MaxChars(pDX, m_strAttrValue2, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE3, m_strAttrValue3);
	DDV_MaxChars(pDX, m_strAttrValue3, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE4, m_strAttrValue4);
	DDV_MaxChars(pDX, m_strAttrValue4, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE5, m_strAttrValue5);
	DDV_MaxChars(pDX, m_strAttrValue5, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE6, m_strAttrValue6);
	DDV_MaxChars(pDX, m_strAttrValue6, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE7, m_strAttrValue7);
	DDV_MaxChars(pDX, m_strAttrValue7, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE8, m_strAttrValue8);
	DDV_MaxChars(pDX, m_strAttrValue8, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE9, m_strAttrValue9);
	DDV_MaxChars(pDX, m_strAttrValue9, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyMultiUint32Dlg, CDialog)
	//{{AFX_MSG_MAP(CModifyMultiUint32Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyMultiUint32Dlg message handlers
