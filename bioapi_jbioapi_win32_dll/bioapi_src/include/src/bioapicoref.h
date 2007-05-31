/*-----------------------------------------------------------------------
 * File: bioapicoref.h
 *
 *-----------------------------------------------------------------------
 */

/* Function declarations for the BioAPI Framework module. The
 * BioAPI_DEFINE_FUNC macro must be defined by the file that includes this header.
 */

/* Check to make sure that all macros were defined */
#ifndef BioAPI_DEFINE_FUNCTION
#error "The BioAPI_DEFINE_FUNCTION(name,params) macro must be defined!"
#endif

/*************************************************************************/
/*** Function declarations ***********************************************/
/*************************************************************************/

BioAPI_DEFINE_FUNCTION( Init, (
						const BioAPI_VERSION *Version,
						uint32 Reserved1,
						const void *Reserved2,
						uint32 Reserved3,
						const void *Reserved4 ) );

BioAPI_DEFINE_FUNCTION( Terminate, (
						void ) );

BioAPI_DEFINE_FUNCTION( ModuleLoad, (
						const BioAPI_UUID *ModuleGuid,
						uint32 Reserved,
						BioAPI_ModuleEventHandler AppNotifyCallback,
						void *AppNotifyCallbackCtx ) );

BioAPI_DEFINE_FUNCTION( ModuleUnload, (
						const BioAPI_UUID *ModuleGuid,
						BioAPI_ModuleEventHandler AppNotifyCallback,
						void *AppNotifyCallbackCtx ) );

BioAPI_DEFINE_FUNCTION( ModuleAttach, (
						const BioAPI_UUID *ModuleGuid,
						const BioAPI_VERSION *Version,
						const BioAPI_MEMORY_FUNCS *MemoryFuncs,
						uint32 DeviceID,
						uint32 Reserved1,
						uint32 Reserved2,
						uint32 Reserved3,
						BioAPI_FUNC_NAME_ADDR *FunctionTable,
						uint32 NumFunctionTable,
						const void *Reserved4,
						BioAPI_HANDLE_PTR NewModuleHandle ) );

BioAPI_DEFINE_FUNCTION( ModuleDetach, (
						BioAPI_HANDLE ModuleHandle ) );

BioAPI_DEFINE_FUNCTION( QueryDevice, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_SERVICE_UID_PTR ServiceUID ) );