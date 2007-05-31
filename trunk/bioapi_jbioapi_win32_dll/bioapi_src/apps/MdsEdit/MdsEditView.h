/*-----------------------------------------------------------------------
 * File: MDSEDITVIEW.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// MdsEditView.h : interface of the CMdsEditTreeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDSEDITVIEW_H__ED147A21_6BBD_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_MDSEDITVIEW_H__ED147A21_6BBD_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRec;
class CMdsEditDoc;
class CRecType;
class CMDS;

class CMdsEditTreeView : public CTreeView
{
public:
	class CState : public CObject
	{
	public:
		CState() :
			m_iSiblingRanking( -1 ),
			m_iListItemSelected( 0 )
		{}

		CString m_strParentOfItemSelected;
		CString m_strItemSelected;
		int m_iSiblingRanking;
		int m_iListItemSelected;
		CMapStringToPtr m_mapItemWasExpanded;
	} m_state;

	class CFind : public CObject
	{
	public:
		CFind() :
			m_bExamineAttrValue( TRUE ),
			m_bExamineAttrName( TRUE ),
			m_bMatchCase( TRUE ),
			m_bMatchWholeStringOnly( TRUE )
		{}

		CString m_strFind;
		BOOL	m_bExamineAttrValue;
		BOOL	m_bExamineAttrName;
		BOOL	m_bMatchCase;
		BOOL	m_bMatchWholeStringOnly;
	} m_find;

protected:
	enum { IID_MYCOMPUTER, IID_CLOSEDFOLDER, IID_OPENEDFOLDER };

protected: // create from serialization only
	CMdsEditTreeView();
	DECLARE_DYNCREATE(CMdsEditTreeView)

// Attributes
public:
	CMdsEditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdsEditTreeView)
	public:
	virtual void OnDraw(CDC* pDC);	// overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL ImportMdsFile( LPCTSTR lpszPathName = NULL );
	CSSM_RETURN DeleteRecordFromMds( HTREEITEM hTreeItemRec );

	HTREEITEM m_hTreeItemNextSearchPos;
	HTREEITEM FindNext( HTREEITEM hTreeItem );
	HTREEITEM FindFirst();
	CString BuildRecordPath( HTREEITEM hTreeItem ) const;
	BOOL UpdateSelectedRecordLabel( LPCTSTR szLabel );
	BOOL Refresh();
	HTREEITEM AddRecord( CRec *pRec, HTREEITEM hTreeItemRecType );
	BOOL IsRecord( HTREEITEM hTreeItem ) const;
	BOOL IsRecordType(HTREEITEM hTreeItem) const;
	BOOL IsDirectory( HTREEITEM hTreeItem ) const;
	BOOL IsMdsRoot( HTREEITEM hTreeItem ) const;
	HTREEITEM AddRecordType( CRecType *pRecType, HTREEITEM hTreeItemDir );
	HTREEITEM AddDirectory( CMDS *pMds, LPCTSTR szDirName, HTREEITEM hTreeItemParent );
	virtual ~CMdsEditTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void StoreExpansionProperties( HTREEITEM hTreeItemRoot );
	void RestoreExpansionProperties( HTREEITEM hTreeItemRoot );
	HTREEITEM FindItem( const CString & szLabel, HTREEITEM hTreeItemSearchRoot ) const;
	BOOL StoreState();
	BOOL RestoreState();
	HTREEITEM FindDirectoryItem( HTREEITEM hTreeItemMdsRoot, CString & strDirName ) const;
	HTREEITEM FindRecordTypeItem( HTREEITEM hTreeItemDir, CSSM_DB_RECORDTYPE dwRecType ) const;
	BOOL ImportRecord( CArchive & archive );

	void ExportMdsRoot( CArchive & archive, HTREEITEM hTreeItemMdsRoot ) const;
	void ExportDirectory( CArchive & archive, HTREEITEM hTreeItemDir ) const;
	void ExportRecordType( CArchive & archive, HTREEITEM hTreeItemRecType ) const;
	void ExportRecord( CArchive & archive, HTREEITEM hTreeItemRec ) const;
	CSSM_RETURN DeleteMdsRootFromMds( HTREEITEM hTreeItemRoot );
	CSSM_RETURN DeleteDirectoryFromMds( HTREEITEM hTreeItemDir );
	CSSM_RETURN DeleteRecordTypeFromMds( HTREEITEM hTreeItemRecType );
	void ShiftFocusToListView( int iItem ) const;
	CMapPtrToWord m_mapItemWasVisited;
	HTREEITEM GetNextSearchPos( HTREEITEM hTreeItem );
	void InvalidateFind();
	HTREEITEM m_hTreeItemRootOfSearch;
	HTREEITEM InsertItem( LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent );

	CImageList m_ctlImage;
	//{{AFX_MSG(CMdsEditTreeView)
	afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditDelete();
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditNewRecord();
	afx_msg void OnUpdateEditNewRecord(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditFindNext();
	afx_msg void OnMdsExportMdsFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in MdsEditView.cpp
inline CMdsEditDoc* CMdsEditTreeView::GetDocument()
   { return (CMdsEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDSEDITVIEW_H__ED147A21_6BBD_11D2_A091_00A0C90988EF__INCLUDED_)
