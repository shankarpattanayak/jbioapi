/*-----------------------------------------------------------------------
 * File: MODIFYUINT32DLG.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


#if !defined(AFX_MODIFYUINT32DLG_H__8E609417_6EE7_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_MODIFYUINT32DLG_H__8E609417_6EE7_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyUint32Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifyUint32Dlg dialog

class CModifyUint32Dlg : public CDialog
{
// Construction
public:
	CModifyUint32Dlg(CWnd* pParent = NULL);	  // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyUint32Dlg)
	enum { IDD = IDD_MODIFYUINT32 };
	CString m_strAttrValue;
	CString m_strAttrName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyUint32Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyUint32Dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYUINT32DLG_H__8E609417_6EE7_11D2_A091_00A0C90988EF__INCLUDED_)
