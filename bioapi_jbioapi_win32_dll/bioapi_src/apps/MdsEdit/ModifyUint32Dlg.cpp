/*-----------------------------------------------------------------------
 * File: MODIFYUINT32DLG.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// ModifyUint32Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MdsEdit.h"
#include "ModifyUint32Dlg.h"
#include "AppMemTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyUint32Dlg dialog


CModifyUint32Dlg::CModifyUint32Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyUint32Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyUint32Dlg)
	m_strAttrValue = _T("");
	m_strAttrName = _T("");
	//}}AFX_DATA_INIT
}


void CModifyUint32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyUint32Dlg)
	DDX_Text(pDX, IDC_EDIT_ATTRVALUE, m_strAttrValue);
	DDV_MaxChars(pDX, m_strAttrValue, 8);
	DDX_Text(pDX, IDC_EDIT_ATTRNAME, m_strAttrName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyUint32Dlg, CDialog)
	//{{AFX_MSG_MAP(CModifyUint32Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyUint32Dlg message handlers
