/*-----------------------------------------------------------------------
 * File: MODIFYSTRINGDLG.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


#if !defined(AFX_MODIFYSTRINGDLG_H__56EA802E_6E3E_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_MODIFYSTRINGDLG_H__56EA802E_6E3E_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyStringDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifyStringDlg dialog

class CModifyStringDlg : public CDialog
{
// Construction
public:
	CModifyStringDlg(CWnd* pParent = NULL);	  // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyStringDlg)
	enum { IDD = IDD_MODIFYSTRING };
	CEdit	m_editAttrValue;
	CButton m_checkBoxValueIsNULL;
	CString m_strAttrValue;
	CString m_strAttrName;
	BOOL	m_bValueIsNULL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyStringDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyStringDlg)
	afx_msg void OnCheckNull();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYSTRINGDLG_H__56EA802E_6E3E_11D2_A091_00A0C90988EF__INCLUDED_)
