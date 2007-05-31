/*-----------------------------------------------------------------------
 * File: DL_MISC.C
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


/*
 * This file contains misc. utility functions for DL modules to use
 */

#include "dlutil.h"
#include "cssmmemtrack.h"

#define GET_FUNC(Name, member) \
	if( Addin_GetProcAddress( CSSMModulePtr, Name, (CSSM_PROC_ADDR *)&(pDLUtilFuncs->member) ) != CSSM_OK ) { \
		return CSSMERR_DL_INTERNAL_ERROR; \
	}

CSSM_RETURN dl_GetCSSMAPIFuncPtrs(
	ADDIN_MODULE_HANDLE CSSMModulePtr,
	DLUTIL_CSSM_FUNCTIONS * pDLUtilFuncs)
{
	GET_FUNC("CSSM_ModuleAttach", ModuleAttach);
	GET_FUNC("CSSM_ModuleLoad", ModuleLoad);
	GET_FUNC("CSSM_ModuleDetach", ModuleDetach);
	GET_FUNC("CSSM_ModuleUnload", ModuleUnload);
	GET_FUNC("CSSM_GetAPIMemoryFunctions", GetAPIMemoryFunctions);
	GET_FUNC("CSSM_CL_CertGetFirstFieldValue", cl_CertGetFirstFieldValue);
	GET_FUNC("CSSM_CL_CertGetNextFieldValue", cl_CertGetNextFieldValue);
	GET_FUNC("CSSM_CL_CertAbortQuery", cl_CertAbortQuery);
	GET_FUNC("CSSM_CL_CertGetAllFields", cl_CertGetAllFields);
	GET_FUNC("CSSM_CL_CrlGetFirstFieldValue", cl_CrlGetFirstFieldValue);
	GET_FUNC("CSSM_CL_CrlGetNextFieldValue", cl_CrlGetNextFieldValue);
	GET_FUNC("CSSM_CL_CrlAbortQuery", cl_CrlAbortQuery);
	GET_FUNC("CSSM_CL_FreeFieldValue", cl_FreeFieldValue);

	/********************************************************************************
	 * assert: all API function pointers specified in dlutil.h have been successfully
	 *				 imported
	 ********************************************************************************/
	return CSSM_OK;
}
