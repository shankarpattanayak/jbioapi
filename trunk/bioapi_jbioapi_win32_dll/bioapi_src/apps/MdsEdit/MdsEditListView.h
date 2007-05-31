/*-----------------------------------------------------------------------
 * File: MDSEDITLISTVIEW.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


#if !defined(AFX_MDSEDITLISTVIEW_H__ED147A2A_6BBD_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_MDSEDITLISTVIEW_H__ED147A2A_6BBD_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MdsEditListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMdsEditListView view

class CRec;
class CDir;
class CMDS;

class CMdsEditListView : public CListView
{
protected:
	CMdsEditListView();			  // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMdsEditListView)

// Attributes
public:

// Operations
public:
	CRec * m_pRec;
	enum { IDXB_STRING, IDXB_UINT32, IDXB_MULTI_UINT32, IDXB_BLOB, IDXB_ERROR };
	enum { IDXC_ATTRNAME, IDXC_ATTRVALUEDATA, IDXC_ATTRVALUELENGTH };
	int GetSelectedItemIndex() const;
	BOOL Populate( CRec *pRec );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdsEditListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);		// overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMdsEditListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	CSSM_RETURN ModifyMds( CSSM_DB_RECORDTYPE dwRecType, int i, CMDS *pMds, CDir *pDir );
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	CImageList m_ctlImage;
	//{{AFX_MSG(CMdsEditListView)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditModify();
	afx_msg void OnUpdateEditModify(CCmdUI* pCmdUI);
	afx_msg void OnEditExportBlob();
	afx_msg void OnUpdateEditExportBlob(CCmdUI* pCmdUI);
	afx_msg void OnEditImportBlob();
	afx_msg void OnUpdateEditImportBlob(CCmdUI* pCmdUI);
	afx_msg void OnHackModifyOrExport();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditFindNext();
	afx_msg void OnDestroy();
	afx_msg void OnViewBlobAsString();
	afx_msg void OnUpdateViewBlobAsString(CCmdUI* pCmdUI);
	afx_msg void OnEditDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDSEDITLISTVIEW_H__ED147A2A_6BBD_11D2_A091_00A0C90988EF__INCLUDED_)
