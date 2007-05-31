/*-----------------------------------------------------------------------
 * File: DAL_CALLOUTS.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


/*
 * This file contains module management functions for the DLM
 */

#if defined(_DEBUG) && defined(WIN32)
#undef new
#include <crtdbg.h>
static char s_szFileName[] = __FILE__;
#define new new(_NORMAL_BLOCK, s_szFileName, __LINE__)
#endif

/* DL include files */
#define DEFINE_FAILURE_ERROR_CODES
#define DAL_SOURCE_FILE
#include "dal_classes.h"
#include "dal_src.h"
#include "maf_config.h"
#include "maf_integ.h"
#include "maf_collectn.h"
#include "maf_interface.h"
#include "maf_callouts.h"

#include "dlutil.h"
#include <cssmMemTrack.h>

#include "mds_util_api.h"

#ifdef _DEBUG
static int g_debug_fInitialized = 0;
#endif

/*-----------------------------------------------------------------------------
 * Name: Addin_callout_Initialize
 *
 * Description:
 * Preforms initialization that takes places when the module is loaded into
 * the process space
 *
 * Parameters:
 * None
 *
 * Return Code:
 * CSSM_OK if successful, otherwise Error
 *---------------------------------------------------------------------------*/
CSSM_RETURN
Addin_callout_Initialize(void)
{
#ifdef _DEBUG
	g_debug_fInitialized = 1;
#endif
	return dlbe_Initialize();
}

/*-----------------------------------------------------------------------------
 * Name: Addin_callout_Terminate
 *
 * Description:
 * Terminates state before the module is unloaded from the process space
 *
 * Parameters:
 * None.
 *
 * Return Code:
 * CSSM_OK if successful, otherwise Error
 *---------------------------------------------------------------------------*/
CSSM_RETURN
Addin_callout_Terminate(void)
{
#ifdef _DEBUG
	g_debug_fInitialized = 0;
#endif
	return dlbe_Uninitialize();
}

/*-----------------------------------------------------------------------------
 * Name: Addin_callout_LoadDataConstruct
 *
 * Description:
 * Constructs a ADDIN_LOAD_DATA structure and initializes it.
 * This function was ment to be the place where any CSSM Functions
 * that need to be imported could be imported
 *
 * Parameters:
 * hCssm (input) : Handle to the current CSSM Module, this handle can
 * be used to do a GetProcAddress
 * pAddinLoadData (ouput) :variable in which ADDIN_LOAD_DATA strcuture will
 * be constructed and initialized.
 *
 * Note:
 * If this function fails, Addin_callout_LoadDataDestroy will still be called
 *
 * Return Code:
 * CSSM_OK if successful, otherwise Error
 *---------------------------------------------------------------------------*/
CSSM_RETURN Addin_callout_LoadDataConstruct(
						ADDIN_MODULE_HANDLE hCssm,
						ADDIN_LOAD_DATA * pAddinLoadData )
{
	memset(pAddinLoadData, 0, sizeof(ADDIN_LOAD_DATA));
	return dl_GetCSSMAPIFuncPtrs(hCssm, pAddinLoadData);
}

/*-----------------------------------------------------------------------------
 * Name: Addin_callout_LoadDataDestroy
 *
 * Description:
 * Constructs a ADDIN_LOAD_DATA structure
 *
 * Parameters:
 * pAddinLoadData (output) : ADDIN_LOAD_DATA structure to destroy
 *
 * Return Code:
 * none
 *---------------------------------------------------------------------------*/
void Addin_callout_LoadDataDestroy(ADDIN_LOAD_DATA * pAddinLoadData)
{
	memset(pAddinLoadData, 0, sizeof(ADDIN_LOAD_DATA));
}

/*-----------------------------------------------------------------------------
 * Name: Addin_callout_AttachDataConstruct
 *
 * Description:
 * Constructs a ADDIN_ATTACH_DATA structure
 *
 * Parameters:
 * pAddinAttachData (output) : variable to initialize
 *
 * Note:
 * If this function fails, Addin_callout_AttachDataDestroy will still be called
 *
 * Return Code:
 * CSSM_OK if successful, otherwise Error
 *---------------------------------------------------------------------------*/
CSSM_RETURN
Addin_callout_AttachDataConstruct(ADDIN_ATTACH_DATA * pAddinAttachData)
{
	CSSM_RETURN retValue;

	pAddinAttachData->pDatabaseList = new DAL_DATABASE_INFO_LIST;

	if ((retValue = pAddinAttachData->pDatabaseList->Initialize()) != CSSM_OK)
		return retValue;

	return CSSM_OK;
}

/*-----------------------------------------------------------------------------
 * Name: Addin_callout_AttachDataDestroy
 *
 * Description:
 * Constructs a ADDIN_ATTACH_DATA structure
 *
 * Parameters:
 * pAddinAttachData (output) : ADDIN_ATTACH_DATA structure to destroy
 *
 * Return Code:
 * none
 *---------------------------------------------------------------------------*/
void Addin_callout_AttachDataDestroy(ADDIN_ATTACH_DATA * pAddinAttachData)
{
	ASSERT(pAddinAttachData->pDatabaseList);
	delete pAddinAttachData->pDatabaseList;
}

/*-----------------------------------------------------------------------------
 * Name: Addin_callout_ModuleAttach
 *
 * Description:
 * Functions is called to indicate that a module attach has been reqested.
 *
 * Parameters:
 * pLoadTracker (input/output) : An initialized load tracker, the ADDIN_LOAD_DATA
 * structure can be modified
 * pAttachTracker (input/output) : An construcuted attach tracker, the ADDIN_ATTACH_DATA
 * structure can be modified
 * FuncTbl (outpt) : Buffer to hold the SPI functions that the addin wants to
 * register with CSSM
 *
 * Return Code:
 * CSSM_OK if successful, otherwise Error
 *---------------------------------------------------------------------------*/
CSSM_RETURN Addin_callout_ModuleAttach(
	MAF_MODULE_LOAD_TRACKER_PTR pLoadTracker,
	MAF_MODULE_ATTACH_TRACKER_PTR pAttachTracker,
	CSSM_MODULE_FUNCS_PTR *FuncTbl )
{
	pLoadTracker;
	pAttachTracker;

	/* The size of the buffer is the size of the header + the size needed to store the dl functions */
	static CSSM_MODULE_FUNCS FunctionList;
	static CSSM_SPI_DL_FUNCS DlFuncs;
	CSSM_SPI_DL_FUNCS_PTR pDlFunctions;


	/* Assign the pointers */
	*FuncTbl = &FunctionList;
	FunctionList.ServiceFuncs = (CSSM_PROC_ADDR *)&DlFuncs;
	pDlFunctions = (CSSM_SPI_DL_FUNCS_PTR)FunctionList.ServiceFuncs;

	/* Fill out the header */
	FunctionList.ServiceType = CSSM_SERVICE_DL;
	FunctionList.NumberOfServiceFuncs = sizeof(CSSM_SPI_DL_FUNCS) / sizeof(CSSM_PROC_ADDR);

	/* Fill in the function table */
	pDlFunctions->DbOpen = DL_DbOpen;
	pDlFunctions->DbClose = DL_DbClose;
	pDlFunctions->DbCreate = DL_DbCreate;
	pDlFunctions->DbDelete = DL_DbDelete;
	pDlFunctions->CreateRelation = DL_CreateRelation;
	pDlFunctions->DestroyRelation = DL_DestroyRelation;
	pDlFunctions->Authenticate = NULL;
	pDlFunctions->GetDbNames = DL_GetDbNames;
	pDlFunctions->GetDbNameFromHandle = DL_GetDbNameFromHandle;
	pDlFunctions->FreeNameList = DL_FreeNameList;
	pDlFunctions->DataInsert = DL_DataInsert;
	pDlFunctions->DataDelete = DL_DataDelete;
	pDlFunctions->DataModify = DL_DataModify;
	pDlFunctions->DataGetFirst = DL_DataGetFirst;
	pDlFunctions->DataGetNext = DL_DataGetNext;
	pDlFunctions->DataAbortQuery = DL_DataAbortQuery;
	pDlFunctions->DataGetFromUniqueRecordId = DL_DataGetFromUniqueRecordId;
	pDlFunctions->FreeUniqueRecord = DL_FreeUniqueRecord;
#if USE_DL_PASSTHROUGH
	pDlFunctions->PassThrough = DL_PassThrough;
#else
	pDlFunctions->PassThrough = NULL;
#endif
	pDlFunctions->GetDbAcl = NULL;
	pDlFunctions->ChangeDbAcl = NULL;
	pDlFunctions->GetDbOwner = NULL;
	pDlFunctions->ChangeDbOwner = NULL;

	return CSSM_OK;
}

/*-----------------------------------------------------------------------------
 * Name: Addin_callout_ModuleLoad
 *
 * Description:
 * Call used to indicate that the application has requested a module load
 *
 * Parameters:
 * pLoadTracker (input/output) : The load tracker node that was created. This
 * node may be writen to.
 * CssmNotifyCallback (input) : Callback function to indicate to CSSM that
 * a subservice is ready for attach (must be called before an attach can occurr).
 * CssmNotifyCallbackCtx (input) : Opaque data to pass to the callback function.
 *
 * Return Code:
 * CSSM_OK if successful, otherwise Error
 *---------------------------------------------------------------------------*/
CSSM_RETURN Addin_callout_ModuleLoad(
	MAF_MODULE_LOAD_TRACKER_PTR pLoadTracker,
	CSSM_SPI_ModuleEventHandler CssmNotifyCallback,
	const void* CssmNotifyCallbackCtx)
{
	pLoadTracker;

	return CssmNotifyCallback(&MODULE_GUID, (void *)CssmNotifyCallbackCtx, 0, CSSM_SERVICE_DL,
		CSSM_NOTIFY_INSERT);
}

/*-----------------------------------------------------------------------------
 * Name: Addin_callout_ModuleUnload
 *
 * Description:
 * Function is called as part of the unload process to give indication to the
 * addin.
 *
 * Parameters:
 * pLoadTracker (input/output) : The load tracker node that was created. This
 * node may be writen to.
 * CssmNotifyCallback (input) : Identifies the corresponding ModuleLoad call
 * CssmNotifyCallbackCtx (input) : Identifies the corresponding ModuleLoad call
 *
 * Note:
 * There is no need to call the callback function on unload.
 *
 * Return Code:
 * CSSM_OK if successful, otherwise Error
 *---------------------------------------------------------------------------*/
CSSM_RETURN Addin_callout_ModuleUnload(
	MAF_MODULE_LOAD_TRACKER_PTR pLoadTracker,
	CSSM_SPI_ModuleEventHandler CssmNotifyCallback,
	const void* CssmNotifyCallbackCtx)
{
	pLoadTracker;
	CssmNotifyCallback;
	CssmNotifyCallbackCtx;

	return CSSM_OK;
}


CSSM_RETURN dal_CSSM_GetAPIMemoryFunctions (CSSM_HANDLE AddInHandle, CSSM_API_MEMORY_FUNCS_PTR MemFuncs)
{
	const ADDIN_LOAD_DATA * pLoadData = Addin_GetLoadData();

	ASSERT(pLoadData && CSSM_FALSE == port_IsBadCodePtr((CSSM_PROC_ADDR)pLoadData->GetAPIMemoryFunctions));

	if (pLoadData == NULL || pLoadData->GetAPIMemoryFunctions == NULL)
		return CSSMERR_DL_INTERNAL_ERROR;

	return pLoadData->GetAPIMemoryFunctions(AddInHandle,MemFuncs);
}

CSSM_MODULE_HANDLE dal_CSSM_ModuleLoadAndAttach (
	const CSSM_SUBSERVICE_UID * pSubserviceUid,
	const CSSM_API_MEMORY_FUNCS * MemoryFuncs)
{
	CSSM_MODULE_HANDLE ModuleHandle = CSSM_INVALID_HANDLE;
	const ADDIN_LOAD_DATA * pLoadData = Addin_GetLoadData();

	ASSERT(pLoadData);
	ASSERT(CSSM_FALSE == port_IsBadCodePtr((CSSM_PROC_ADDR)pLoadData->ModuleAttach));
	ASSERT(CSSM_FALSE == port_IsBadCodePtr((CSSM_PROC_ADDR)pLoadData->ModuleLoad));

	if (pLoadData == NULL || pLoadData->ModuleLoad == NULL || pLoadData->ModuleAttach == NULL)
		return CSSM_INVALID_HANDLE;

	/* TODO - fix this to do the right thing */
	if (CSSM_OK != pLoadData->ModuleLoad(
		&pSubserviceUid->Guid, /* GUID */
		CSSM_KEY_HIERARCHY_NONE, /* KeyHierarchy */
		NULL, /* AppNotifyCallback */ /* TODO - fix */
		NULL/* AppCallbackCtx */ /* TODO - fix */
		))
	{
		return CSSM_INVALID_HANDLE;
	}

	if (CSSM_OK != pLoadData->ModuleAttach(
					(CSSM_GUID_PTR)&pSubserviceUid->Guid, /* GUID */
					(CSSM_VERSION_PTR)&pSubserviceUid->Version, /* Version */
					(CSSM_API_MEMORY_FUNCS *)MemoryFuncs, /* MemoryFuncs */
					pSubserviceUid->SubserviceId, /* SubserviceID */
					pSubserviceUid->SubserviceType, /* SubserviceType */
					0, /* AttachFlags */
					CSSM_KEY_HIERARCHY_NONE, /* KeyHierarchy */
					NULL, /* FunctionTable */
					0, /* NumFunctionTable */
					NULL, /* Reserved */
					&ModuleHandle /*NewModuleHandle */
					))
	{
		return CSSM_INVALID_HANDLE;
	}

	return ModuleHandle;
}

CSSM_RETURN dal_CSSM_ModuleDetachAndUnload (CSSM_MODULE_HANDLE ModuleHandle, const CSSM_GUID * pGuid)
{
	const ADDIN_LOAD_DATA * pLoadData = Addin_GetLoadData();

	ASSERT(pLoadData);
	ASSERT(CSSM_FALSE == port_IsBadCodePtr((CSSM_PROC_ADDR)pLoadData->ModuleUnload));
	ASSERT(CSSM_FALSE == port_IsBadCodePtr((CSSM_PROC_ADDR)pLoadData->ModuleDetach));

	if (pLoadData == NULL || pLoadData->ModuleUnload == NULL || pLoadData->ModuleDetach == NULL)
		return CSSMERR_DL_INTERNAL_ERROR;

	CSSM_RETURN retCode;
	if ((retCode = pLoadData->ModuleDetach(ModuleHandle)) != CSSM_OK)
		return retCode;

	return pLoadData->ModuleUnload(pGuid, NULL, NULL);
}
