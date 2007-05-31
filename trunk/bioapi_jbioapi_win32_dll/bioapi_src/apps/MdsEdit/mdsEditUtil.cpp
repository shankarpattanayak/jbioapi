/*-----------------------------------------------------------------------
 * File: MDSEDITUTIL.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#include "stdafx.h"
#include "mdsEditUtil.h"

static CSSM_ERROR s_ceError;

void* CSSMAPI mdsEdit_malloc( uint32 size, void* ref)
{
	return malloc( size );
}

void CSSMAPI mdsEdit_free( void* ptr, void* ref )
{
	free( ptr );
	return;
}

void* CSSMAPI mdsEdit_realloc( void* ptr, uint32 size, void* ref )
{
	return realloc( ptr, size );
}

void* CSSMAPI mdsEdit_calloc( uint32 num, uint32 size, void* ref )
{
	return calloc( num, size );
}

/*
CSSM_RETURN CSSMAPI mdsEdit_SetError (CSSM_GUID_PTR guid, uint32 error)
{
	guid;
	error;
	return CSSM_OK;
}

CSSM_ERROR_PTR CSSMAPI mdsEdit_GetError(void)
{
	s_ceError.error = CSSM_OK;
	return &s_ceError;
}

void CSSMAPI mdsEdit_ClearError(void)
{
}
*/