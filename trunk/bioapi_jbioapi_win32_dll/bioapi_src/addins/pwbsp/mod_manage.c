/*-----------------------------------------------------------------------
 * File: mod_manage.c
 *-----------------------------------------------------------------------
 */

/*
 * This file implements the module management functions for a BioAPI addin based
 * on MAF.
 */


#include "precomp.h"
#include <time.h>

/* Declare the custom attach functions for hrs service.
 * Function is defined in hrspwbspi.c; however, the
 * definition of Addin_callout_ModuleAttach below requires
 * its declaration here. */
BioAPI_RETURN SPI_ModuleAttach(BioAPI_MODULE_FUNCS_PTR *FuncTbl);

#if ADDIN_NEED_ADDIN_LOAD_STRUCT
/*-----------------------------------------------------------------------------
 * Name: Addin_callout_LoadDataConstruct
 *
 * Description:
 * Constructs and populates the custom ADDIN_LOAD_DATA struct provided by
 * the MAF load tracker.  For this BSP, the function attaches a CSP and saves
 * the handle for use later when hashing and verifying passwords.
 *
 * Parameters:
 * pAddinLoadData (output) : data struct to initialize
 *
 * Note:
 * If this function fails, Addin_callout_LoadDataDestroy will still be
 * called.
 *
 * Return Code:
 * BioAPI_OK if successful, BioAPI_FAIL otherwise.
 *---------------------------------------------------------------------------*/
BioAPI_RETURN Addin_callout_LoadDataConstruct( BioAPI_HANDLE hFramework,
											 ADDIN_LOAD_DATA *	 pAddinLoadData )
{
	BioAPI_RETURN retVal;


	/* Initialize the fields of the ADDIN_LOAD_DATA to zero */
	port_memset((void*)pAddinLoadData, 0, sizeof(ADDIN_LOAD_DATA));
	retVal = BioAPI_OK;


	return retVal;
}


/*-------------------------------------------------------------------------
 * Name: Addin_callout_LoadDataDestroy
 *
 * Description:
 * Destructs a ADDIN_LOAD_DATA structure
 *
 * Parameters:
 * pAddinLoadData (output) : ADDIN_LOAD_DATA structure to destroy
 *
 * Return Code:
 * none
 *-------------------------------------------------------------------------
 */
void Addin_callout_LoadDataDestroy( ADDIN_LOAD_DATA * pAddinLoadData )
{
	/* Detach and unload CSP, and release the framework */
	/* TODO Add detach code here */
}

#endif


/*-------------------------------------------------------------------------
 * Name: Addin_callout_AttachDataConstruct
 *
 * Description:
 * Constructs and populates the custom ADDIN_ATTACH_DATA struct provided
 * by the MAF attach tracker.  For this BSP, the function initializes
 * a list of BIRs and a counter used to give the newly created BIRs their
 * handles.
 *
 * Parameters:
 * pAddinAttachData (output) : data struct to initialize
 *
 * Note:
 * If this function fails, Addin_callout_AttachDataDestroy will still be
 * called
 *
 * Return Code:
 * BioAPI_OK if successful, otherwise BioAPI_FAIL
 *-------------------------------------------------------------------------
 */
BioAPI_RETURN
Addin_callout_AttachDataConstruct(ADDIN_ATTACH_DATA * pAddinAttachData )
{
	pAddinAttachData->BIRList	  = NULL;
	pAddinAttachData->HandleIndex = 1;

	return BioAPI_OK;
}


/*-------------------------------------------------------------------------
 * Name: Addin_callout_AttachDataDestroy
 *
 * Description:
 * Deconstructs the addin's attach data struct.	 In this BSP,
 * this deallocates memory used for the list of BIRs residing in the
 * addin's memory space.
 *
 * Parameters:
 * pAddinAttachData (output) : ADDIN_ATTACH_DATA structure to destroy
 *
 * Return Code:
 * none
 *-------------------------------------------------------------------------
 */
void Addin_callout_AttachDataDestroy(ADDIN_ATTACH_DATA * pAddinAttachData )
{
	BIR_LIST_NODE* pNodeToFree;

	while (pAddinAttachData->BIRList != NULL)
	{
		pNodeToFree = pAddinAttachData->BIRList;
		pAddinAttachData->BIRList = (BIR_LIST_NODE*)pNodeToFree->NextNode;
		BioAPI_free(pNodeToFree->BIR.BiometricData,	NULL);
		BioAPI_free(pNodeToFree, NULL);
	}
}



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
 * BioAPI_OK if successful, otherwise BioAPI_FAIL
 *---------------------------------------------------------------------------*/

BioAPI_RETURN
Addin_callout_Initialize(void)
{
	return BioAPI_OK;
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
 * BioAPI_OK if successful, otherwise BioAPI_FAIL
 *---------------------------------------------------------------------------*/

BioAPI_RETURN
Addin_callout_Terminate(void)
{
	return BioAPI_OK;
}



/*-------------------------------------------------------------------------
 * Name: Addin_callout_ModuleLoad
 *
 * Description:
 * Call used to indicate that the application has requested a module load
 *
 * Parameters:
 * pLoadTracker (input/output) : The load tracker node that was created.
 *	This node may be writen to.
 * BioAPINotifyCallback (input) : Callback function to indicate to the
 *  framework that a subservice is ready for attach (must be called before
 *  an attach can occur).
 * BioAPINotifyCallbackCtx (input) : Opaque data to pass to the callback
 *	function.
 *
 * Return Code:
 * BioAPI_OK if successful, otherwise BioAPI_FAIL
 *-------------------------------------------------------------------------
 */

BioAPI_RETURN
Addin_callout_ModuleLoad(MAF_MODULE_LOAD_TRACKER_PTR pLoadTracker,
						 BioSPI_ModuleEventHandler BioAPINotifyCallback,
						 const void* BioAPINotifyCallbackCtx)
{
	BioAPI_RETURN ret = BioAPI_OK;

	ERR(ret = BioAPINotifyCallback(&BSP_UUID,
								 (void *)BioAPINotifyCallbackCtx,
								 0,
								 0,/* reserver */
								 BioAPI_NOTIFY_INSERT));
	return ret;
}



/*-------------------------------------------------------------------------
 * Name: Addin_callout_ModuleUnload
 *
 * Description:
 * Function is called as part of the unload process to give indication to
 * the addin.
 *
 * Parameters:
 * pLoadTracker (input/output) : The load tracker node that was created.
 *	This node may be written to.
 * BioAPINotifyCallback (input) : Identifies the corresponding ModuleLoad
 *	call BioAPINotifyCallbackCtx (input) : Identifies the corresponding
 *	ModuleLoad call
 *
 * Note:
 * There is no need to call the callback function on unload.
 *
 * Return Code:
 * BioAPI_OK if successful, otherwise BioAPI_FAIL
 *-------------------------------------------------------------------------
 */

BioAPI_RETURN Addin_callout_ModuleUnload(
						MAF_MODULE_LOAD_TRACKER_PTR pLoadTracker,
						BioSPI_ModuleEventHandler BioAPINotifyCallback,
						const void* BioAPINotifyCallbackCtx )
{
	return BioAPI_OK;
}



/*-------------------------------------------------------------------------
 * Name: Addin_callout_ModuleAttach
 *
 * Description:
 * Functions is called to indicate that a module attach has been reqested.
 *
 * Parameters:
 * pLoadTracker (input/output) : An initialized load tracker, the
 *	ADDIN_LOAD_DATA structure can be modified
 * pAttachTracker (input/output) : An construcuted attach tracker, the
 *	ADDIN_ATTACH_DATA structure can be modified
 * FuncTbl (outpt) : Buffer to hold the SPI functions that the addin wants
 * to register with BioAPI
 *
 * Return Code:
 * BioAPI_OK if successful, otherwise BioAPI_FAIL
 *-------------------------------------------------------------------------
 */

BioAPI_RETURN Addin_callout_ModuleAttach(
						MAF_MODULE_LOAD_TRACKER_PTR pLoadTracker,
						MAF_MODULE_ATTACH_TRACKER_PTR pAttachTracker,
						BioAPI_MODULE_FUNCS_PTR *FuncTbl )
{
	if (!pAttachTracker)
	{
		return BioAPI_ERRCODE_INVALID_POINTER;
	}
	else
	{
		return SPI_ModuleAttach(FuncTbl);
	}
}
