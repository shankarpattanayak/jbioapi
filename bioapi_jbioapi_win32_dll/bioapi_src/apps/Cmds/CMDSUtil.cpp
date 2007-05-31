/*-----------------------------------------------------------------------
 * File: CMDSUTIL.CPP
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


#include "stdafx.h"
#include "CMdsUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef CSSM_MEMTRACK_ON
void* CSSMAPI CMdsUtil_malloc(uint32 size,
							  void* ref)
{
	return malloc( size );
}

void CSSMAPI CMdsUtil_free( void* ptr, void* ref)
{
	free( ptr );
}

void* CSSMAPI CMdsUtil_realloc(void* ptr,
							   uint32 size,
							   void* ref)
{
	return realloc( ptr, size);
}

void* CSSMAPI CMdsUtil_calloc(uint32 num,
							  uint32 size,
							  void* ref)
{
	return calloc( num, size );
}


#else

void* CSSMAPI CMdsUtil_malloc(uint32 size,
							  void* ref,
							  const char * szFilename,
							  uint32 u32LineNumber)
{
	return _malloc_dbg( size, _NORMAL_BLOCK, szFilename, u32LineNumber );
}

void CSSMAPI CMdsUtil_free( void* ptr, void* ref,
							  const char * szFilename,
							  uint32 u32LineNumber )
{
	_free_dbg( ptr, _NORMAL_BLOCK );
}

void* CSSMAPI CMdsUtil_realloc(void* ptr,
							   uint32 size,
							   void* ref,
							   const char * szFilename,
							   uint32 u32LineNumber)
{
	return _realloc_dbg( ptr, size, _NORMAL_BLOCK, szFilename, u32LineNumber );
}

void* CSSMAPI CMdsUtil_calloc(uint32 num,
							  uint32 size,
							  void* ref,
							  const char * szFilename,
							  uint32 u32LineNumber)
{
	return _calloc_dbg( num, size, _NORMAL_BLOCK, szFilename, u32LineNumber );
}

#endif

#include "AppMemTrack.h"

DWORD CMdsUtil_AllocRef = 0;

