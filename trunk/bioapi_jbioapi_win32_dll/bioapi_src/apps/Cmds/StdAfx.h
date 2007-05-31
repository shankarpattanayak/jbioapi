/*-----------------------------------------------------------------------
 * File: STDAFX.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


// stdafx.h : include file for standard system include files,
//	or project specific include files that are used frequently, but
//		are changed infrequently
//

#if !defined(AFX_STDAFX_H__9253E7E5_6BEE_11D2_A091_00A0C90988EF__INCLUDED_)
#define AFX_STDAFX_H__9253E7E5_6BEE_11D2_A091_00A0C90988EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>

// TODO: reference additional headers your program requires here
#include <afxtempl.h>

#include "cssmtype.h"
#include "mds.h"
#include "bioapi.h"
#include "bsp_schema.h"
#include "device_schema.h"

#include "cssmerr.h"
#include "mds_schema.h"
#include "CMDSUtil.h"
#include "RecType.h"

#ifdef _DEBUG
#define ASSERTVALID()	AssertValid()
#else
#define ASSERTVALID()
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9253E7E5_6BEE_11D2_A091_00A0C90988EF__INCLUDED_)
