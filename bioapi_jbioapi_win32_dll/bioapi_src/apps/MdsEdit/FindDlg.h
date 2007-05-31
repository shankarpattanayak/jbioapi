/*-----------------------------------------------------------------------
 * File: FINDDLG.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


#if !defined(AFX_FINDDLG_H__275FA976_7042_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_FINDDLG_H__275FA976_7042_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindDlg dialog

class CFindDlg : public CDialog
{
// Construction
public:
	CFindDlg(CWnd* pParent = NULL);	  // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindDlg)
	enum { IDD = IDD_FIND };
	CButton m_cbExamineAttrValue;
	CButton m_cbExamineAttrName;
	CEdit	m_editFind;
	CButton m_buttonFind;
	CString m_strFind;
	BOOL	m_bExamineAttrValue;
	BOOL	m_bExamineAttrName;
	BOOL	m_bMatchCase;
	BOOL	m_bMatchWholeStringOnly;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableOrDisableFindButton();

	// Generated message map functions
	//{{AFX_MSG(CFindDlg)
	afx_msg void OnChangeEditFind();
	virtual BOOL OnInitDialog();
	afx_msg void OnAttrName();
	afx_msg void OnAttrValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDDLG_H__275FA976_7042_11D2_A091_00A0C90988EF__INCLUDED_)
