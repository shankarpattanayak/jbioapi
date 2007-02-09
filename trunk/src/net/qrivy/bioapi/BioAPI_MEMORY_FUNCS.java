/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.24
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package net.qrivy.bioapi;

public class BioAPI_MEMORY_FUNCS {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected BioAPI_MEMORY_FUNCS(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(BioAPI_MEMORY_FUNCS obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      BioAPIJNI.delete_BioAPI_MEMORY_FUNCS(swigCPtr);
    }
    swigCPtr = 0;
  }

  public void setMalloc_func(SWIGTYPE_p_f_unsigned_int_p_void__p_void Malloc_func) {
    BioAPIJNI.set_BioAPI_MEMORY_FUNCS_Malloc_func(swigCPtr, SWIGTYPE_p_f_unsigned_int_p_void__p_void.getCPtr(Malloc_func));
  }

  public SWIGTYPE_p_f_unsigned_int_p_void__p_void getMalloc_func() {
    long cPtr = BioAPIJNI.get_BioAPI_MEMORY_FUNCS_Malloc_func(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_unsigned_int_p_void__p_void(cPtr, false);
  }

  public void setFree_func(SWIGTYPE_p_f_p_void_p_void__void Free_func) {
    BioAPIJNI.set_BioAPI_MEMORY_FUNCS_Free_func(swigCPtr, SWIGTYPE_p_f_p_void_p_void__void.getCPtr(Free_func));
  }

  public SWIGTYPE_p_f_p_void_p_void__void getFree_func() {
    long cPtr = BioAPIJNI.get_BioAPI_MEMORY_FUNCS_Free_func(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_void_p_void__void(cPtr, false);
  }

  public void setRealloc_func(SWIGTYPE_p_f_p_void_unsigned_int_p_void__p_void Realloc_func) {
    BioAPIJNI.set_BioAPI_MEMORY_FUNCS_Realloc_func(swigCPtr, SWIGTYPE_p_f_p_void_unsigned_int_p_void__p_void.getCPtr(Realloc_func));
  }

  public SWIGTYPE_p_f_p_void_unsigned_int_p_void__p_void getRealloc_func() {
    long cPtr = BioAPIJNI.get_BioAPI_MEMORY_FUNCS_Realloc_func(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_void_unsigned_int_p_void__p_void(cPtr, false);
  }

  public void setCalloc_func(SWIGTYPE_p_f_unsigned_int_unsigned_int_p_void__p_void Calloc_func) {
    BioAPIJNI.set_BioAPI_MEMORY_FUNCS_Calloc_func(swigCPtr, SWIGTYPE_p_f_unsigned_int_unsigned_int_p_void__p_void.getCPtr(Calloc_func));
  }

  public SWIGTYPE_p_f_unsigned_int_unsigned_int_p_void__p_void getCalloc_func() {
    long cPtr = BioAPIJNI.get_BioAPI_MEMORY_FUNCS_Calloc_func(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_unsigned_int_unsigned_int_p_void__p_void(cPtr, false);
  }

  public void setAllocRef(SWIGTYPE_p_void AllocRef) {
    BioAPIJNI.set_BioAPI_MEMORY_FUNCS_AllocRef(swigCPtr, SWIGTYPE_p_void.getCPtr(AllocRef));
  }

  public SWIGTYPE_p_void getAllocRef() {
    long cPtr = BioAPIJNI.get_BioAPI_MEMORY_FUNCS_AllocRef(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_void(cPtr, false);
  }

  public BioAPI_MEMORY_FUNCS() {
    this(BioAPIJNI.new_BioAPI_MEMORY_FUNCS(), true);
  }

}
