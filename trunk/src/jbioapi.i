/* JBioAPI: a library of tools for accessing BioAPI-compliant biometric
 * service providers in Java.
 * 
 * Copyright (C) 2005 Michael R. Crusoe <michael@qrivy.net>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
 
%module BioAPI
%javaconst(1);
%include "typemaps.i"

%ignore BioAPI_TRUE;
%immutable reference_h_layer_1_0_0_uuid; 

%{
#include <bioapi.h>
%}
%include bioapi_type.h
%include bioapi_err.h
%include bioapi_uuid.h
%include bioapi_typecast.h

%{
BioAPI_RETURN BioAPI_GetPrintableUUID( const BioAPI_UUID *INPUT,
		char *OUTPUT );
BioAPI_RETURN BioAPI_GetStructuredUUID( const char *INPUT,
		BioAPI_UUID_PTR OUTPUT );
%}

%inline %{

typedef char BioAPI_STRING[68];

typedef struct _bioapi_bsp_schema
{
        BioAPI_UUID ModuleId;
        BioAPI_DEVICE_ID DeviceId;
        BioAPI_STRING BSPName;
        BioAPI_VERSION SpecVersion;
        BioAPI_VERSION ProductVersion;
        BioAPI_STRING Vendor;
        BioAPI_BIR_BIOMETRIC_DATA_FORMAT BspSupportedFormats;
        uint32 NumSupportedFormats;
        uint32 FactorsMask;
        uint32 Operations;
        uint32 Options;
        uint32 PayloadPolicy;
        uint32 MaxPayloadSize;
        sint32 DefaultVerifyTimeout;
        sint32 DefaultIdentifyTimeout;
        sint32 DefaultCaptureTimeout;
        sint32 DefaultEnrollTimeout;
        uint32 MaxBspDbSize;
        uint32 MaxIdentify;
        BioAPI_STRING Description;
        char Path;
} BioAPI_BSP_SCHEMA, *BioAPI_BSP_SCHEMA_PTR;

typedef BioAPI_BSP_SCHEMA_PTR BioAPI_BSP_SCHEMA_ARRAY, *BioAPI_BSP_SCHEMA_ARRAY_PTR;

BioAPI_RETURN BioAPI BioAPI_EnumModules(BioAPI_BSP_SCHEMA *BspSchemaArray,
									uint32 ArraySize,
									uint32 *ElementsNeeded,
									uint32 *NumElementsReturned);

%}

extern const BioAPI_MEMORY_FUNCS BioAPIMemoryFuncs;

BioAPI_RETURN BioAPI BioAPI_QueryDevice(
						BioAPI_HANDLE INPUT,
						BioAPI_SERVICE_UID_PTR OUTPUT );
BioAPI_RETURN BioAPI BioAPI_FreeBIRHandle(
						BioAPI_HANDLE INPUT,
						BioAPI_BIR_HANDLE INPUT );

BioAPI_RETURN BioAPI BioAPI_GetBIRFromHandle(
						BioAPI_HANDLE INPUT,
						BioAPI_BIR_HANDLE INPUT,
						BioAPI_BIR_PTR *OUTPUT );

BioAPI_RETURN BioAPI BioAPI_GetHeaderFromHandle(
						BioAPI_HANDLE INPUT,
						BioAPI_BIR_HANDLE INPUT,
						BioAPI_BIR_HEADER_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_EnableEvents(
						BioAPI_HANDLE INPUT,
						BioAPI_MODULE_EVENT_MASK *INPUT );

//BioAPI_RETURN BioAPI BioAPI_SetGUICallbacks(
//						BioAPI_HANDLE INPUT,
//						BioAPI_GUI_STREAMING_CALLBACK INPUT,
//						void *INPUT,
//						BioAPI_GUI_STATE_CALLBACK INPUT,
//						void *INPUT );

//BioAPI_RETURN BioAPI BioAPI_SetStreamCallback(
//						BioAPI_HANDLE INPUT,
//						BioAPI_STREAM_CALLBACK INPUT,
//						void *INPUT );

//BioAPI_RETURN BioAPI BioAPI_StreamInputOutput(
//						BioAPI_HANDLE INPUT,
//						BioAPI_DATA_PTR INPUT,
//						BioAPI_DATA_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_Capture(
						BioAPI_HANDLE INPUT,
						BioAPI_BIR_PURPOSE INPUT,
						BioAPI_BIR_HANDLE_PTR OUTPUT,
						sint32 INPUT,
						BioAPI_BIR_HANDLE_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_CreateTemplate(
						BioAPI_HANDLE INPUT,
						const BioAPI_INPUT_BIR *INPUT,
						const BioAPI_INPUT_BIR *INPUT,
						BioAPI_BIR_HANDLE_PTR OUTPUT,
						const BioAPI_DATA *INPUT );

BioAPI_RETURN BioAPI BioAPI_Process(
						BioAPI_HANDLE INPUT,
						const BioAPI_INPUT_BIR *INPUT,
						BioAPI_BIR_HANDLE_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_VerifyMatch(
						BioAPI_HANDLE INPUT,
						const BioAPI_FAR *INPUT,
						const BioAPI_FRR *INPUT,
						const BioAPI_BOOL *INPUT,
						const BioAPI_INPUT_BIR *INPUT,
						const BioAPI_INPUT_BIR *INPUT,
						BioAPI_BIR_HANDLE *OUTPUT,
						BioAPI_BOOL *OUTPUT,
						BioAPI_FAR_PTR OUTPUT,
						BioAPI_FRR_PTR OUTPUT,
						BioAPI_DATA_PTR *OUTPUT );

BioAPI_RETURN BioAPI BioAPI_IdentifyMatch(
						BioAPI_HANDLE INPUT,
						const BioAPI_FAR *INPUT,
						const BioAPI_FRR *INPUT,
						const BioAPI_BOOL *INPUT,
						const BioAPI_INPUT_BIR *INPUT,
						const BioAPI_IDENTIFY_POPULATION *INPUT,
						BioAPI_BOOL INPUT,
						uint32 INPUT,
						uint32 *OUTPUT,
						BioAPI_CANDIDATE_ARRAY_PTR *OUTPUT,
						sint32 INPUT );

BioAPI_RETURN BioAPI BioAPI_Identify(
						BioAPI_HANDLE INPUT,
						const BioAPI_FAR *INPUT,
						const BioAPI_FRR *INPUT,
						const BioAPI_BOOL *INPUT,
						const BioAPI_IDENTIFY_POPULATION *INPUT,
						BioAPI_BOOL INPUT,
						uint32 INPUT,
						uint32 *OUTPUT,
						BioAPI_CANDIDATE_ARRAY_PTR *OUTPUT,
						sint32 INPUT,
						BioAPI_BIR_HANDLE_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_Import(
						BioAPI_HANDLE INPUT,
						const BioAPI_DATA *INPUT,
						BioAPI_BIR_BIOMETRIC_DATA_FORMAT INPUT,
						BioAPI_BIR_PURPOSE INPUT,
						BioAPI_BIR_HANDLE_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_SetPowerMode(
						BioAPI_HANDLE INPUT,
						BioAPI_POWER_MODE INPUT );

BioAPI_RETURN BioAPI BioAPI_DbOpen(
						BioAPI_HANDLE INPUT,
						const uint8 *INPUT,
						BioAPI_DB_ACCESS_TYPE INPUT,
						BioAPI_DB_HANDLE_PTR OUTPUT,
						BioAPI_DB_CURSOR_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_DbClose(
						BioAPI_HANDLE INPUT,
						BioAPI_DB_HANDLE INPUT );

BioAPI_RETURN BioAPI BioAPI_DbCreate(
						BioAPI_HANDLE INPUT,
						const uint8 *INPUT,
						BioAPI_DB_ACCESS_TYPE INPUT,
						BioAPI_DB_HANDLE_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_DbDelete(
						BioAPI_HANDLE INPUT,
						const uint8 *INPUT );

BioAPI_RETURN BioAPI BioAPI_DbSetCursor(
						BioAPI_HANDLE INPUT,
						BioAPI_DB_HANDLE INPUT,
						const BioAPI_UUID *INPUT,
						BioAPI_DB_CURSOR_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_DbFreeCursor(
						BioAPI_HANDLE INPUT,
						BioAPI_DB_CURSOR_PTR INPUT );

BioAPI_RETURN BioAPI BioAPI_DbStoreBIR(
						BioAPI_HANDLE INPUT,
						const BioAPI_INPUT_BIR *INPUT,
						BioAPI_DB_HANDLE INPUT,
						BioAPI_UUID_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_DbGetBIR(
						BioAPI_HANDLE INPUT,
						BioAPI_DB_HANDLE INPUT,
						const BioAPI_UUID *INPUT,
						BioAPI_BIR_HANDLE_PTR OUTPUT,
						BioAPI_DB_CURSOR_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_DbGetNextBIR(
						BioAPI_HANDLE INPUT,
						BioAPI_DB_CURSOR_PTR INOUT,
						BioAPI_BIR_HANDLE_PTR OUTPUT,
						BioAPI_UUID_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_DbQueryBIR(
						BioAPI_HANDLE INPUT,
						BioAPI_DB_HANDLE INPUT,
						const BioAPI_INPUT_BIR *INPUT,
						BioAPI_UUID_PTR OUTPUT );

BioAPI_RETURN BioAPI BioAPI_DbDeleteBIR(
						BioAPI_HANDLE INPUT,
						BioAPI_DB_HANDLE INPUT,
						const BioAPI_UUID *INPUT );
%constant long BioAPI_MAJOR = 1;
%constant long BioAPI_MINOR = 10;

BioAPI_RETURN BioAPI BioAPI_EnumModules(BioAPI_BSP_SCHEMA *INPUT,
					uint32 OUTPUT,
					uint32 *OUTPUT,
					uint32 *OUTPUT);

%newobject newUUID;

%javaexception ("net.qrivy.jbioapi.BioApiException") getBirFromHandle {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") getStructuredUuid {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") init {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") attachModule {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") enroll {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") detachModule {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") terminate {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") loadModule {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") unloadModule {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") loadModuleWithCallbacks {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") unloadModuleWithCallbacks {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") verify {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}

%javaexception ("net.qrivy.jbioapi.BioApiException") getSchema {
	$action
	if (jbioapierr != BioAPI_OK) {
		if (bioApiException == NULL) {
			bioApiException = (*jenv)->FindClass(jenv, "net/qrivy/jbioapi/BioApiException");
		}
		if (bioApiExceptionInit == NULL) {
			bioApiExceptionInit = (*jenv)->GetMethodID(jenv, bioApiException, "<init>", "(J)V");
		}
		jobject exception = (*jenv)->NewObject(jenv, bioApiException, bioApiExceptionInit, (jlong)jbioapierr);
		(*jenv)->Throw(jenv, exception);
		return $null;
	}
}


%{
BioAPI_RETURN jbioapierr;
jclass bioApiException;
jmethodID bioApiExceptionInit;
static const BioAPI_VERSION version = { 1, 10 };
%}

%include "carrays.i";
%array_class(BioAPI_BSP_SCHEMA, SchemaArray);

%inline %{
BioAPI_BIR* BioAPI getBirFromHandle(BioAPI_HANDLE moduleHandle,
	BioAPI_BIR_HANDLE handle) {
	BioAPI_BIR *bir;
	jbioapierr = BioAPI_GetBIRFromHandle(moduleHandle, handle, &bir);
	return bir;
	}

BioAPI_UUID_PTR getStructuredUuid(const char *INPUT) {
	BioAPI_UUID_PTR uuid = (BioAPI_UUID_PTR) malloc(sizeof(BioAPI_UUID));
	jbioapierr = BioAPI_GetStructuredUUID(INPUT, uuid);
	return uuid;
	}

char* getPrintableUUID(const BioAPI_UUID *INPUT) {
	char *uuid;
	jbioapierr = BioAPI_GetPrintableUUID(INPUT, uuid);
	return uuid;
	}

BioAPI_HANDLE attachModule(	const BioAPI_UUID *uuid,
				const BioAPI_MEMORY_FUNCS *memoryFuncs,
				uint32 DeviceID) {
	BioAPI_HANDLE bspHandle;
	jbioapierr = BioAPI_ModuleAttach(uuid, &version, memoryFuncs, DeviceID, 0, 0, 0, NULL, 0, NULL, &bspHandle);
	return bspHandle;
	}

void detachModule(BioAPI_HANDLE bspHandle) {
	jbioapierr = BioAPI_ModuleDetach(bspHandle);
	}

uint32 getNumberOfModules() {
	uint32 modules, numModulesReturned;
	jbioapierr = BioAPI_EnumModules(NULL, 0, &modules, &numModulesReturned);
	return modules;
	}

BioAPI_BSP_SCHEMA* getSchemas() {
	uint32 elementsNeeded, numElementsReturned, arraySize;
	jbioapierr = BioAPI_EnumModules(NULL, 0, &elementsNeeded, &numElementsReturned);
	if (jbioapierr == BioAPI_OK) {
		BioAPI_BSP_SCHEMA* schemaArray = (BioAPI_BSP_SCHEMA *)malloc(elementsNeeded * sizeof(BioAPI_BSP_SCHEMA));
		jbioapierr = BioAPI_EnumModules(schemaArray, arraySize, &elementsNeeded, &numElementsReturned);
		return schemaArray;
	} else {
		return NULL;
	}
}

void loadModule(const BioAPI_UUID *uuid) {
	jbioapierr = BioAPI_ModuleLoad(uuid, 0, NULL, NULL);
	}

void unloadModule(const BioAPI_UUID *uuid) {
	jbioapierr = BioAPI_ModuleUnload(uuid, NULL, NULL);
	}

void loadModuleWithCallbacks(const BioAPI_UUID *uuid, BioAPI_ModuleEventHandler appNotifyCallback, void *appNotifyCallbackContext) {
	jbioapierr = BioAPI_ModuleLoad(uuid, 0, appNotifyCallback, appNotifyCallbackContext);
	}

void unloadModuleWithCallbacks(const BioAPI_UUID *uuid, BioAPI_ModuleEventHandler appNotifyCallback, void *appNotifyCallbackContext) {
	jbioapierr = BioAPI_ModuleUnload(uuid, appNotifyCallback, appNotifyCallbackContext);
	}

void init() {
	jbioapierr = BioAPI_Init(&version, 0, NULL, 0, NULL);
	}

BioAPI_BIR_HANDLE enroll(BioAPI_HANDLE moduleHandle, BioAPI_BIR_PURPOSE purpose, sint32 timeout) {
	BioAPI_BIR_HANDLE bir;
	jbioapierr = BioAPI_Enroll(moduleHandle, purpose, NULL, &bir, NULL, timeout, NULL);
	return bir;
	}
	
BioAPI_BIR_HANDLE enrollWithPayload(BioAPI_HANDLE moduleHandle, BioAPI_BIR_PURPOSE purpose, const BioAPI_DATA payload, sint32 timeout) {
	BioAPI_BIR_HANDLE bir;
	jbioapierr = BioAPI_Enroll(moduleHandle, purpose, NULL, &bir, &payload, timeout, NULL);
	return bir;
	}

BioAPI_BIR_HANDLE enrollAndAdapt(BioAPI_HANDLE moduleHandle, BioAPI_BIR_PURPOSE purpose, const BioAPI_INPUT_BIR storedTemplate, sint32 timeout) {
	BioAPI_BIR_HANDLE bir;
	jbioapierr = BioAPI_Enroll(moduleHandle, purpose, &storedTemplate, &bir, NULL, timeout, NULL);
	return bir;
	}

BioAPI_BIR_HANDLE enrollAndAdaptWithPayload(BioAPI_HANDLE moduleHandle, BioAPI_BIR_PURPOSE purpose, const BioAPI_INPUT_BIR storedTemplate, const BioAPI_DATA payload, sint32 timeout) {
	BioAPI_BIR_HANDLE bir;
	jbioapierr = BioAPI_Enroll(moduleHandle, purpose, &storedTemplate, &bir, &payload, timeout, NULL);
	return bir;
	}

void terminate() {
	jbioapierr = BioAPI_Terminate();
	}
	
BioAPI_INPUT_BIR getInputBIR(BioAPI_BIR bir) {
	BioAPI_INPUT_BIR inputBIR;
	inputBIR.InputBIR.BIR = &bir;
	inputBIR.Form = BioAPI_FULLBIR_INPUT;
	return inputBIR;
	}

typedef struct {
BioAPI_BIR_HANDLE adaptedBir;
BioAPI_BOOL result;
BioAPI_FAR farAchieved;
BioAPI_FRR frrAchieved;
BioAPI_DATA_PTR payload;
BioAPI_BIR_HANDLE auditData;
} verifyResult;

verifyResult verify(BioAPI_HANDLE moduleHandle, const BioAPI_FAR far, const BioAPI_FRR frr, BioAPI_BOOL farOrFrr, const BioAPI_INPUT_BIR inputBir, sint32 timeout) {
	BioAPI_BIR_HANDLE adaptedBir;
	BioAPI_BOOL result = BioAPI_FALSE;
	BioAPI_FAR farAchieved;
	BioAPI_FRR frrAchieved;
	BioAPI_DATA_PTR payload;
	BioAPI_BIR_HANDLE auditData;
	verifyResult answer;
	answer.adaptedBir = adaptedBir;
	answer.result = result;
	answer.farAchieved = farAchieved;
	answer.frrAchieved = frrAchieved;
	answer.payload = payload;
	answer.auditData = auditData;
	jbioapierr = BioAPI_OK;
	jbioapierr = BioAPI_Verify(moduleHandle, &far, &frr, &farOrFrr, &inputBir, &(answer.adaptedBir), &(answer.result), &(answer.farAchieved), &(answer.frrAchieved), &(answer.payload), timeout, &(answer.auditData));
	//jbioapierr = BioAPI_Verify(moduleHandle, &far, NULL, NULL, &inputBir, NULL, &(answer.result), &(answer.farAchieved), NULL, NULL, -1, NULL);
	return answer;
	}

verifyResult verifyBir(BioAPI_HANDLE moduleHandle, const BioAPI_FAR far, const BioAPI_FRR frr, BioAPI_BOOL farOrFrr, BioAPI_BIR bir, sint32 timeout) {
	BioAPI_INPUT_BIR inputBir;
	inputBir.InputBIR.BIR = &bir;
	inputBir.Form = BioAPI_FULLBIR_INPUT;
	return verify(moduleHandle, far, frr, farOrFrr,(const BioAPI_INPUT_BIR) inputBir, timeout);
}
%}

%pragma(java) modulecode=%{
  public static java.nio.ByteBuffer getBirHeaderByteBuffer(BioAPI_BIR bir) {
    return getBirHeaderByteBuffer(BioAPI_BIR.getCPtr(bir));
    }
    
  static native java.nio.ByteBuffer getBirHeaderByteBuffer(long cpointer);
  
  public static java.nio.ByteBuffer getBirDataByteBuffer(BioAPI_BIR bir) {
    return getBirDataByteBuffer(BioAPI_BIR.getCPtr(bir));
    }
  
  static native java.nio.ByteBuffer getBirDataByteBuffer(long cpointer);
	
  public static java.nio.ByteBuffer getBirSignatureByteBuffer(BioAPI_BIR bir) {
    return getBirSignatureByteBuffer(BioAPI_BIR.getCPtr(bir));
    }
  
  static native java.nio.ByteBuffer getBirSignatureByteBuffer(long cpointer);

  public static void setBirHeader(BioAPI_BIR bir, java.nio.ByteBuffer headerBuffer) {
    setBirHeader(BioAPI_BIR.getCPtr(bir), headerBuffer);
    }

  static native void setBirHeader(long cpointer, java.nio.ByteBuffer headerBuffer);

  public static void setBirData(BioAPI_BIR bir, java.nio.ByteBuffer dataBuffer) {
    setBirData(BioAPI_BIR.getCPtr(bir), dataBuffer);
    }

  static native void setBirData(long cpointer, java.nio.ByteBuffer dataBuffer);

  public static void setSignatureData(BioAPI_BIR bir, java.nio.ByteBuffer signatureBuffer) {
    setSignatureData(BioAPI_BIR.getCPtr(bir), signatureBuffer);
    }

  static native void setSignatureData(long cpointer, java.nio.ByteBuffer signatureBuffer);
%}
