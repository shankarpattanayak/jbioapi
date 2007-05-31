/*-----------------------------------------------------------------------
 * File: MDSEDITUTIL.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef MDS_EDIT_UTIL_H
#define MDS_EDIT_UTIL_H

#include <cssmtype.h>

void*  CSSMAPI mdsEdit_malloc( uint32 size, void* ref);
void   CSSMAPI mdsEdit_free( void* ptr, void* ref );
void*  CSSMAPI mdsEdit_realloc( void* ptr, uint32 size, void* ref );
void*  CSSMAPI mdsEdit_calloc( uint32 num, uint32 size, void* ref );
/*
CSSM_RETURN CSSMAPI mdsEdit_SetError(CSSM_GUID_PTR guid, uint32	 error);
CSSM_ERROR_PTR CSSMAPI mdsEdit_GetError(void);
void CSSMAPI mdsEdit_ClearError(void);
*/
#endif
