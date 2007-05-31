/*-----------------------------------------------------------------------
 * File: INS_MDS.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _INS_MDS_H
#define _INS_MDS_H

#include "intel/installerr.h"
#include "cssmtype.h"
#include "dlutil_reg.h"
#include "mds.h"
#include "mds_schema.h"

#ifdef WIN32
  #define Remove DeleteFile
  #define Copy CopyFile
#endif

#define MDS_REGISTRY_PATH "Software\\BioAPI\\MDS\\"
#define MDS_MAJOR 1
#define MDS_MINOR 0

#ifdef __cplusplus
extern "C" {
#endif


INSTALL_ERROR install_mds( char* MDSPath,
						   char* dbpath,
						   char* ManifestPath );

INSTALL_ERROR uninstall_mds( void );

#ifdef WIN32
BOOL
mds_GetRegString ( LPSTR pszKey,
				   LPSTR pszValue,
				   LPSTR pszData );
#endif

#ifdef __cplusplus
}
#endif


#endif /* _INS_MDS_H */
