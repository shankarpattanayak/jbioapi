/*-----------------------------------------------------------------------
 * File: CMDSUTIL.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */


#ifndef CMDS_EDIT_UTIL_H
#define CMDS_EDIT_UTIL_H

#include <cssmtype.h>


#ifndef CSSM_MEMTRACK_ON

void* CSSMAPI CMdsUtil_malloc(uint32 size,
							  void* ref);

void CSSMAPI CMdsUtil_free( void* ptr, void* ref);

void* CSSMAPI CMdsUtil_realloc(void* ptr,
							   uint32 size,
							   void* ref);

void* CSSMAPI CMdsUtil_calloc(uint32 num,
							  uint32 size,
							  void* ref);


#else

void* CSSMAPI CMdsUtil_malloc(uint32 size,
							  void* ref,
							  const char * szFilename,
							  uint32 u32LineNumber);

void CSSMAPI CMdsUtil_free( void* ptr, void* ref,
							  const char * szFilename,
							  uint32 u32LineNumber );

void* CSSMAPI CMdsUtil_realloc(void* ptr,
							   uint32 size,
							   void* ref,
							   const char * szFilename,
							   uint32 u32LineNumber);

void* CSSMAPI CMdsUtil_calloc(uint32 num,
							  uint32 size,
							  void* ref,
							  const char * szFilename,
							  uint32 u32LineNumber);
#endif

extern DWORD CMdsUtil_AllocRef;


#endif
