/*-----------------------------------------------------------------------
 * File: MDSEDITVIEW.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// MdsEditView.cpp : implementation of the CMdsEditTreeView class
//

#include "stdafx.h"
#include "MdsEdit.h"

#include "MdsEditDoc.h"
#include "MdsEditView.h"
#include "RecType.h"
#include "CdsaRecType.h"
#include "MainFrm.h"
#include "MdsEditListView.h"
#include "FindDlg.h"
#include "AppMemTrack.h"
//#include "errMsgString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdsEditTreeView

IMPLEMENT_DYNCREATE(CMdsEditTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CMdsEditTreeView, CTreeView)
	//{{AFX_MSG_MAP(CMdsEditTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteItem)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_EDIT_NEWRECORD, OnEditNewRecord)
	ON_UPDATE_COMMAND_UI(ID_EDIT_NEWRECORD, OnUpdateEditNewRecord)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_FINDNEXT, OnEditFindNext)
	ON_COMMAND(ID_MDS_EXPORTMDSFILE, OnMdsExportMdsFile)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMdsEditTreeView construction/destruction

CMdsEditTreeView::CMdsEditTreeView() :
	m_hTreeItemRootOfSearch( 0 ),
	m_hTreeItemNextSearchPos( 0 )
{
	// TODO: add construction code here
}

CMdsEditTreeView::~CMdsEditTreeView()
{
}

BOOL CMdsEditTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//	the CREATESTRUCT cs
	cs.style |= TVS_HASLINES	|
				TVS_LINESATROOT |
				TVS_HASBUTTONS	|
				TVS_SHOWSELALWAYS;

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMdsEditTreeView drawing

void CMdsEditTreeView::OnDraw(CDC* pDC)
{
	CMdsEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CMdsEditTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	Refresh();

	CMdsEditDoc *pDoc = GetDocument();
	if ( pDoc->m_strImportFile != "" )
	{
		if ( ImportMdsFile(pDoc->m_strImportFile) == FALSE )
		{
			AfxMessageBox( _T("Error occurred during import") );
		}
		else
		{
			AfxMessageBox( _T("MDS updated") );
		}

		pDoc->m_strImportFile = "";
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMdsEditTreeView printing

BOOL CMdsEditTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMdsEditTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMdsEditTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMdsEditTreeView diagnostics

#ifdef _DEBUG
void CMdsEditTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMdsEditTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMdsEditDoc* CMdsEditTreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMdsEditDoc)));
	return (CMdsEditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMdsEditTreeView message handlers

HTREEITEM CMdsEditTreeView::AddDirectory(CMDS *pMds, LPCTSTR szDirName, HTREEITEM hTreeItemParent )
{
	CString strDirName = szDirName;
	HTREEITEM hTreeItemDir =
		InsertItem(
			szDirName,
			IID_CLOSEDFOLDER,
			IID_OPENEDFOLDER,
			hTreeItemParent);

	CDir * pDir = NULL;
	if ( strDirName == MDS_CDSA_DIRECTORY )
	{
		pDir = new CDir( pMds, szDirName );

		/*h_layer*/
		CCssmRecInfoType cssmRecInfoType;
		CRecType *pRecType =
			new CCdsaRecType< CCssmRecInfoType >( cssmRecInfoType, pDir );
		AddRecordType( pRecType, hTreeItemDir );

		/*bsp*/
		CEmmRecInfoType emmRecInfoType;
		pRecType =
			new CCdsaRecType< CEmmRecInfoType >( emmRecInfoType, pDir );
		AddRecordType( pRecType, hTreeItemDir );

		/*device*/
		CBioAPI_DeviceInfoType bioDeviceRecInfoType;
		pRecType =
			new CCdsaRecType< CBioAPI_DeviceInfoType >( bioDeviceRecInfoType, pDir );
		AddRecordType( pRecType, hTreeItemDir );

	}

	/*BOOL bStatus = */
		GetTreeCtrl().SetItemData(
						hTreeItemDir,
						(DWORD) pDir);

	return hTreeItemDir;
}

void CMdsEditTreeView::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM hTreeItemSelected	   = GetTreeCtrl().GetSelectedItem();

	//populate the list view
	//CMdsEditDoc * pDoc = GetDocument();

	CMainFrame * pWnd = (CMainFrame *) AfxGetMainWnd();
	CString strRecPath = BuildRecordPath( hTreeItemSelected );
	pWnd->SetPaneText( strRecPath );

	CMdsEditListView * pListView =
		(CMdsEditListView *) pWnd->GetListView();

	CRec *pRec = NULL;
	if ( IsRecord(hTreeItemSelected) )
	{
		pRec = (CRec *) GetTreeCtrl().GetItemData( hTreeItemSelected );
	}

	pListView->Populate( pRec );

	*pResult = 0;
}

HTREEITEM CMdsEditTreeView::AddRecordType(CRecType *pRecType, HTREEITEM hTreeItemDir)
{

	HTREEITEM hTreeItemRecType =
		InsertItem(
			pRecType->Name(),
			IID_CLOSEDFOLDER,
			IID_OPENEDFOLDER,
			hTreeItemDir);

	/*BOOL bStatus = */
		GetTreeCtrl().SetItemData(
						hTreeItemRecType,
						(DWORD) pRecType);

	for (CRec * pRec = pRecType->FirstRec();
		 pRec;
		 pRec = pRecType->NextRec())
	{
		/*HTREEITEM hTreeItemRec = */AddRecord( pRec, hTreeItemRecType );
	} //for
	return hTreeItemRecType;
}

void CMdsEditTreeView::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM hTreeItem = pNMTreeView->itemOld.hItem;

	do
	{
		if ( IsMdsRoot(hTreeItem) )
		{
			break;
		}
		if ( IsDirectory(hTreeItem) )
		{
			CDir * pDir =
				(CDir *) GetTreeCtrl().GetItemData( hTreeItem );
			delete pDir;
			GetTreeCtrl().SetItemData( hTreeItem, 0 );
			break;
		}
		if ( IsRecordType(hTreeItem) )
		{
			CRecType * pRecType =
				(CRecType *) GetTreeCtrl().GetItemData( hTreeItem );
			delete pRecType;
			GetTreeCtrl().SetItemData( hTreeItem, 0 );
			break;
		}
		if ( IsRecord(hTreeItem) )
		{
			CRec * pRec =
				(CRec *) GetTreeCtrl().GetItemData( hTreeItem );
			delete pRec;
			GetTreeCtrl().SetItemData( hTreeItem, 0 );
			break;
		}
	} while ( 1 );

	*pResult = 0;
}

BOOL CMdsEditTreeView::IsMdsRoot(HTREEITEM hTreeItem) const
{
	HTREEITEM hTreeItemMdsRoot = GetTreeCtrl().GetRootItem();
	return hTreeItem == hTreeItemMdsRoot;
}

BOOL CMdsEditTreeView::IsDirectory(HTREEITEM hTreeItem) const
{
	HTREEITEM hTreeItemParent = GetTreeCtrl().GetParentItem(hTreeItem);
	return IsMdsRoot( hTreeItemParent );
}

BOOL CMdsEditTreeView::IsRecordType(HTREEITEM hTreeItem) const
{
	HTREEITEM hTreeItemParent = GetTreeCtrl().GetParentItem(hTreeItem);
	return IsDirectory( hTreeItemParent );
}

BOOL CMdsEditTreeView::IsRecord(HTREEITEM hTreeItem) const
{
	HTREEITEM hTreeItemParent = GetTreeCtrl().GetParentItem(hTreeItem);
	return IsRecordType( hTreeItemParent );
}

HTREEITEM CMdsEditTreeView::AddRecord(CRec *pRec, HTREEITEM hTreeItemRecType)
{
	CString strItemSelected =
		pRec->AttributeFormatString(0); //this is wrong, but it will have to do

	HTREEITEM hTreeItemRec =
		InsertItem(
			strItemSelected,
			IID_CLOSEDFOLDER,
			IID_OPENEDFOLDER,
			hTreeItemRecType);
	/*BOOL bStatus = */
		GetTreeCtrl().SetItemData(
						hTreeItemRec,
						(DWORD) pRec);

	return hTreeItemRec;
}

BOOL CMdsEditTreeView::Refresh()
{
	GetTreeCtrl().LockWindowUpdate();

	StoreState();

	HTREEITEM hTreeItemMdsRoot = GetTreeCtrl().GetRootItem();
	if ( hTreeItemMdsRoot )
	{
		GetTreeCtrl().Expand( hTreeItemMdsRoot, TVE_COLLAPSE );

		// fixme, free all the records stored in the tree before
		// deleting the items
		GetTreeCtrl().DeleteAllItems();
	}

	hTreeItemMdsRoot =
				InsertItem(
					_T("MDS"),
					IID_MYCOMPUTER,
					IID_MYCOMPUTER,
					TVI_ROOT);

	CMdsEditDoc * pDoc = GetDocument();

	/*BOOL bStatus = */GetTreeCtrl().SetItemData( hTreeItemMdsRoot, (DWORD) (pDoc->m_pMds) );

	CSSM_NAME_LIST_PTR pDirNameList = NULL;

	CSSM_RETURN ret = pDoc->m_pMds->GetDbNames(&pDirNameList);

	if ( ret == CSSM_OK )
	{
		for ( uint32 i = 0; i < pDirNameList->NumStrings; i++ )
		{
			AddDirectory( (pDoc->m_pMds), pDirNameList->String[i], hTreeItemMdsRoot );
		}
	}

	pDoc->m_pMds->FreeNameList( pDirNameList );

	if ( RestoreState() == FALSE )
	{
		TRACE( "CMdsEditTreeView::Refresh:Can't fully restore state\n" );
	}

	GetTreeCtrl().UnlockWindowUpdate();

	InvalidateFind();
	return TRUE;
}

HTREEITEM CMdsEditTreeView::InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent)
{
	CString strItemSelected = lpszItem;

	HTREEITEM hTreeItem =
		GetTreeCtrl().InsertItem(
						strItemSelected,
						nImage,
						nSelectedImage,
						hParent,
						TVI_SORT);

	CString strParentOfItemSelected;
	HTREEITEM hTreeItemParent = GetTreeCtrl().GetParentItem(hTreeItem);
	if ( hTreeItemParent )
	{
		strParentOfItemSelected = GetTreeCtrl().GetItemText( hTreeItemParent );
	}

	return hTreeItem;
}

void CMdsEditTreeView::OnEditDelete()
{
	HTREEITEM hTreeItemSelected = GetTreeCtrl().GetSelectedItem();

	try
	{
		if ( IsRecord(hTreeItemSelected) )
		{
			int iRet =
				AfxMessageBox(
					_T("Do You Really Want to Delete a Record?"),
					MB_YESNO);
			if ( iRet != IDYES )
			{
				return;
			}
			if ( DeleteRecordFromMds(hTreeItemSelected) == CSSM_OK )
			{
				throw( "Tree item deleted" );
			}
			else
			{
				AfxMessageBox( "Cannot delete record" );
				return;
			}
		}
		if ( IsRecordType(hTreeItemSelected) )
		{
			int iRet =
				AfxMessageBox(
					_T("Do You Really Want to Delete a RecordType?"),
					MB_YESNO);
			if ( iRet != IDYES )
			{
				return;
			}
			if ( DeleteRecordTypeFromMds(hTreeItemSelected) == CSSM_OK )
			{
				throw( "Tree item deleted" );
			}
			else
			{
				AfxMessageBox( "Cannot delete record type" );
				return;
			}
		}
		if ( IsDirectory(hTreeItemSelected) )
		{
			int iRet =
				AfxMessageBox(
					_T("Do You Really Want to Delete a Directory?"),
					MB_YESNO);
			if ( iRet != IDYES )
			{
				return;
			}
			if ( DeleteDirectoryFromMds(hTreeItemSelected) == CSSM_OK )
			{
				throw( "Tree item deleted" );
			}
			else
			{
				AfxMessageBox( "Cannot delete directory" );
				return;
			}
		}
		if ( IsMdsRoot(hTreeItemSelected) )
		{
			int iRet =
				AfxMessageBox(
					_T("Do You Really Want to Delete the MDS Root?"),
					MB_YESNO);
			if ( iRet != IDYES )
			{
				return;
			}
			if ( DeleteMdsRootFromMds(hTreeItemSelected) == CSSM_OK )
			{
				throw( "MDS root deleted" );
			}
			else
			{
				AfxMessageBox( "Cannot delete MDS root" );
				return;
			}
		}

		AfxMessageBox( "Unexpected tree item type" );
		ASSERT( FALSE );
		return;
	} //try
	catch ( char *szMsg )
	{
		TRACE( "CMdsEditTreeView::OnEditDelete:%s\n", szMsg );
	}
	catch ( ... )
	{
		TRACE( "CMdsEditTreeView::OnEditDelete:Unknown exception\n" );
	}

	InvalidateFind();
}

void CMdsEditTreeView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	DWORD dwPos = ::GetMessagePos();
	CPoint point ((int) LOWORD (dwPos), (int) HIWORD (dwPos));
	CPoint clientPoint = point;
	ScreenToClient( &clientPoint );

	HTREEITEM hItemUnderCursor = GetTreeCtrl().HitTest(clientPoint);

	if ( hItemUnderCursor )
	{
		GetTreeCtrl().SelectItem( hItemUnderCursor );
	}

	HTREEITEM hItemSelected = GetTreeCtrl().GetSelectedItem();
	if ( hItemSelected )
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MDS_EDIT_TREE_VIEW));

		CMenu * pPopup = menu.GetSubMenu(0);

		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}

	*pResult = 0;
}

void CMdsEditTreeView::OnEditNewRecord()
{
	HTREEITEM hTreeItemSelected = GetTreeCtrl().GetSelectedItem();
	CRecType *pRecType = (CRecType *) GetTreeCtrl().GetItemData( hTreeItemSelected );

	CDir *pDir = pRecType->m_pDir;
	CMDS *pMds = pDir->m_pMds;

	CSSM_DB_UNIQUE_RECORD_PTR recordId = NULL;

	CSSM_RETURN ret =
		pMds->DataInsert(
			pDir->m_hDb,
			pRecType->m_dwRecType,
			&(pRecType->m_outputAttributes),
			NULL,
			&recordId);

	if ( ret != CSSM_OK )
	{
		AfxMessageBox( _T("DataInsert Failed") );
		//REPORT_ERROR(ret,"inserting data");

		Refresh();
		return;
	}

	CRec *pRec = pRecType->NewRec( recordId );
	if ( pRec == NULL )
	{
		AfxThrowMemoryException();
		return;
	}

	HTREEITEM hTreeItemRec = AddRecord( pRec, hTreeItemSelected );
	ASSERT( hTreeItemRec );

	BOOL bStatus = GetTreeCtrl().SelectItem( hTreeItemRec );
	InvalidateFind();

	ASSERT( bStatus );
}

void CMdsEditTreeView::OnUpdateEditNewRecord(CCmdUI* pCmdUI)
{
	HTREEITEM hTreeItemSelected = GetTreeCtrl().GetSelectedItem();
	pCmdUI->Enable( IsRecordType(hTreeItemSelected) );
}

BOOL CMdsEditTreeView::UpdateSelectedRecordLabel(LPCTSTR szLabel)
{
	HTREEITEM hTreeItemSelected = GetTreeCtrl().GetSelectedItem();
	ASSERT ( IsRecord(hTreeItemSelected) );

	BOOL bStatus =
		GetTreeCtrl().SetItemText(
			hTreeItemSelected,
			szLabel);

	return bStatus;
}

CString CMdsEditTreeView::BuildRecordPath(HTREEITEM hTreeItem) const
{
	CString strRecPath = GetTreeCtrl().GetItemText(hTreeItem);

	for (hTreeItem = GetTreeCtrl().GetParentItem(hTreeItem);
		 hTreeItem;
		 hTreeItem = GetTreeCtrl().GetParentItem(hTreeItem))
	{
		 strRecPath = GetTreeCtrl().GetItemText(hTreeItem) + "/" + strRecPath;
	}

	return strRecPath;
}

int CMdsEditTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the Image List
	m_ctlImage.Create(IDB_MDS_IMAGELIST,16,0,RGB(255,0,255));
	m_ctlImage.SetBkColor(GetSysColor(COLOR_WINDOW));

	/// Attach image list to Tree
	GetTreeCtrl().SetImageList(&m_ctlImage, TVSIL_NORMAL);

	return 0;
}

HTREEITEM CMdsEditTreeView::FindFirst()
{
	CFindDlg findDlg;

	findDlg.m_strFind				= m_find.m_strFind;
	findDlg.m_bExamineAttrName		= m_find.m_bExamineAttrName;
	findDlg.m_bExamineAttrValue		= m_find.m_bExamineAttrValue;
	findDlg.m_bMatchCase			= m_find.m_bMatchCase;
	findDlg.m_bMatchWholeStringOnly = m_find.m_bMatchWholeStringOnly;

	if ( findDlg.DoModal() != IDOK )
	{
		return 0;
	}

	m_find.m_strFind			   = findDlg.m_strFind;
	m_find.m_bExamineAttrName	   = findDlg.m_bExamineAttrName;
	m_find.m_bExamineAttrValue	   = findDlg.m_bExamineAttrValue;
	m_find.m_bMatchCase			   = findDlg.m_bMatchCase;
	m_find.m_bMatchWholeStringOnly = findDlg.m_bMatchWholeStringOnly;

	//clear visited map
	m_mapItemWasVisited.RemoveAll();

	m_hTreeItemRootOfSearch = GetTreeCtrl().GetSelectedItem();
	HTREEITEM hTreeItemNextSearchPos =
			GetNextSearchPos( m_hTreeItemRootOfSearch );

	if ( IsRecord(m_hTreeItemRootOfSearch) )
	{
		CRec * pRec =
			(CRec *) GetTreeCtrl().GetItemData( m_hTreeItemRootOfSearch );
		ASSERT( pRec );

		int iMatch =
			pRec->FindStringInRecord(
						m_find.m_strFind,
						m_find.m_bMatchWholeStringOnly,
						m_find.m_bMatchCase,
						m_find.m_bExamineAttrName,
						m_find.m_bExamineAttrValue);
		if ( iMatch != -1 )
		{
			GetTreeCtrl().SelectItem( m_hTreeItemRootOfSearch );

			ShiftFocusToListView( iMatch );

			m_hTreeItemNextSearchPos = hTreeItemNextSearchPos;
			return m_hTreeItemRootOfSearch;
		}
	}

	return FindNext( hTreeItemNextSearchPos );
}

HTREEITEM CMdsEditTreeView::FindNext( HTREEITEM hTreeItem )
{
	if ( m_hTreeItemRootOfSearch == 0 )
	{
		return FindFirst();
	}

	//kinda base case of recursion
	if ( hTreeItem == 0 )
	{
		CString strMsg;
		strMsg.Format( _T("No more record with \"%s\" found"), m_find.m_strFind );
		AfxMessageBox( strMsg );
		InvalidateFind();
		return 0;
	}

	ASSERT( hTreeItem );

	HTREEITEM hTreeItemNextSearchPos =
		GetNextSearchPos( hTreeItem );

	//look at current item
	if ( IsRecord(hTreeItem) )
	{
		CRec * pRec = (CRec *) GetTreeCtrl().GetItemData( hTreeItem );
		int iMatch =
			pRec->FindStringInRecord(
						m_find.m_strFind,
						m_find.m_bMatchWholeStringOnly,
						m_find.m_bMatchCase,
						m_find.m_bExamineAttrName,
						m_find.m_bExamineAttrValue);
		if ( iMatch != -1 )
		{
			GetTreeCtrl().SelectItem( hTreeItem );

			ShiftFocusToListView( iMatch );

			m_hTreeItemNextSearchPos = hTreeItemNextSearchPos;
			return hTreeItem;
		}
	}

	return FindNext( hTreeItemNextSearchPos );
}

void CMdsEditTreeView::InvalidateFind()
{
	m_hTreeItemRootOfSearch = 0;
	m_hTreeItemNextSearchPos = 0;
}

//Return the items in the tree view in a depth first traversal.
HTREEITEM CMdsEditTreeView::GetNextSearchPos(HTREEITEM hTreeItem)
{
	ASSERT( hTreeItem );
	//mark item as visited
	m_mapItemWasVisited[hTreeItem] = TRUE;

	HTREEITEM hTreeItemFirstChild =
		GetTreeCtrl().GetNextItem( hTreeItem, TVGN_CHILD );

	if ( hTreeItemFirstChild && !m_mapItemWasVisited[hTreeItemFirstChild] )
	{
		return hTreeItemFirstChild;
	}

	HTREEITEM hTreeItemNextSibling =
		GetTreeCtrl().GetNextItem( hTreeItem, TVGN_NEXT );

	if ( hTreeItemNextSibling && !m_mapItemWasVisited[hTreeItemNextSibling] )
	{
		return hTreeItemNextSibling;
	}

	HTREEITEM hTreeItemParent =
		GetTreeCtrl().GetNextItem( hTreeItem, TVGN_PARENT );

	if ( hTreeItemParent )
	{
		HTREEITEM hTreeItemRecursion =
			GetNextSearchPos( hTreeItemParent );
		if ( hTreeItemRecursion )
		{
			return hTreeItemRecursion;
		}
	}

	return NULL;
}

void CMdsEditTreeView::OnEditFindNext()
{
	FindNext( m_hTreeItemNextSearchPos );
}

void CMdsEditTreeView::ShiftFocusToListView(int iItem) const
{
	CMainFrame * pWnd = (CMainFrame *) AfxGetMainWnd();
	pWnd->MakeListViewActive();
	CMdsEditListView * pListView = pWnd->GetListView();
	pListView->GetListCtrl().SetItemState(
					iItem,							//int nItem,
					0xFFFFFFFF,						//UINT nState,
					LVIS_FOCUSED | LVIS_SELECTED);	//UINT nMask );
}

CSSM_RETURN CMdsEditTreeView::DeleteRecordFromMds(HTREEITEM hTreeItemRec)
{
	CRec *pRec =
		(CRec *) GetTreeCtrl().GetItemData( hTreeItemRec );
	if ( !pRec )
	{
		AfxMessageBox( _T("NULL CRec*") );
		return ! CSSM_OK;
	}
	CDir *pDir = pRec->m_pRecType->m_pDir;
	CMDS *pMds = pDir->m_pMds;

	CSSM_RETURN crStatus =
		pMds->DataDelete(
				pDir->m_hDb,
				pRec->m_recordId);
	if ( crStatus != CSSM_OK )
	{
		AfxMessageBox( _T("Record Cannot Be Deleted") );
		//REPORT_ERROR(crStatus,"deleting record");
		Refresh();
		return crStatus;
	}

	/*BOOL bStatus = */GetTreeCtrl().DeleteItem( hTreeItemRec );
	return crStatus;
}

CSSM_RETURN CMdsEditTreeView::DeleteRecordTypeFromMds(HTREEITEM hTreeItemRecType)
{
	CSSM_RETURN crStatus = CSSM_OK;

	for (HTREEITEM hTreeItemRec = GetTreeCtrl().GetNextItem(hTreeItemRecType, TVGN_CHILD);
		 hTreeItemRec;
		 hTreeItemRec = GetTreeCtrl().GetNextItem(hTreeItemRecType, TVGN_CHILD)) //No, this is not a bug
	{
		crStatus = DeleteRecordFromMds( hTreeItemRec );
		if ( crStatus != CSSM_OK )
		{
			AfxMessageBox( _T("Cannot delete record type") );
			//REPORT_ERROR(crStatus,"deleting record type");

			return crStatus;
		}
	}

	return CSSM_OK;
}

CSSM_RETURN CMdsEditTreeView::DeleteDirectoryFromMds(HTREEITEM hTreeItemDir)
{
	CSSM_RETURN crStatus = ! CSSM_OK;

	for (HTREEITEM hTreeItemRecType = GetTreeCtrl().GetNextItem(hTreeItemDir, TVGN_CHILD);
		 hTreeItemRecType;
		 hTreeItemRecType = GetTreeCtrl().GetNextItem(hTreeItemRecType, TVGN_NEXT))
	{
		crStatus = DeleteRecordTypeFromMds( hTreeItemRecType );
		if ( crStatus != CSSM_OK )
		{
			AfxMessageBox( _T("Cannot delete directory") );
			//REPORT_ERROR(crStatus,"deleting directory");

			return crStatus;
		}
	}

	return CSSM_OK;
}

CSSM_RETURN CMdsEditTreeView::DeleteMdsRootFromMds(HTREEITEM hTreeItemMdsRoot)
{
	CSSM_RETURN crStatus = ! CSSM_OK;

	for (HTREEITEM hTreeItemDir = GetTreeCtrl().GetNextItem(hTreeItemMdsRoot, TVGN_CHILD);
		 hTreeItemDir;
		 hTreeItemDir = GetTreeCtrl().GetNextItem(hTreeItemDir, TVGN_NEXT))
	{
		crStatus = DeleteDirectoryFromMds( hTreeItemDir );
		if ( crStatus != CSSM_OK )
		{
			AfxMessageBox( _T("Cannot delete mds root") );
			//REPORT_ERROR(crStatus,"deleting mds root");

			return crStatus;
		}
	}

	return CSSM_OK;
}

void CMdsEditTreeView::OnMdsExportMdsFile()
{
	CFileDialog fileDialog(
					FALSE,
					_T("mds"),
					NULL,
					0,
					_T("MDS Archive Files (*.mds)|*.mds|All Files (*.*)|*.*||"));

	fileDialog.m_ofn.lpstrTitle = _T("Export MDS Content");
	fileDialog.m_ofn.Flags |= OFN_HIDEREADONLY;

	if ( fileDialog.DoModal() == IDCANCEL )
	{
		return;
	}

	CString strPathName = fileDialog.GetPathName();

	CFile file;
	if ( !file.Open(strPathName, CFile::modeCreate | CFile::modeWrite) )
	{
		CString strStatus;
		strStatus.Format( _T("Cannot open %s for writing"), strPathName );
		AfxMessageBox( strStatus );
		return;
	}

	CArchive archive(&file, CArchive::store);
	try
	{
		HTREEITEM hTreeItemSelected = GetTreeCtrl().GetSelectedItem();
		if ( IsRecord(hTreeItemSelected) )
		{
			ExportRecord( archive, hTreeItemSelected );
			throw( "Exported Record" );
		}
		if ( IsRecordType(hTreeItemSelected) )
		{
			ExportRecordType( archive, hTreeItemSelected );
			throw( "Exported RecordType" );
		}
		if ( IsDirectory(hTreeItemSelected) )
		{
			ExportDirectory( archive, hTreeItemSelected );
			throw( "Exported Directory" );
		}
		if ( IsMdsRoot(hTreeItemSelected) )
		{
			ExportMdsRoot( archive, hTreeItemSelected );
			throw( "Exported MDS root" );
		}
	} //try
	catch ( char *szMsg )
	{
		TRACE( "OnMdsExportMdsFile:%s\n", szMsg );
	}
	catch ( CFileException * e )
	{
		AfxMessageBox( _T("File Exception") );
		e->Delete();
	}
	catch ( ... )
	{
		AfxMessageBox( _T("Unknown Exception") );
	}

	archive.Close();
	file.Close();
}

void CMdsEditTreeView::ExportRecord(CArchive & archive, HTREEITEM hTreeItemRec) const
{
	CRec *pRec =
		(CRec *) GetTreeCtrl().GetItemData( hTreeItemRec );
	if ( !pRec )
	{
		AfxMessageBox( _T("NULL CRec*") );
		return;
	}

	CDir *pDir = pRec->m_pRecType->m_pDir;

	//store record
	archive << pDir->m_strDirName;
	archive.Write( &(pRec->m_pRecType->m_dwRecType), 4 );
	pRec->Serialize( archive );
}

void CMdsEditTreeView::ExportRecordType(CArchive & archive, HTREEITEM hTreeItemRecType) const
{
	for (HTREEITEM hTreeItemRec = GetTreeCtrl().GetNextItem(hTreeItemRecType, TVGN_CHILD);
		 hTreeItemRec;
		 hTreeItemRec = GetTreeCtrl().GetNextItem(hTreeItemRec, TVGN_NEXT))
	{
		ExportRecord( archive, hTreeItemRec );
	}
}

void CMdsEditTreeView::ExportDirectory(CArchive & archive, HTREEITEM hTreeItemDir) const
{
	for (HTREEITEM hTreeItemRecType = GetTreeCtrl().GetNextItem(hTreeItemDir, TVGN_CHILD);
		 hTreeItemRecType;
		 hTreeItemRecType = GetTreeCtrl().GetNextItem(hTreeItemRecType, TVGN_NEXT))
	{
		ExportRecordType( archive, hTreeItemRecType );
	}
}

void CMdsEditTreeView::ExportMdsRoot(CArchive & archive, HTREEITEM hTreeItemMdsRoot) const
{
	for (HTREEITEM hTreeItemDir = GetTreeCtrl().GetNextItem(hTreeItemMdsRoot, TVGN_CHILD);
		 hTreeItemDir;
		 hTreeItemDir = GetTreeCtrl().GetNextItem(hTreeItemDir, TVGN_NEXT))
	{
		ExportDirectory( archive, hTreeItemDir );
	}
}

BOOL CMdsEditTreeView::ImportRecord(CArchive & archive)
{
	BOOL bStatus = FALSE;

	HTREEITEM hTreeItemMdsRoot = GetTreeCtrl().GetRootItem();
	if ( !hTreeItemMdsRoot )
	{
		AfxMessageBox( _T("MDS root is missing") );
		return FALSE;
	}

	CMDS * pMds = (CMDS *) GetTreeCtrl().GetItemData( hTreeItemMdsRoot );

	BOOL bDone = FALSE;
	while ( !bDone )
	{
		CString strDirName;
		CSSM_DB_RECORDTYPE dwRecType = 0;
		//retrieve record
		try
		{
			archive >> strDirName;
			UINT iRead = archive.Read( &dwRecType, 4 );
			ASSERT( iRead == 4 );
			HTREEITEM hTreeItemDir = FindDirectoryItem( hTreeItemMdsRoot, strDirName );
			if ( !hTreeItemDir )
			{
				AfxMessageBox( _T("Unsupported directory in MDS file") );
				break;
			}
			CDir * pDir =
				(CDir *) GetTreeCtrl().GetItemData( hTreeItemDir );

			HTREEITEM hTreeItemRecType =
				FindRecordTypeItem( hTreeItemDir, dwRecType );
			if ( !hTreeItemRecType )
			{
				AfxMessageBox( _T("Unsupported record type in MDS file") );
				break;
			}

			CRecType * pRecType =
				(CRecType *) GetTreeCtrl().GetItemData( hTreeItemRecType ); //polymorphic

			CRec * pRec = NULL;
			//this is going to be ugly
			switch ( dwRecType )
			{
			case BIOAPI_H_LAYER_RECORDTYPE:
				{
					CCssmRecInfoType recInfoType;
					pRec =
						new CCdsaRec< CCssmRecInfoType >( recInfoType, pRecType );
				}
				break;

			case BIOAPI_BSP_RECORDTYPE:
				{
					CEmmRecInfoType recInfoType;
					pRec =
						new CCdsaRec< CEmmRecInfoType >( recInfoType, pRecType );
				}
				break;


			default:
				AfxMessageBox( _T("Unexpected record type") );
				break;
			} //switch

			pRec->Serialize( archive );

			//DataInsert here
			CSSM_DB_UNIQUE_RECORD_PTR recordId = NULL;

			CSSM_RETURN ret = pMds->DataInsert(
					pDir->m_hDb,
					pRecType->m_dwRecType,
					&(pRec->m_outputAttributes),
					NULL,
					&recordId);

			pRec->m_recordId = recordId;

			if ( ret != CSSM_OK )
			{
				AfxMessageBox( _T("DataInsert failed during MDS file import") );
				//REPORT_ERROR(ret,"inserting data during file import");

				break;
			}
			else
			{
				AddRecord( pRec, hTreeItemRecType );
			}
		}

		catch ( CArchiveException * e )
		{
			if ( e->m_cause != CArchiveException::endOfFile )
			{
				throw( e );
			}
			bStatus = TRUE;
			bDone = TRUE;
			e->Delete();
		}
		catch ( ... )
		{
			bDone = TRUE;
			TRACE( "ImportRecord:Unknown Exception\n" );
			ASSERT( FALSE );
		}
	} //while

	GetTreeCtrl().InvalidateRect( NULL );

	return bStatus;
}

BOOL CMdsEditTreeView::ImportMdsFile(LPCTSTR lpszPathName) //NULL
{
	BOOL bStatus = FALSE;

	CString strPathName;

	if ( !lpszPathName )
	{
		CFileDialog fileDialog(
						TRUE,
						_T("mds"),
						NULL,
						0,
						_T("MDS Archive Files (*.mds)|*.mds|All Files (*.*)|*.*||"));

		fileDialog.m_ofn.lpstrTitle = _T("Import MDS Content");
		fileDialog.m_ofn.Flags |= OFN_HIDEREADONLY;

		if ( fileDialog.DoModal() == IDCANCEL )
		{
			return FALSE;
		}

		strPathName = fileDialog.GetPathName();
	}
	else
	{
		strPathName = lpszPathName;
	}

	CFile file;
	if ( !file.Open(strPathName, CFile::modeRead) )
	{
		CString strStatus;
		strStatus.Format( _T("Cannot open %s for reading"), strPathName );
		AfxMessageBox( strStatus );
		return FALSE;
	}

	CArchive archive(&file, CArchive::load);
	try
	{
		bStatus = ImportRecord( archive );
		if ( bStatus == FALSE )
		{
			throw( "ImportRecord returned FALSE" );
		}
	} //try
	catch ( char *szMsg )
	{
		TRACE( "ImportMdsFile:%s\n", szMsg );
	}
	catch ( CFileException * e )
	{
		AfxMessageBox( _T("File Exception") );
		e->Delete();
	}
	catch ( ... )
	{
		AfxMessageBox( _T("Unknown Exception") );
	}

	archive.Close();
	file.Close();

	return bStatus;
}

HTREEITEM CMdsEditTreeView::FindRecordTypeItem(HTREEITEM hTreeItemDir, CSSM_DB_RECORDTYPE dwRecType) const
{
	for (HTREEITEM hTreeItemRecType = GetTreeCtrl().GetNextItem(hTreeItemDir, TVGN_CHILD);
		 hTreeItemRecType;
		 hTreeItemRecType = GetTreeCtrl().GetNextItem(hTreeItemRecType, TVGN_NEXT))
	{
		CRecType * pRecType = (CRecType *) GetTreeCtrl().GetItemData( hTreeItemRecType );
		if ( pRecType && (pRecType->m_dwRecType == dwRecType) )
		{
			return hTreeItemRecType;
		}
	}

	return 0;
}

HTREEITEM CMdsEditTreeView::FindDirectoryItem(HTREEITEM hTreeItemMdsRoot, CString &strDirName) const
{
	for (HTREEITEM hTreeItemDir = GetTreeCtrl().GetNextItem(hTreeItemMdsRoot, TVGN_CHILD);
		 hTreeItemDir;
		 hTreeItemDir = GetTreeCtrl().GetNextItem(hTreeItemDir, TVGN_NEXT))
	{
		CString strLabel = GetTreeCtrl().GetItemText( hTreeItemDir );
		if ( strLabel == strDirName )
		{
			return hTreeItemDir;
		}
	}

	return 0;
}

BOOL CMdsEditTreeView::StoreState()
{
	HTREEITEM hTreeItemSelected = GetTreeCtrl().GetSelectedItem();
	if ( !hTreeItemSelected ) //tree is empty
	{
		return TRUE;
	}

	HTREEITEM hTreeItemParent = GetTreeCtrl().GetParentItem(hTreeItemSelected);

	m_state.m_strItemSelected = GetTreeCtrl().GetItemText( hTreeItemSelected );
	if ( hTreeItemParent )
	{
		m_state.m_strParentOfItemSelected =
			GetTreeCtrl().GetItemText( hTreeItemParent );

		m_state.m_iSiblingRanking = 0;
		for (HTREEITEM hTreeItem = GetTreeCtrl().GetNextItem( hTreeItemParent, TVGN_CHILD );
			 hTreeItem;
			 hTreeItem = GetTreeCtrl().GetNextItem( hTreeItem, TVGN_NEXT ))
		{
			if ( hTreeItem == hTreeItemSelected )
			{
				break;
			}
			m_state.m_iSiblingRanking++;
		}
		if ( !hTreeItem )
		{
			return FALSE;
		}
	}
	else //assume the selected item is MDS root
	{
		m_state.m_strParentOfItemSelected.Empty();
		m_state.m_iSiblingRanking = -1;
	}

	//store the expansion properties of the tree
	m_state.m_mapItemWasExpanded.RemoveAll();

	HTREEITEM hTreeItemMdsRoot = GetTreeCtrl().GetRootItem();
	if ( hTreeItemMdsRoot )
	{
		StoreExpansionProperties( hTreeItemMdsRoot );
	}

	//store list view selected position
	CMainFrame * pWnd = (CMainFrame *) AfxGetMainWnd();
	CMdsEditListView * pListView = pWnd->GetListView();
	m_state.m_iListItemSelected =
		pListView->GetSelectedItemIndex() - 1;

	return TRUE;
}

BOOL CMdsEditTreeView::RestoreState()
{
	BOOL bStatus = FALSE;

	HTREEITEM hTreeItemMdsRoot = GetTreeCtrl().GetRootItem();

	//find parent
	HTREEITEM hTreeItemParent =
		FindItem( m_state.m_strParentOfItemSelected, hTreeItemMdsRoot );

	HTREEITEM hTreeItem = 0;
	if ( hTreeItemParent )
	{
		//find sibling of correct ranking
		int i = 0;
		for (hTreeItem = GetTreeCtrl().GetNextItem( hTreeItemParent, TVGN_CHILD );
			 hTreeItem && (i < m_state.m_iSiblingRanking);
			 hTreeItem = GetTreeCtrl().GetNextItem( hTreeItem, TVGN_NEXT ))
		{
			i++;
		}
		if ( !hTreeItem || (i != m_state.m_iSiblingRanking) )
		{
			hTreeItem = hTreeItemParent;
			bStatus = FALSE;
		}

		//check the label of the sibling found
		CString strLabel = GetTreeCtrl().GetItemText( hTreeItem );
		if ( strLabel != m_state.m_strItemSelected )
		{
			hTreeItem = hTreeItemParent;
			bStatus = FALSE;
		}

		bStatus = TRUE;
	}
	else //can sorta assume the selected item is MDS root
	{
		hTreeItem = hTreeItemMdsRoot;
		bStatus = FALSE;
	}

	//restore the expansion properties of the tree
	if ( hTreeItemMdsRoot )
	{
		RestoreExpansionProperties( hTreeItemMdsRoot );
	}

	GetTreeCtrl().SelectItem( hTreeItem );

	if ( bStatus == TRUE )
	{
		//recall list view selected position
		if ( m_state.m_iListItemSelected >= 0 )
		{
			CMainFrame * pWnd = (CMainFrame *) AfxGetMainWnd();
			CMdsEditListView * pListView = pWnd->GetListView();
			pListView->GetListCtrl().SetItemState(
										m_state.m_iListItemSelected,	//int nItem,
										0xFFFFFFFF,						//UINT nState,
										LVIS_FOCUSED | LVIS_SELECTED);	//UINT nMask );
		}
	}

	return bStatus;
}

HTREEITEM CMdsEditTreeView::FindItem(const CString & strLabel,
									 HTREEITEM hTreeItemSearchRoot) const
{
	if ( (strLabel == "") || !hTreeItemSearchRoot )
	{
		return 0;
	}

	CString strCurrentLabel = GetTreeCtrl().GetItemText( hTreeItemSearchRoot );
	if ( strCurrentLabel == strLabel )
	{
		return hTreeItemSearchRoot;
	}

	for (HTREEITEM hTreeItem = GetTreeCtrl().GetNextItem( hTreeItemSearchRoot, TVGN_CHILD );
		 hTreeItem;
		 hTreeItem = GetTreeCtrl().GetNextItem( hTreeItem, TVGN_NEXT ))
	{
		HTREEITEM hTreeItemRecursive = FindItem( strLabel, hTreeItem );
		if ( hTreeItemRecursive )
		{
			return hTreeItemRecursive;
		}
	}

	return 0;
}

void CMdsEditTreeView::StoreExpansionProperties(HTREEITEM hTreeItemRoot)
{
	ASSERT( hTreeItemRoot );

	if ( IsRecord(hTreeItemRoot) )
	{
		return;
	}

	CString strCurrentLabel = GetTreeCtrl().GetItemText( hTreeItemRoot );

	m_state.m_mapItemWasExpanded[strCurrentLabel] =
		(void *) (GetTreeCtrl().GetItemState(
							hTreeItemRoot,
							TVIS_EXPANDED) & TVIS_EXPANDED ? TRUE : FALSE);

	for (HTREEITEM hTreeItem = GetTreeCtrl().GetNextItem( hTreeItemRoot, TVGN_CHILD );
		 hTreeItem;
		 hTreeItem = GetTreeCtrl().GetNextItem( hTreeItem, TVGN_NEXT ))
	{
		StoreExpansionProperties( hTreeItem );
	}
}

void CMdsEditTreeView::RestoreExpansionProperties(HTREEITEM hTreeItemRoot)
{
	ASSERT( hTreeItemRoot );

	if ( IsRecord(hTreeItemRoot) )
	{
		return;
	}

	CString strCurrentLabel = GetTreeCtrl().GetItemText( hTreeItemRoot );

	if ( m_state.m_mapItemWasExpanded[strCurrentLabel] )
	{
		GetTreeCtrl().Expand( hTreeItemRoot, TVE_EXPAND );
	}

	for (HTREEITEM hTreeItem = GetTreeCtrl().GetNextItem( hTreeItemRoot, TVGN_CHILD );
		 hTreeItem;
		 hTreeItem = GetTreeCtrl().GetNextItem( hTreeItem, TVGN_NEXT ))
	{
		RestoreExpansionProperties( hTreeItem );
	}
}
