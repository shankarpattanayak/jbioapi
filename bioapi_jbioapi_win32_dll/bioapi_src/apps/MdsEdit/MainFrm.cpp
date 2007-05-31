/*-----------------------------------------------------------------------
 * File: MAINFRM.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MdsEdit.h"

#include "MainFrm.h"
#include "MdsEditListView.h"
#include "MdsEditView.h"
#include "OptionsDlg.h"
#include "Rec.h"
#include "AppMemTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_WM_DESTROY()
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	ON_COMMAND(ID_MDS_IMPORTMDSFILE, OnMdsImportMdsFile)
	ON_UPDATE_COMMAND_UI(ID_MDS_IMPORTMDSFILE, OnUpdateMdsImportMdsFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,			// status line indicator
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() :
	m_bIsZoomedInitially( FALSE )
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

/*	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) //VC6.0
*/
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))

	{
		TRACE0("Failed to create toolbar\n");
		return -1;		// fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;		// fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//	be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndToolBar.ShowWindow( FALSE );

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//	the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// CG: The following block was added by the Splitter Bar component.
	{
		if ( !m_wndSplitter.CreateStatic(this, 1, 2) )
		{
			TRACE0("Failed to create splitter bar ");
			return FALSE;	 // failed to create
		}

		// add the first splitter pane - the default view in column 0
		if (!m_wndSplitter.CreateView(0, 0,
			pContext->m_pNewViewClass, CSize(200, 50), pContext))
		{
			TRACE0("Failed to create first pane\n");
			return FALSE;
		}

		// add the second splitter pane - an input view in column 1
		if (!m_wndSplitter.CreateView(
							0,
							1,
							RUNTIME_CLASS(CMdsEditListView),
							CSize(0, 0),
							pContext))
		{
			TRACE0("Failed to create second pane\n");
			return FALSE;
		}

		int cx, cy;
		CMdsEditApp * pApp = (CMdsEditApp *) AfxGetApp();

		m_bIsZoomedInitially =
			pApp->GetProfileInt(
				_T("Settings"),
				_T("IsZoomed"),
				FALSE);

		if ( !m_bIsZoomedInitially )
		{
			cx =
				pApp->GetProfileInt(
					_T("Settings"),
					_T("MainFrameWidth"),
					0x300);

			cy =
				pApp->GetProfileInt(
					_T("Settings"),
					_T("MainFrameHeight"),
					0x200);

			SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOMOVE );
		}

		cx =
			pApp->GetProfileInt(
				_T("Settings"),
				_T("TreeViewWidth"),
				200);

		m_wndSplitter.SetColumnInfo( 0, cx, 0 );

		return TRUE;
	}
}

CMdsEditTreeView * CMainFrame::GetTreeView()
{
	return (CMdsEditTreeView *) m_wndSplitter.GetPane(0, 0);
}

CMdsEditListView * CMainFrame::GetListView()
{
	return (CMdsEditListView *) m_wndSplitter.GetPane(0, 1);
}

void CMainFrame::OnViewRefresh()
{
	CMdsEditTreeView *pTreeView = GetTreeView();
	/*BOOL bStatus = */pTreeView->Refresh();
}

BOOL CMainFrame::SetPaneText(LPCTSTR szMsg)
{
	return m_wndStatusBar.SetPaneText( 0, szMsg );
}

void CMainFrame::MakeListViewActive()
{
	m_wndSplitter.SetActivePane( 0, 1 );
}

void CMainFrame::OnEditFind()
{
	GetTreeView()->FindFirst();
}

void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	CString strTmp;
	CMdsEditApp * pApp = (CMdsEditApp *) AfxGetApp();

	BOOL bStatus = FALSE;
	int cxCur =0, cxMin = 0, cyCur = 0;

	if ( IsZoomed() )
	{
		pApp->WriteProfileInt(
				_T("Settings"),
				_T("IsZoomed"),
				TRUE);
	}
	else
	{
		pApp->WriteProfileInt(
				_T("Settings"),
				_T("IsZoomed"),
				FALSE);

		CRect rectMainFrame;
		GetWindowRect( rectMainFrame );
		cyCur = rectMainFrame.bottom - rectMainFrame.top;
		cxCur = rectMainFrame.right - rectMainFrame.left;
		bStatus =
			pApp->WriteProfileInt(
				_T("Settings"),
				_T("MainFrameWidth"),
				cxCur);

		bStatus =
			pApp->WriteProfileInt(
				_T("Settings"),
				_T("MainFrameHeight"),
				cyCur);
	}

	m_wndSplitter.GetColumnInfo( 0, cxCur, cxMin );
	bStatus =
		pApp->WriteProfileInt(
			_T("Settings"),
			_T("TreeViewWidth"),
			cxCur);
}

void CMainFrame::OnViewOptions()
{
	//CMdsEditApp *pApp = (CMdsEditApp *) AfxGetApp();

	COptionsDlg optionsDlg;

	optionsDlg.m_bViewBlobAsString = CRec::s_bViewBlobAsString;
	if ( optionsDlg.DoModal() != IDOK )
	{
		return;
	}

	if ( optionsDlg.m_bViewBlobAsString == CRec::s_bViewBlobAsString )
	{
		return;
	}

	CRec::s_bViewBlobAsString = optionsDlg.m_bViewBlobAsString;

	CMdsEditListView * pListView = GetListView();

	if ( pListView && pListView->m_pRec )
	{
		pListView->Populate( pListView->m_pRec );
	}
}

void CMainFrame::OnMdsImportMdsFile()
{
	CMdsEditTreeView * pTreeView = GetTreeView();
	pTreeView->ImportMdsFile();
}

void CMainFrame::OnUpdateMdsImportMdsFile(CCmdUI* pCmdUI)
{
	CMdsEditTreeView *pTreeView = GetTreeView();

	HTREEITEM hTreeItemSelected = 0;

	if ( pTreeView )
	{
		hTreeItemSelected =
			pTreeView->GetTreeCtrl().GetSelectedItem();

		pCmdUI->Enable(
			hTreeItemSelected &&
			pTreeView->IsMdsRoot(hTreeItemSelected));

		return;
	}

	pCmdUI->Enable( FALSE );
}
