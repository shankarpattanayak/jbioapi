/*-----------------------------------------------------------------------
 * File: MDSEDITLISTVIEW.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// MdsEditListView.cpp : implementation file
//

#include "stdafx.h"
#include "stdio.h"
#include "MdsEdit.h"
#include "MdsEditListView.h"
#include "MdsEditView.h"
#include "MainFrm.h"
#include "rec.h"
#include "recType.h"
#include "Dir.h"
#include "CMDS.h"
#include "ModifyStringDlg.h"
#include "ModifyUint32Dlg.h"
#include "ModifyMultiUint32Dlg.h"
#include "resource.h"
#include <string.h>
#include "AppMemTrack.h"
#include "cssmMemTrack.h"
//#include "errMsgString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdsEditListView

IMPLEMENT_DYNCREATE(CMdsEditListView, CListView)

CMdsEditListView::CMdsEditListView()
{
}

CMdsEditListView::~CMdsEditListView()
{
}


BEGIN_MESSAGE_MAP(CMdsEditListView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CMdsEditListView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(ID_EDIT_MODIFY, OnEditModify)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MODIFY, OnUpdateEditModify)
	ON_COMMAND(ID_EDIT_EXPORTBLOB, OnEditExportBlob)
	ON_UPDATE_COMMAND_UI(ID_EDIT_EXPORTBLOB, OnUpdateEditExportBlob)
	ON_COMMAND(ID_EDIT_IMPORTBLOB, OnEditImportBlob)
	ON_UPDATE_COMMAND_UI(ID_EDIT_IMPORTBLOB, OnUpdateEditImportBlob)
	ON_COMMAND(ID_HACK_MODIFYEXPORT, OnHackModifyOrExport)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_FINDNEXT, OnEditFindNext)
	ON_WM_DESTROY()
	ON_COMMAND(ID_VIEW_BLOBASSTRING, OnViewBlobAsString)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BLOBASSTRING, OnUpdateViewBlobAsString)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMdsEditListView drawing

void CMdsEditListView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMdsEditListView diagnostics

#ifdef _DEBUG
void CMdsEditListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMdsEditListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMdsEditListView message handlers

void CMdsEditListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
}

BOOL CMdsEditListView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

BOOL CMdsEditListView::Populate(CRec *pRec)
{
	/*BOOL bStatus = */GetListCtrl().DeleteAllItems();

	m_pRec = pRec;

	if ( !pRec || !(pRec->m_pRecType) )
	{
		return FALSE;
	}

	for ( int i = 0; i < (int) pRec->m_pRecType->m_dwNumAttrs; i++ )
	{
		int iImage = 0;
		switch ( pRec->m_outputAttributeData[i].Info.AttributeFormat )
		{
		case CSSM_DB_ATTRIBUTE_FORMAT_STRING:
			iImage = IDXB_STRING;
			break;

		case CSSM_DB_ATTRIBUTE_FORMAT_UINT32:
		case CSSM_DB_ATTRIBUTE_FORMAT_SINT32:
			iImage = IDXB_UINT32;
			break;

		case CSSM_DB_ATTRIBUTE_FORMAT_MULTI_UINT32:
			iImage = IDXB_MULTI_UINT32;
			break;

		case CSSM_DB_ATTRIBUTE_FORMAT_BLOB:
			iImage = IDXB_BLOB;
			break;

		default:
			iImage = IDXB_ERROR;
			break;
		} //switch

		int iActualItem =
			GetListCtrl().InsertItem(
				i,
				pRec->m_outputAttributeData[i].Info.Label.AttributeName,
				iImage);
		if ( iActualItem != i )
		{
			AfxMessageBox( _T("Error Occurred While Populating List Control") );
			return FALSE;
		}

		GetListCtrl().SetItemText(
				iActualItem,
				1,
				(*pRec)[i]);

		CString strLength;
		strLength.Format(
			"%d",
			pRec->m_outputAttributeData[i].Value->Length);

		GetListCtrl().SetItemText(
				iActualItem,
				2,
				strLength);
	} //for

	GetListCtrl().SetItemState(
						0,								//int nItem,
						0xFFFFFFFF,						//UINT nState,
						LVIS_FOCUSED | LVIS_SELECTED);	//UINT nMask );
	return TRUE;
}

void CMdsEditListView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnHackModifyOrExport();
	*pResult = 0;
}

void CMdsEditListView::OnEditModify()
{
	int iPos = GetSelectedItemIndex();
	if ( iPos == 0 )
	{
		TRACE0("No items were selected!\n");
		return;
	}

	CDir *pDir = m_pRec->m_pRecType->m_pDir;
	CMDS *pMds = pDir->m_pMds;
	CSSM_DB_RECORDTYPE dwRecType = m_pRec->m_pRecType->m_dwRecType;

	int i = iPos - 1;
	switch ( m_pRec->m_outputAttributeData[i].Info.AttributeFormat )
	{
	case CSSM_DB_ATTRIBUTE_FORMAT_UINT32:
		{
			CModifyUint32Dlg modifyUint32Dlg;
			modifyUint32Dlg.m_strAttrName =
				m_pRec->m_outputAttributeData[i].Info.Label.AttributeName;

			CString strAttrValue;

			uint32 u32Value;
			if ( m_pRec->m_outputAttributeData[i].Value->Data )
			{
				u32Value =
					*((uint32 *) m_pRec->m_outputAttributeData[i].Value->Data);

				strAttrValue.Format( "%.8X", u32Value );
			}

			modifyUint32Dlg.m_strAttrValue = strAttrValue;

			if ( modifyUint32Dlg.DoModal() != IDOK )
			{
				return;
			}

			if ( modifyUint32Dlg.m_strAttrValue == strAttrValue )
			{
				return;
			}

			//modifyUint32Dlg.m_strAttrValue.Remove( ' ' ); VC6.0
			modifyUint32Dlg.m_strAttrValue.TrimLeft();

			if ( modifyUint32Dlg.m_strAttrValue.GetLength() == 0 )
			{
				CSSM_FREE_WRAPPER(pMds->m_memoryFunctions.free_func,
					m_pRec->m_outputAttributeData[i].Value->Data,
					pMds->m_memoryFunctions.AllocRef);

				m_pRec->m_outputAttributeData[i].Value->Data = NULL;
				m_pRec->m_outputAttributeData[i].Value->Length = 0;
			}
			else
			{
				if ( m_pRec->m_outputAttributeData[i].Value->Data == NULL )
				{
					m_pRec->m_outputAttributeData[i].Value->Length = 4;

					m_pRec->m_outputAttributeData[i].Value->Data =
						(uint8 *) CSSM_MALLOC_WRAPPER(
							pMds->m_memoryFunctions.malloc_func,
							m_pRec->m_outputAttributeData[i].Value->Length,
							pMds->m_memoryFunctions.AllocRef);
				}

				if ( m_pRec->m_outputAttributeData[i].Value->Data == NULL )
				{
					AfxThrowMemoryException();
				}

				sscanf(
					modifyUint32Dlg.m_strAttrValue,
					"%X",
					m_pRec->m_outputAttributeData[i].Value->Data );
			}
		}
		break;

	case CSSM_DB_ATTRIBUTE_FORMAT_STRING:
		{
			CModifyStringDlg modifyStringDlg;

			modifyStringDlg.m_strAttrName =
				m_pRec->m_outputAttributeData[i].Info.Label.AttributeName;

			if ( m_pRec->m_outputAttributeData[i].Value->Data == NULL )
			{
				modifyStringDlg.m_bValueIsNULL = TRUE;
			}
			else
			{
				modifyStringDlg.m_bValueIsNULL = FALSE;

				modifyStringDlg.m_strAttrValue =
					m_pRec->m_outputAttributeData[i].Value->Data;
			}

			if ( modifyStringDlg.DoModal() != IDOK )
			{
				return;
			}

			//exit if there is really no change necessary to MDS
			if ( modifyStringDlg.m_bValueIsNULL )
			{
				if ( m_pRec->m_outputAttributeData[i].Value->Data == NULL )
				{
					return;
				}
			}
			else
			{
				if (m_pRec->m_outputAttributeData[i].Value->Data &&
					(modifyStringDlg.m_strAttrValue ==
					 m_pRec->m_outputAttributeData[i].Value->Data))
				{
					return;
				}
			}

			//fix up m_pRec->m_outputAttributeData[i].Value
			if ( m_pRec->m_outputAttributeData[i].Value->Data )
			{
				CSSM_FREE_WRAPPER(pMds->m_memoryFunctions.free_func,
					m_pRec->m_outputAttributeData[i].Value->Data,
					pMds->m_memoryFunctions.AllocRef);

				m_pRec->m_outputAttributeData[i].Value->Data = NULL;
				m_pRec->m_outputAttributeData[i].Value->Length = 0;
			}

			ASSERT( m_pRec->m_outputAttributeData[i].Value->Data == NULL );

			if ( modifyStringDlg.m_bValueIsNULL == FALSE )
			{
				m_pRec->m_outputAttributeData[i].Value->Length =
					modifyStringDlg.m_strAttrValue.GetLength() + 1;

				m_pRec->m_outputAttributeData[i].Value->Data =
					(uint8 *) CSSM_MALLOC_WRAPPER(
						pMds->m_memoryFunctions.malloc_func,
						m_pRec->m_outputAttributeData[i].Value->Length,
						pMds->m_memoryFunctions.AllocRef);

				memcpy(
					m_pRec->m_outputAttributeData[i].Value->Data,
					modifyStringDlg.m_strAttrValue,
					m_pRec->m_outputAttributeData[i].Value->Length);
			}
		} //case CSSM_DB_ATTRIBUTE_FORMAT_STRING
		break;

	case CSSM_DB_ATTRIBUTE_FORMAT_MULTI_UINT32:
		{
			const int iMaxNumUint32 = 10;

			CModifyMultiUint32Dlg modifyMultiUint32Dlg;
			modifyMultiUint32Dlg.m_strAttrName =
				m_pRec->m_outputAttributeData[i].Info.Label.AttributeName;

			CString * dlgStrAttrValue[iMaxNumUint32] =
			{
				&modifyMultiUint32Dlg.m_strAttrValue0,
				&modifyMultiUint32Dlg.m_strAttrValue1,
				&modifyMultiUint32Dlg.m_strAttrValue2,
				&modifyMultiUint32Dlg.m_strAttrValue3,
				&modifyMultiUint32Dlg.m_strAttrValue4,
				&modifyMultiUint32Dlg.m_strAttrValue5,
				&modifyMultiUint32Dlg.m_strAttrValue6,
				&modifyMultiUint32Dlg.m_strAttrValue7,
				&modifyMultiUint32Dlg.m_strAttrValue8,
				&modifyMultiUint32Dlg.m_strAttrValue9
			};

			if ( m_pRec->m_outputAttributeData[i].Value->Length >iMaxNumUint32*4 )
			{
				AfxMessageBox( _T("The set of uint32 is too large for MDS Edit") );
			}

			if ( m_pRec->m_outputAttributeData[i].Value->Data )
			{
				for (uint32 j = 0;
					 j < m_pRec->m_outputAttributeData[i].Value->Length;
					 j+=4 )
				{
					uint32 u32Value =
						*((uint32 *) (m_pRec->m_outputAttributeData[i].Value->Data+j));

					dlgStrAttrValue[j/4]->Format( "%.8X", u32Value );
				}
			}

			if ( modifyMultiUint32Dlg.DoModal() != IDOK )
			{
				return;
			}

			uint32 u32DlgValue[iMaxNumUint32];
			memset( u32DlgValue, 0, sizeof(u32DlgValue) );
			uint32 k = 0;
			//construct the new CSSM_DATA
			for ( uint32 j = 0; j < iMaxNumUint32; j++ )
			{
				//dlgStrAttrValue[j]->Remove( ' ' ); VC6.0
				dlgStrAttrValue[j]->TrimLeft();

				if ( dlgStrAttrValue[j]->GetLength() > 0 )
				{
					sscanf( *dlgStrAttrValue[j], "%X", &u32DlgValue[k] );
					k++;
				}
			}

			CSSM_DATA cdData;
			cdData.Data = (uint8 *) u32DlgValue;
			cdData.Length = k * 4;
			if ((cdData.Length	== m_pRec->m_outputAttributeData[i].Value->Length) &&
				(memcmp(
					cdData.Data,
					m_pRec->m_outputAttributeData[i].Value->Data,
					cdData.Length) == 0))
			{
				return;
			}

			//modify m_pRec->m_outputAttributeData[i].Value.Data
			if ( m_pRec->m_outputAttributeData[i].Value->Data )
			{
				CSSM_FREE_WRAPPER(pMds->m_memoryFunctions.free_func,
					m_pRec->m_outputAttributeData[i].Value->Data,
					pMds->m_memoryFunctions.AllocRef);
				m_pRec->m_outputAttributeData[i].Value->Data = NULL;
				m_pRec->m_outputAttributeData[i].Value->Length = 0;
			}

			if ( cdData.Length > 0 )
			{
				m_pRec->m_outputAttributeData[i].Value->Length = cdData.Length;

				m_pRec->m_outputAttributeData[i].Value->Data =
					(uint8 *) CSSM_MALLOC_WRAPPER(
						pMds->m_memoryFunctions.malloc_func,
						m_pRec->m_outputAttributeData[i].Value->Length,
						pMds->m_memoryFunctions.AllocRef);

				memcpy(
					m_pRec->m_outputAttributeData[i].Value->Data,
					cdData.Data,
					m_pRec->m_outputAttributeData[i].Value->Length);
			}
		}
		break;

	default:
		TRACE("Don't Know How To Edit This RecordType\n");
		ASSERT(FALSE);
		return;
		break;
	} //switch

	/*CSSM_RETURN crStatus = */ModifyMds( dwRecType, i, pMds, pDir );
}

void CMdsEditListView::OnUpdateEditModify(CCmdUI* pCmdUI)
{
	int iPos = GetSelectedItemIndex();
	if ( iPos == 0 )
	{
		TRACE0("No items were selected!\n");
		pCmdUI->Enable( FALSE );
		return;
	}

	int i = iPos - 1;
	pCmdUI->Enable(
		m_pRec->m_outputAttributeData[i].Info.AttributeFormat !=
		CSSM_DB_ATTRIBUTE_FORMAT_BLOB);
}

int CMdsEditListView::GetSelectedItemIndex() const
{
	return 1+GetListCtrl().GetNextItem( -1, LVIS_SELECTED );
}

void CMdsEditListView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_MDS_EDIT_LIST_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CMdsEditListView::OnEditExportBlob()
{
	int iPos = GetSelectedItemIndex();
	if ( iPos == 0 )
	{
		TRACE0("No items were selected!\n");
		return;
	}

	int i = iPos - 1;
	CSSM_DATA &cdValue = *(m_pRec->m_outputAttributeData[i].Value);

	if ( (cdValue.Data == NULL) || (cdValue.Length == 0) )
	{
		AfxMessageBox( _T("There Is Nothing to Export") );
		return;
	}

	CFileDialog fileDialog(
					FALSE,
					_T("blb"),
					NULL,
					0,
					_T("Blob Data Files (*.blb)|*.blb|Electronic Shrink Wrappers (*.esw)|*.esw|All Files (*.*)|*.*||"));

	fileDialog.m_ofn.lpstrTitle = _T("Export Blob Attribute");
	fileDialog.m_ofn.Flags |= OFN_HIDEREADONLY;

	if ( strcmp(m_pRec->m_outputAttributeData[i].Info.Label.AttributeName, "Manifest") == 0 )
	{
		fileDialog.m_ofn.nFilterIndex = 2;
	}

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

	try
	{
		file.Write( cdValue.Data,cdValue.Length );
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

	file.Close();
}

void CMdsEditListView::OnUpdateEditExportBlob(CCmdUI* pCmdUI)
{
	int iPos = GetSelectedItemIndex();
	if ( iPos == 0 )
	{
		TRACE0("No items were selected!\n");
		pCmdUI->Enable( FALSE );
		return;
	}

	int i = iPos - 1;
	pCmdUI->Enable(
		m_pRec->m_outputAttributeData[i].Info.AttributeFormat ==
		CSSM_DB_ATTRIBUTE_FORMAT_BLOB);
}

void CMdsEditListView::OnEditImportBlob()
{
	int iPos = GetSelectedItemIndex();
	if ( iPos == 0 )
	{
		TRACE0("No items were selected!\n");
		return;
	}

	int i = iPos - 1;

	CFileDialog fileDialog(
					TRUE,
					_T("blb"),
					NULL,
					0,
					_T("Blob Data Files (*.blb)|*.blb|Electronic Shrink Wrappers (*.esw)|*.esw|All Files (*.*)|*.*||"));

	fileDialog.m_ofn.lpstrTitle = _T("Import Blob Attribute");
	fileDialog.m_ofn.Flags |= OFN_HIDEREADONLY;

	if ( strcmp(m_pRec->m_outputAttributeData[i].Info.Label.AttributeName, "Manifest") == 0 )
	{
		fileDialog.m_ofn.nFilterIndex = 2;
	}

	if ( fileDialog.DoModal() == IDCANCEL )
	{
		return;
	}

	CDir *pDir = m_pRec->m_pRecType->m_pDir;
	CMDS *pMds = pDir->m_pMds;
	CSSM_DB_RECORDTYPE dwRecType = m_pRec->m_pRecType->m_dwRecType;

	CString strPathName = fileDialog.GetPathName();
	CSSM_DATA &cdValue = *(m_pRec->m_outputAttributeData[i].Value);

	if ( cdValue.Data )
	{
		CSSM_FREE_WRAPPER(pMds->m_memoryFunctions.free_func,
							cdValue.Data,
							pMds->m_memoryFunctions.AllocRef);

		cdValue.Data = NULL;
		cdValue.Length = 0;
	}

	ASSERT(cdValue.Data == NULL);

	CFile	  file;
	if ( !file.Open(strPathName, CFile::modeRead) )
	{
		CString strStatus;
		strStatus.Format( _T("Cannot open %s for reading"), strPathName );
		AfxMessageBox( strStatus );
		return;
	}

	cdValue.Length = file.GetLength();
	if ( cdValue.Length )
	{
		cdValue.Data =
			(uint8 *) CSSM_MALLOC_WRAPPER(
							pMds->m_memoryFunctions.malloc_func,
							cdValue.Length,
							pMds->m_memoryFunctions.AllocRef);
		if ( cdValue.Data == NULL )
		{
			AfxThrowMemoryException();
		}

		file.Read( cdValue.Data, cdValue.Length );
	}

	CSSM_RETURN crStatus = ModifyMds( dwRecType, i, pMds, pDir );
	ASSERT(crStatus == CSSM_OK);

	file.Close();
}

void CMdsEditListView::OnUpdateEditImportBlob(CCmdUI* pCmdUI)
{
	int iPos = GetSelectedItemIndex();
	if ( iPos == 0 )
	{
		TRACE0("No items were selected!\n");
		pCmdUI->Enable( FALSE );
		return;
	}

	int i = iPos - 1;
	pCmdUI->Enable(
		m_pRec->m_outputAttributeData[i].Info.AttributeFormat ==
		CSSM_DB_ATTRIBUTE_FORMAT_BLOB);
}

CSSM_RETURN CMdsEditListView::ModifyMds(CSSM_DB_RECORDTYPE dwRecType,
										int i,
										CMDS *pMds,
										CDir *pDir)
{
	// fixme, is this the right mode?
	CSSM_DB_MODIFY_MODE mode = CSSM_DB_MODIFY_ATTRIBUTE_NONE;

	CSSM_RETURN crStatus =
		pMds->DataModify(
			pDir->m_hDb,
			dwRecType,
			m_pRec->m_recordId,
			&(m_pRec->m_outputAttributes),
			NULL,
			mode);
	if ( crStatus != CSSM_OK )
	{
		AfxMessageBox( _T("Modification Failed") );
		//REPORT_ERROR(crStatus,"modifying data");
		CMainFrame *pWnd = (CMainFrame *)AfxGetMainWnd();
		CMdsEditTreeView *pTreeView = pWnd->GetTreeView();
		pTreeView->Refresh();
		return crStatus;
	}

	GetListCtrl().SetItemText(
				i,
				1,
				(*m_pRec)[i]);

	CString strLength;
	strLength.Format(
		"%d",
		m_pRec->m_outputAttributeData[i].Value->Length);

	GetListCtrl().SetItemText(
			i,
			2,
			strLength);

	if ( i == 0 )
	{
		CMdsEditTreeView * pTreeView =
			((CMainFrame *) AfxGetMainWnd())->GetTreeView();
		pTreeView->UpdateSelectedRecordLabel( (*m_pRec)[i] );
	}

	return crStatus;
}

void CMdsEditListView::OnHackModifyOrExport()
{
	int iPos = GetSelectedItemIndex();
	if ( iPos == 0 )
	{
		TRACE0("No items were selected!\n");
		return;
	}

	//CDir *pDir = m_pRec->m_pRecType->m_pDir;
	//CMDS *pMds = pDir->m_pMds;
	//CSSM_DB_RECORDTYPE dwRecType = m_pRec->m_pRecType->m_dwRecType;

	int i = iPos - 1;
	if (m_pRec->m_outputAttributeData[i].Info.AttributeFormat ==
		CSSM_DB_ATTRIBUTE_FORMAT_BLOB)
	{
		if ( m_pRec->m_outputAttributeData[i].Value->Data )
		{
			OnEditExportBlob();
		}
		else
		{
			OnEditImportBlob();
		}
	}
	else
	{
		OnEditModify();
	}
}

int CMdsEditListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the Image List
	m_ctlImage.Create(IDB_ATTRIBUTE_IMAGELIST,16,0,RGB(255,0,255));
	m_ctlImage.SetBkColor(GetSysColor(COLOR_WINDOW));

	/// Attach image list to Tree
	GetListCtrl().SetImageList( &m_ctlImage, LVSIL_SMALL );

	// Setup  columns
	CMdsEditApp *pApp = (CMdsEditApp *) AfxGetApp();

	int iAttrNameColWidth =
		pApp->GetProfileInt(
			_T("Settings"),
			_T("AttrNameColWidth"),
			150);

	int iAttrValueDataColWidth =
		pApp->GetProfileInt(
			_T("Settings"),
			_T("AttrValueDataColWidth"),
			350);

	int iAttrValueLengthColWidth =
		pApp->GetProfileInt(
			_T("Settings"),
			_T("AttrValueLengthColWidth"),
			49);

	LVCOLUMN Col;
	Col.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
	Col.fmt = LVCFMT_LEFT;
	Col.cchTextMax = 0;

	Col.pszText	 = "Attribute Name";
	Col.iSubItem = IDXC_ATTRNAME;
	Col.cx		 = iAttrNameColWidth;
	GetListCtrl().InsertColumn( IDXC_ATTRNAME, &Col );

	Col.pszText	 = "Data";
	Col.iSubItem = IDXC_ATTRVALUEDATA;
	Col.cx		 = iAttrValueDataColWidth;
	GetListCtrl().InsertColumn( IDXC_ATTRVALUEDATA, &Col );

	Col.pszText	 = "Length";
	Col.iSubItem = IDXC_ATTRVALUELENGTH;
	Col.cx		 = iAttrValueLengthColWidth;
	GetListCtrl().InsertColumn( IDXC_ATTRVALUELENGTH, &Col );

	//other initializations
	CRec::s_bViewBlobAsString =
		pApp->GetProfileInt(
			_T("Settings"),
			_T("ViewBlobAsString"),
			FALSE);

//	CHeaderCtrl * pHdr = GetListCtrl().GetHeaderCtrl(); //VC6.0
	HWND hWndHeader = ListView_GetHeader( GetListCtrl().m_hWnd );
	CHeaderCtrl * pHdr = (CHeaderCtrl *) FromHandle( hWndHeader );
	pHdr->ModifyStyle( HDS_BUTTONS, 0 );

	return 0;
}

void CMdsEditListView::OnEditFindNext()
{
	int iItem = GetSelectedItemIndex();
	CMainFrame *pWnd = (CMainFrame *) AfxGetMainWnd();
	CMdsEditTreeView *pTreeView = pWnd->GetTreeView();

	int iNextItem =
		m_pRec->FindStringInRecord(
					pTreeView->m_find.m_strFind,
					pTreeView->m_find.m_bMatchWholeStringOnly,
					pTreeView->m_find.m_bMatchCase,
					pTreeView->m_find.m_bExamineAttrName,
					pTreeView->m_find.m_bExamineAttrValue,
					iItem );
	if ( iNextItem == -1 )
	{
		pTreeView->FindNext( pTreeView->m_hTreeItemNextSearchPos );
		return;
	}

	GetListCtrl().SetItemState(
						iNextItem,						//int nItem,
						0xFFFFFFFF,						//UINT nState,
						LVIS_FOCUSED | LVIS_SELECTED);	//UINT nMask );
}

void CMdsEditListView::OnDestroy()
{
	CListView::OnDestroy();

	CMdsEditApp *pApp = (CMdsEditApp *) AfxGetApp();

	int iWidth = GetListCtrl().GetColumnWidth( IDXC_ATTRNAME );
	pApp->WriteProfileInt(
		_T("Settings"),
		_T("AttrNameColWidth"),
		iWidth);

	iWidth = GetListCtrl().GetColumnWidth( IDXC_ATTRVALUEDATA );
	pApp->WriteProfileInt(
		_T("Settings"),
		_T("AttrValueDataColWidth"),
		iWidth);

	iWidth = GetListCtrl().GetColumnWidth( IDXC_ATTRVALUELENGTH );
	pApp->WriteProfileInt(
		_T("Settings"),
		_T("AttrValueLengthColWidth"),
		iWidth);

	pApp->WriteProfileInt(
			_T("Settings"),
			_T("ViewBlobAsString"),
			CRec::s_bViewBlobAsString);
}

void CMdsEditListView::OnViewBlobAsString()
{
	CRec::s_bViewBlobAsString = !CRec::s_bViewBlobAsString;

	if ( m_pRec )
	{
		Populate( m_pRec );
	}
}

void CMdsEditListView::OnUpdateViewBlobAsString(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( CRec::s_bViewBlobAsString );
	int i = GetSelectedItemIndex();
	pCmdUI->Enable(
		i > 0 &&
		(m_pRec->m_outputAttributeData[i-1].Info.AttributeFormat ==
		 CSSM_DB_ATTRIBUTE_FORMAT_BLOB));
}

void CMdsEditListView::OnEditDelete()
{
	if (AfxMessageBox(
			_T("Do You Really Want to Delete the Attribute Value?"),
			MB_YESNO) != IDYES )
	{
		return;
	}

	int iPos = GetSelectedItemIndex();
	if ( iPos == 0 )
	{
		TRACE0("No items were selected!\n");
		return;
	}

	int i = iPos - 1;

	CDir *pDir = m_pRec->m_pRecType->m_pDir;
	CMDS *pMds = pDir->m_pMds;
	//CSSM_DB_RECORDTYPE dwRecType = m_pRec->m_pRecType->m_dwRecType;

	CSSM_DATA &cdValue = *(m_pRec->m_outputAttributeData[i].Value);

	if ( cdValue.Data )
	{
		CSSM_FREE_WRAPPER(pMds->m_memoryFunctions.free_func,
							cdValue.Data,
							pMds->m_memoryFunctions.AllocRef);

		cdValue.Data = NULL;
		cdValue.Length = 0;
	}

	ASSERT(cdValue.Data == NULL);

	CSSM_RETURN crStatus =
		ModifyMds(
			m_pRec->m_pRecType->m_dwRecType,
			i,
			pMds,
			pDir);

	ASSERT(crStatus == CSSM_OK);
}
