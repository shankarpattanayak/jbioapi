/*-----------------------------------------------------------------------
 * File: bioapif.h
 *
 *-----------------------------------------------------------------------
 */

/* Function declarations for the BioAPI Service Provider module.
 * The BioAPI_DEFINE_FUNC, __BioAPI_PASTE2 and __BioAPI_PASTE3 macros must be
 * defined by the file that includes this header.
 */

/* Check to make sure that all macros were defined */
#ifndef BioAPI_DEFINE_FUNCTION
#error "The BioAPI_DEFINE_FUNCTION(name,params) macro must be defined!"
#endif

/*************************************************************************/
/*** Function declarations ***********************************************/
/*************************************************************************/

BioAPI_DEFINE_FUNCTION( FreeBIRHandle, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_BIR_HANDLE BIRHandle ) );

BioAPI_DEFINE_FUNCTION( GetBIRFromHandle, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_BIR_HANDLE BIRHandle,
						BioAPI_BIR_PTR *BIR ) );

BioAPI_DEFINE_FUNCTION( GetHeaderFromHandle, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_BIR_HANDLE BIRHandle,
						BioAPI_BIR_HEADER_PTR Header ) );

BioAPI_DEFINE_FUNCTION( EnableEvents, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_MODULE_EVENT_MASK *Events ) );

BioAPI_DEFINE_FUNCTION( SetGUICallbacks, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_GUI_STREAMING_CALLBACK GuiStreamingCallback,
						void *GuiStreamingCallbackCtx,
						BioAPI_GUI_STATE_CALLBACK  GuiStateCallback,
						void *GuiStateCallbackCtx ) );

BioAPI_DEFINE_FUNCTION( SetStreamCallback, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_STREAM_CALLBACK StreamCallback,
						void *StreamCallbackCtx ) );

BioAPI_DEFINE_FUNCTION( StreamInputOutput, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_DATA_PTR InMessage,
						BioAPI_DATA_PTR OutMessage ) );

BioAPI_DEFINE_FUNCTION( Capture, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_BIR_PURPOSE Purpose,
						BioAPI_BIR_HANDLE_PTR CapturedBIR,
						sint32 Timeout,
						BioAPI_BIR_HANDLE_PTR AuditData ) );

BioAPI_DEFINE_FUNCTION( CreateTemplate, (
						BioAPI_HANDLE ModuleHandle,
						const BioAPI_INPUT_BIR *CapturedBIR,
						const BioAPI_INPUT_BIR *StoredTemplate,
						BioAPI_BIR_HANDLE_PTR NewTemplate,
						const BioAPI_DATA *Payload ) );

BioAPI_DEFINE_FUNCTION( Process, (
						BioAPI_HANDLE ModuleHandle,
						const BioAPI_INPUT_BIR *CapturedBIR,
						BioAPI_BIR_HANDLE_PTR ProcessedBIR ) );

BioAPI_DEFINE_FUNCTION( VerifyMatch, (
						BioAPI_HANDLE ModuleHandle,
						const BioAPI_FAR *MaxFARRequested,
						const BioAPI_FRR *MaxFRRRequested,
						const BioAPI_BOOL *FARPrecedence,
						const BioAPI_INPUT_BIR *ProcessedBIR,
						const BioAPI_INPUT_BIR *StoredTemplate,
						BioAPI_BIR_HANDLE *AdaptedBIR,
						BioAPI_BOOL *Result,
						BioAPI_FAR_PTR FARAchieved,
						BioAPI_FRR_PTR FRRAchieved,
						BioAPI_DATA_PTR	 *Payload ) );

BioAPI_DEFINE_FUNCTION( IdentifyMatch, (
						BioAPI_HANDLE ModuleHandle,
						const BioAPI_FAR *MaxFARRequested,
						const BioAPI_FRR *MaxFRRRequested,
						const BioAPI_BOOL *FARPrecedence,
						const BioAPI_INPUT_BIR *ProcessedBIR,
						const BioAPI_IDENTIFY_POPULATION *Population,
						BioAPI_BOOL	 Binning,
						uint32 MaxNumberOfResults,
						uint32 *NumberOfResults,
						BioAPI_CANDIDATE_ARRAY_PTR *Candidates,
						sint32 Timeout ) );

BioAPI_DEFINE_FUNCTION( Enroll, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_BIR_PURPOSE Purpose,
						const BioAPI_INPUT_BIR *StoredTemplate,
						BioAPI_BIR_HANDLE_PTR NewTemplate,
						const BioAPI_DATA *Payload,
						sint32 Timeout,
						BioAPI_BIR_HANDLE_PTR AuditData ) );

BioAPI_DEFINE_FUNCTION( Verify, (
						BioAPI_HANDLE ModuleHandle,
						const BioAPI_FAR *MaxFARRequested,
						const BioAPI_FRR *MaxFRRRequested,
						const BioAPI_BOOL *FARPrecedence,
						const BioAPI_INPUT_BIR *StoredTemplate,
						BioAPI_BIR_HANDLE_PTR AdaptedBIR,
						BioAPI_BOOL *Result,
						BioAPI_FAR_PTR FARAchieved,
						BioAPI_FRR_PTR FRRAchieved,
						BioAPI_DATA_PTR *Payload,
						sint32 Timeout,
						BioAPI_BIR_HANDLE_PTR AuditData ) );

BioAPI_DEFINE_FUNCTION( Identify, (
						BioAPI_HANDLE ModuleHandle,
						const BioAPI_FAR *MaxFARRequested,
						const BioAPI_FRR *MaxFRRRequested,
						const BioAPI_BOOL *FARPrecedence,
						const BioAPI_INPUT_BIR *ProcessedBIR,
						const BioAPI_IDENTIFY_POPULATION *Population,
						BioAPI_BOOL Binning,
						uint32 MaxNumberOfResults,
						uint32 *NumberOfResults,
						BioAPI_CANDIDATE_ARRAY_PTR *Candidates,
						sint32 Timeout,
						BioAPI_BIR_HANDLE_PTR AuditData ) );

BioAPI_DEFINE_FUNCTION( Import, (
						BioAPI_HANDLE ModuleHandle,
						const BioAPI_DATA *InputData,
						BioAPI_BIR_BIOMETRIC_DATA_FORMAT InputFormat,
						BioAPI_BIR_PURPOSE Purpose,
						BioAPI_BIR_HANDLE_PTR ConstructedBIR ) );

BioAPI_DEFINE_FUNCTION( SetPowerMode, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_POWER_MODE PowerMode ) );

BioAPI_DEFINE_FUNCTION( DbOpen, (
						BioAPI_HANDLE ModuleHandle,
						const uint8 *DbName,
						BioAPI_DB_ACCESS_TYPE AccessRequest,
						BioAPI_DB_HANDLE_PTR DbHandle,
						BioAPI_DB_CURSOR_PTR Cursor ) );

BioAPI_DEFINE_FUNCTION( DbClose, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_DB_HANDLE DbHandle ) );

BioAPI_DEFINE_FUNCTION( DbCreate, (
						BioAPI_HANDLE ModuleHandle,
						const uint8 *DbName,
						BioAPI_DB_ACCESS_TYPE AccessRequest,
						BioAPI_DB_HANDLE_PTR DbHandle ) );

BioAPI_DEFINE_FUNCTION( DbDelete, (
						BioAPI_HANDLE ModuleHandle,
						const uint8 *DbName ) );

BioAPI_DEFINE_FUNCTION( DbSetCursor, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_DB_HANDLE DbHandle,
						const BioAPI_UUID *KeyValue,
						BioAPI_DB_CURSOR_PTR Cursor ) );

BioAPI_DEFINE_FUNCTION( DbFreeCursor, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_DB_CURSOR_PTR Cursor ) );

BioAPI_DEFINE_FUNCTION( DbStoreBIR, (
						BioAPI_HANDLE ModuleHandle,
						const BioAPI_INPUT_BIR *BIRToStore,
						BioAPI_DB_HANDLE DbHandle,
						BioAPI_UUID_PTR Uuid ) );

BioAPI_DEFINE_FUNCTION( DbGetBIR, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_DB_HANDLE DbHandle,
						const BioAPI_UUID *KeyValue,
						BioAPI_BIR_HANDLE_PTR RetrievedBIR,
						BioAPI_DB_CURSOR_PTR Cursor ) );

BioAPI_DEFINE_FUNCTION( DbGetNextBIR, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_DB_CURSOR_PTR Cursor,
						BioAPI_BIR_HANDLE_PTR RetievedBIR,
						BioAPI_UUID_PTR Uuid ) );

BioAPI_DEFINE_FUNCTION( DbQueryBIR, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_DB_HANDLE DbHandle,
						const BioAPI_INPUT_BIR *BIRToQuery,
						BioAPI_UUID_PTR Uuid ) );

BioAPI_DEFINE_FUNCTION( DbDeleteBIR, (
						BioAPI_HANDLE ModuleHandle,
						BioAPI_DB_HANDLE DbHandle,
						const BioAPI_UUID *KeyValue ) );