/*-----------------------------------------------------------------------
 * File: MDSEDIT.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// MdsEdit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MdsEdit.h"

#include "MainFrm.h"
#include "MdsEditDoc.h"
#include "MdsEditView.h"
#include "AppMemTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdsEditApp

BEGIN_MESSAGE_MAP(CMdsEditApp, CWinApp)
	//{{AFX_MSG_MAP(CMdsEditApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMdsEditApp construction

CMdsEditApp::CMdsEditApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMdsEditApp object

CMdsEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMdsEditApp initialization

BOOL CMdsEditApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//	of your final executable, you should remove from the following
	//	the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Intel"));

	LoadStdProfileSettings(0);	// Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//	serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMdsEditDoc),
		RUNTIME_CLASS(CMainFrame),		 // main SDI frame window
		RUNTIME_CLASS(CMdsEditTreeView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.

	if ( ((CMainFrame *)m_pMainWnd)->m_bIsZoomedInitially )
	{
		m_pMainWnd->ShowWindow( SW_SHOWMAXIMIZED );
	}
	else
	{
		m_pMainWnd->ShowWindow(SW_SHOW);
	}
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
// this little class should be split out into a separate library,
// but we'll compile it in line here
class CVersionInfo
{

public:
	BOOL GetVersionInfo(char* fileName);

	CString m_productVersion;
	CString m_copyright;
	CString m_description;

};

BOOL CVersionInfo::GetVersionInfo(char* fileName)
{
	DWORD temp;
	DWORD size;

	size = GetFileVersionInfoSize(fileName,&temp);

	unsigned char* buffer = (unsigned char*)malloc(size);

	if( ! GetFileVersionInfo(fileName,
							0,
							size,
							buffer))
	{
		free(buffer);
		return FALSE;
	}
	else
	{
		unsigned int valueSize;
		char* pValue;

		VerQueryValue(buffer,
					TEXT("\\StringFileInfo\\040904b0\\ProductVersion"),
					(void**)&pValue,
					&valueSize);


		m_productVersion = pValue;

		VerQueryValue(buffer,
					TEXT("\\StringFileInfo\\040904b0\\LegalCopyright"),
					(void**)&pValue,
					&valueSize);


		m_copyright = pValue;

		VerQueryValue(buffer,
					TEXT("\\StringFileInfo\\040904b0\\FileDescription"),
					(void**)&pValue,
					&valueSize);


		m_description = pValue;

	}

	free(buffer);
	return TRUE;
}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString m_appName;
	CString m_copyright;
	CString m_version;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_appName = _T("");
	m_copyright = _T("");
	m_version = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_APPNAME, m_appName);
	DDX_Text(pDX, IDC_COPYRIGHT, m_copyright);
	DDX_Text(pDX, IDC_VERSION, m_version);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMdsEditApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMdsEditApp message handlers

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

CVersionInfo info;
	char filename[1024];


	/*DWORD l = */GetModuleFileName( NULL,
							filename,
							1024);


	if(info.GetVersionInfo(filename))
	{
		m_version = info.m_productVersion;
		m_appName = info.m_description;
		m_copyright = info.m_copyright;
	}
	else
	{
		m_version = "2.1.0";
		m_appName = "MDS Edit";
		m_copyright = "Copyright © 1995-2000 Intel Corporation";
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
