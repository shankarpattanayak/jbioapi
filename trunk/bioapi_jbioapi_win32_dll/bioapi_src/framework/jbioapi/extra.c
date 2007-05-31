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

#include "net_qrivy_bioapi_BioAPI.h"
#include <bioapi.h>
#include <string.h>

/*
 * Class:     net_qrivy_jbioapi_BioAPI
 * Method:    getBirHeaderByteBuffer
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_net_qrivy_bioapi_BioAPI_getBirHeaderByteBuffer
  (JNIEnv *env, jclass this, jlong birPointer) {
	  BioAPI_BIR_PTR bir = (BioAPI_BIR_PTR)(int)birPointer;
	  return (* env)->NewDirectByteBuffer(env, &(bir->Header), (jlong)16);
  }

/*
 * Class:     net_qrivy_jbioapi_BioAPI
 * Method:    getBirDataByteBuffer
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_net_qrivy_bioapi_BioAPI_getBirDataByteBuffer
  (JNIEnv *env, jclass this, jlong birPointer) {
	  BioAPI_BIR_PTR bir = (BioAPI_BIR_PTR)(int)birPointer;
	  return (* env)->NewDirectByteBuffer(env, bir->BiometricData, (jlong)((bir->Header.Length)-16));
  }

/*
 * Class:     net_qrivy_jbioapi_BioAPI
 * Method:    getBirSignatureByteBuffer
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_net_qrivy_bioapi_BioAPI_getBirSignatureByteBuffer
  (JNIEnv *env, jclass this, jlong birPointer) {
	  BioAPI_BIR_PTR bir = (BioAPI_BIR_PTR)(int)birPointer;
	  jlong length;
	  if (bir->Signature) {
		  length = (jlong)(bir->Signature->Length);
	  } else {
		  length = (jlong)0;
	  }
	  return (* env)->NewDirectByteBuffer(env, bir->Signature, length);
  }

/*
 * Class:     net_qrivy_bioapi_BioAPI
 * Method:    setBirHeader
 * Signature: (JLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_net_qrivy_bioapi_BioAPI_setBirHeader
  (JNIEnv *env, jclass this, jlong birPointer, jobject headerDirectBuffer) {
	  memcpy(&(((BioAPI_BIR_PTR)(int)birPointer)->Header), (* env)->GetDirectBufferAddress(env, headerDirectBuffer), sizeof(BioAPI_BIR_HEADER));
	  }

/*
 * Class:     net_qrivy_bioapi_BioAPI
 * Method:    setBirData
 * Signature: (JLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_net_qrivy_bioapi_BioAPI_setBirData
  (JNIEnv *env, jclass this, jlong birPointer, jobject dataDirectBuffer) {
	  BioAPI_BIR_PTR bir = (BioAPI_BIR_PTR)(int)birPointer;
	  size_t length = bir->Header.Length - 16;
	  bir->BiometricData = (BioAPI_BIR_BIOMETRIC_DATA_PTR)malloc(length);
	  memcpy(bir->BiometricData, (* env)->GetDirectBufferAddress(env, dataDirectBuffer), length);
  }

/*
 * Class:     net_qrivy_bioapi_BioAPI
 * Method:    setSignatureData
 * Signature: (JLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_net_qrivy_bioapi_BioAPI_setSignatureData
  (JNIEnv *env, jclass this, jlong birPointer, jobject signatureDirectBuffer) {
	  BioAPI_BIR_PTR bir = (BioAPI_BIR_PTR)(int)birPointer;
	  bir->Signature = (BioAPI_DATA_PTR)malloc(sizeof(BioAPI_DATA));
	  bir->Signature->Length = (uint32)((* env)->GetDirectBufferCapacity(env, signatureDirectBuffer));
	  memcpy(bir->Signature->Data, (* env)->GetDirectBufferAddress(env, signatureDirectBuffer), (size_t)(bir->Signature->Length));
  }
	  

