/*-----------------------------------------------------------------------
 * File: MODIFYMULTIUINT32DLG.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


#if !defined(AFX_MODIFYMULTIUINT32DLG_H__8E60941B_6EE7_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_MODIFYMULTIUINT32DLG_H__8E60941B_6EE7_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyMultiUint32Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifyMultiUint32Dlg dialog

class CModifyMultiUint32Dlg : public CDialog
{
// Construction
public:
	CModifyMultiUint32Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyMultiUint32Dlg)
	enum { IDD = IDD_MODIFYMULTIUINT32 };
	CString m_strAttrName;
	CString m_strAttrValue0;
	CString m_strAttrValue1;
	CString m_strAttrValue2;
	CString m_strAttrValue3;
	CString m_strAttrValue4;
	CString m_strAttrValue5;
	CString m_strAttrValue6;
	CString m_strAttrValue7;
	CString m_strAttrValue8;
	CString m_strAttrValue9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyMultiUint32Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyMultiUint32Dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYMULTIUINT32DLG_H__8E60941B_6EE7_11D2_A091_00A0C90988EF__INCLUDED_)
