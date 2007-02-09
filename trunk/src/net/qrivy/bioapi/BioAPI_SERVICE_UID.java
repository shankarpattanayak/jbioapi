/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.24
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package net.qrivy.bioapi;

public class BioAPI_SERVICE_UID {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected BioAPI_SERVICE_UID(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(BioAPI_SERVICE_UID obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      BioAPIJNI.delete_BioAPI_SERVICE_UID(swigCPtr);
    }
    swigCPtr = 0;
  }

  public void setUuid(SWIGTYPE_p_unsigned_char Uuid) {
    BioAPIJNI.set_BioAPI_SERVICE_UID_Uuid(swigCPtr, SWIGTYPE_p_unsigned_char.getCPtr(Uuid));
  }

  public SWIGTYPE_p_unsigned_char getUuid() {
    long cPtr = BioAPIJNI.get_BioAPI_SERVICE_UID_Uuid(swigCPtr);
    return (cPtr == 0) ? null : new SWIGTYPE_p_unsigned_char(cPtr, false);
  }

  public void setVersion(BioAPI_VERSION Version) {
    BioAPIJNI.set_BioAPI_SERVICE_UID_Version(swigCPtr, BioAPI_VERSION.getCPtr(Version));
  }

  public BioAPI_VERSION getVersion() {
    long cPtr = BioAPIJNI.get_BioAPI_SERVICE_UID_Version(swigCPtr);
    return (cPtr == 0) ? null : new BioAPI_VERSION(cPtr, false);
  }

  public void setDeviceId(long DeviceId) {
    BioAPIJNI.set_BioAPI_SERVICE_UID_DeviceId(swigCPtr, DeviceId);
  }

  public long getDeviceId() {
    return BioAPIJNI.get_BioAPI_SERVICE_UID_DeviceId(swigCPtr);
  }

  public void setReserved(long Reserved) {
    BioAPIJNI.set_BioAPI_SERVICE_UID_Reserved(swigCPtr, Reserved);
  }

  public long getReserved() {
    return BioAPIJNI.get_BioAPI_SERVICE_UID_Reserved(swigCPtr);
  }

  public BioAPI_SERVICE_UID() {
    this(BioAPIJNI.new_BioAPI_SERVICE_UID(), true);
  }

}
