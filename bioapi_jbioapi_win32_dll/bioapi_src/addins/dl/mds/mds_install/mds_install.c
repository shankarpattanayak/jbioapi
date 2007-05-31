/*-----------------------------------------------------------------------
 * File: MDS_INSTALL.C
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#pragma warning (disable:4201 4514 4214 4115)
  #include <stdio.h>
  #include <io.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <windows.h>
#pragma warning (default:4201 4214 4115)
/* note that error 4514 is "unreferenced inline function has been removed" */

#include "port/bioapi_port.h"
#include "intel/installerr.h"
#include "ins_mds.h"


CSSM_RETURN CSSMAPI port_SetError ( CSSM_GUID_PTR guid, uint32 error )
{ guid; error; return( CSSM_OK ); }

#define MDS_BASENAME	"bioapi_mds300"
#define MDS_FILENAME	MDS_BASENAME ".dll"

void main( int argc, char* argv[] )
{
	BOOL bDNO = FALSE;
	BOOL bResult = FALSE;
	INSTALL_ERROR eError = INSTALL_SUCCESS;
	int index = 0, uninstall = 0, source = 0, dbdest = 0;
	char szSourcePath[_MAX_PATH],
		 szDbDestPath[_MAX_PATH],
		 szWinSys[_MAX_PATH],
		 szCurrDir[_MAX_PATH],
		 szMdsDbDir[_MAX_PATH],
		 szMdsEswSrc[_MAX_PATH],
		 szMdsDllDst[_MAX_PATH],
		 szMdsDllSrc[_MAX_PATH];

	memset( szSourcePath, 0, _MAX_PATH );
	memset( szDbDestPath, 0, _MAX_PATH );
	memset( szWinSys,	  0, _MAX_PATH );
	memset( szCurrDir,	  0, _MAX_PATH );
	memset( szMdsDbDir,	  0, _MAX_PATH );
	memset( szMdsEswSrc,  0, _MAX_PATH );
	memset( szMdsDllDst,  0, _MAX_PATH );
	memset( szMdsDllSrc,  0, _MAX_PATH );

	index = argc-1;

	/* parse command line */
	while( index )
	{
	  /* assign paths if necessary */
	  if( source == 1 )
	  {
		  strcpy( szSourcePath, argv[argc-index] );
		  source++;
	  }
	  if( dbdest == 1 )
	  {
		  strcpy( szDbDestPath, argv[argc-index] );
		  dbdest++;
	  }
	  if( !stricmp( argv[argc-index], "-u") && !uninstall )
	  {
		  uninstall = 1;
	  }
	  else if( !stricmp( argv[argc-index], "-s") && !source )
	  {
		  source = 1;
	  }
	  else if( !stricmp( argv[argc-index], "-d") && !dbdest )
	  {
		  dbdest = 1;
	  }

	  index--;
	}

	if( uninstall )
	{
		/* Begin uninstalling MDS */

		eError = uninstall_mds( );
		if( INSTALL_SUCCESS != eError )
		{
			printf("MDS uinstall failed.\n");
			exit(1);
		}
		else
		{
			printf("MDS uninstalled successfully.\n");
			exit(0);
		}
	}
	else
	{
		/* Begin installing MDS */

		GetSystemDirectory( szWinSys, sizeof( szWinSys ) );
		GetCurrentDirectory( _MAX_PATH, szCurrDir);

		/* MDS DLL Source Location */
		if( !source )
		{
			/* There is no -s source specified; search path. */

			SearchPath( NULL,		   // LPCSTR lpPath,
						MDS_BASENAME,  // LPCSTR lpFileName,
						".dll",		   // LPCSTR lpExtension,
						_MAX_PATH,	   // DWORD nBufferLength,
						szSourcePath,  // LPSTR lpBuffer,
						NULL );		   // LPSTR *lpFilePart

			if( strlen( szSourcePath ) < 3 )
			{
				MessageBox( NULL, "Source file not found.","Install Error",
							MB_ICONEXCLAMATION|MB_OK|MB_SETFOREGROUND );
				exit(1);
			}
		}

		/* Set MDS Database Destination */
		if( !dbdest )
		{
			/* There is no -d destination specified; create default. */
			wsprintf( szMdsDbDir, "%s%s", szWinSys, "\\BioAPIFFDB" );
		}
		else
		{
			/* Heuristic for detection of type of path being passed in:
			 *
			 *	If there's a ":" **OR**
			 *	if \ and \ are the first two characters,
			 *	assume a network path was passed in; use as is.
			 *
			 *	Else if \ is the first character (but \ is not the second),
			 *	prepend the current drive letter and a ":" character.
			 *
			 *	Else those three cases failed, and it must be a relative path
			 *	so prepend the fully-qualified current directory path.
			 *
			 */

			if ( (strcspn(szDbDestPath, ":") < strlen(szDbDestPath)) ||
				 ((szDbDestPath[0] == '\\') && (szDbDestPath[1] == '\\')) )
			{
				wsprintf( szMdsDbDir, "%s", szDbDestPath );
			}
			else if (szDbDestPath[0] == '\\')
			{
				wsprintf( szMdsDbDir, "%c:%s", szCurrDir[0], szDbDestPath);
			}
			else
			{
				wsprintf( szMdsDbDir, "%s\\%s", szCurrDir, szDbDestPath);
			}
		}

		CreateDirectory( szMdsDbDir, NULL );

		/* Copy MDS DLL and set file attributes */
		wsprintf( szMdsDllSrc, "%s%s", szSourcePath, "\\" MDS_FILENAME );
		wsprintf( szMdsDllDst, "%s%s", szWinSys, "\\" MDS_FILENAME );
		/* Just in case a read-only version exists at the destination . . . */
		SetFileAttributes( szMdsDllDst, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE );
		/* Now copy the file . . . */
		bResult = CopyFile( szMdsDllSrc, szMdsDllDst, bDNO );
		if( bResult == FALSE )
		{
		   MessageBox( NULL, "Error", "Copy failed for " MDS_FILENAME,
					   MB_ICONEXCLAMATION|MB_OK|MB_SETFOREGROUND );
		   exit(1);
		}
		else
		{
			SetFileAttributes( szMdsDllDst, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE );
		}

		eError = install_mds( szMdsDllDst, szMdsDbDir, szMdsEswSrc );

		if( INSTALL_SUCCESS != eError )
		{
		  printf("MDS install failed.\n");
		  exit(1);
		}
		else
		{
		  printf("MDS installed successfully.\n");
		  exit(0);
		}
	}
}
