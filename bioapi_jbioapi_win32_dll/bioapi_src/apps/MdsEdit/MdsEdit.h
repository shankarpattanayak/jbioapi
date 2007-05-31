/*-----------------------------------------------------------------------
 * File: MDSEDIT.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// MdsEdit.h : main header file for the MDSEDIT application
//

#if !defined(AFX_MDSEDIT_H__ED147A19_6BBD_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_MDSEDIT_H__ED147A19_6BBD_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
//#include "bioapi_type.h"
#include "cssmtype.h"

#include "mds.h"
#include "bioapi.h"
#include "mds_util.h"
#include "bsp_schema.h"
#include "device_schema.h"

//#include "bioapi_err.h"
#include "cssmerr.h"
#include "mds_schema.h"
#include "CMDSUtil.h"

/////////////////////////////////////////////////////////////////////////////
// CMdsEditApp:
// See MdsEdit.cpp for the implementation of this class
//

class CMdsEditApp : public CWinApp
{
public:
	CMdsEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdsEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMdsEditApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDSEDIT_H__ED147A19_6BBD_11D2_A091_00A0C90988EF__INCLUDED_)
