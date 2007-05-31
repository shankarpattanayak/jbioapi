/*-----------------------------------------------------------------------
 * File: bioapi_dummy_addini.c
 *-----------------------------------------------------------------------
 */

#include "precomp.h"

/* Define each SPI function.
 */
#process_start paramindent 20 funcptrindent 0 fptrnameindent 32 fnameindent 0 fbodyindent 4

/* Define a few utility macros for generating symbol names */
#define __BIOAPI_PASTE2( _x_, _y_ ) _x_##_y_

#define BioAPI_DEFINE_FUNCTION( name, params ) \
	BioAPI_RETURN BioAPI __BIOAPI_PASTE2( BSP_, name ) params \
	{ \
		BioAPI_RETURN ret = BioAPI_OK; \
		void *pAddinContext = NULL; \
		ADDIN_SPI_BEGIN(ret, FIRST_FUNC_PARAM, pAddinContext); \
		if (ret != BioAPI_OK) \
			return ret;		/* insert code here */ \
		Addin_SPIEnd(pAddinContext); \
		return __BIOAPI_PASTE2(BioAPIERR_, FUNC_NAME_AS_ERROR); \
	}

#include "bioapif.c"

#process_end

/* Define the attach function.
 */
#process_start paramindent 20 funcptrindent 0 fptrnameindent 32 fnameindent 0 fbodyindent 4

/* Define a few utility macros for generating symbol names */
#define __BIOAPI_PASTE2( _x_, _y_ ) _x_##_y_

#define BioAPI_DEFINE_FUNCTION( name, params ) \
	Functions.name = __BIOAPI_PASTE2( BSP_, name);

BioAPI_RETURN BSP_ModuleAttach(
				   BioAPI_MODULE_FUNCS_PTR *FuncTbl )
{
	static BioAPI_MODULE_FUNCS FunctionList;
	static BioAPI_BSP_FUNCS Functions;
	if (!FuncTbl)
	{
		return BioAPIERR_BSP_INVALID_POINTER;
	}
	FunctionList.NumberOfServiceFuncs = sizeof(BioAPI_BSP_FUNCS) /
										  sizeof(BioAPI_PROC_ADDR);

	FunctionList.ServiceFuncs = (BioAPI_PROC_ADDR*)&Functions;

#include "bioapif.c"
	*FuncTbl = &FunctionList;
	return BioAPI_OK;
}

#process_end
