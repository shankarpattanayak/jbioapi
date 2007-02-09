all-binSetup:
	test -d bin || $(mkdir_p) bin || exit 1

libjbioapilibdir=$(libdir)
libjbioapilib_LTLIBRARIES = libjbioapi.la
libjbioapi_la_SOURCES = jbioapi_wrap.c extra.c bioapi_api.h bioapi_schema.h bioapi_util.h net_qrivy_bioapi_BioAPI.h bioapi_err.h  bioapi_typecast.h  bioapi_uuid.h bioapi.h bioapi_type.h biospi_type.h
#jbioapi_wrap_c_SOURCES = jbioapi.i
EXTRA_DIST = jbioapi.i
libjbioapi_la_LDFLAGS = -module -version-info 0:0:0
#JAVAROOT=../bin
jbioapisources = net/qrivy/bioapi/BioAPI_BIR_ARRAY_POPULATION.java \
net/qrivy/bioapi/BioAPI_BIR_BIOMETRIC_DATA_FORMAT.java \
net/qrivy/bioapi/BioAPI_BIR_HEADER.java \
net/qrivy/bioapi/BioAPI_BIR.java \
net/qrivy/bioapi/BioAPI_BSP_SCHEMA.java \
net/qrivy/bioapi/BioAPI_CANDIDATE_BIR.java \
net/qrivy/bioapi/BioAPI_CANDIDATE.java \
net/qrivy/bioapi/BioAPIConstants.java \
net/qrivy/bioapi/BioAPI_DATA.java \
net/qrivy/bioapi/BioAPI_DBBIR_ID.java \
net/qrivy/bioapi/BioAPI_FUNC_NAME_ADDR.java \
net/qrivy/bioapi/BioAPI_GUI_BITMAP.java \
net/qrivy/bioapi/BioAPI_IDENTIFY_POPULATION_BIRs.java \
net/qrivy/bioapi/BioAPI_IDENTIFY_POPULATION.java \
net/qrivy/bioapi/BioAPI_INPUT_BIR_InputBIR.java \
net/qrivy/bioapi/BioAPI_INPUT_BIR.java \
net/qrivy/bioapi/BioAPI.java \
net/qrivy/bioapi/BioAPIJNI.java \
net/qrivy/bioapi/BioAPI_MEMORY_FUNCS.java \
net/qrivy/bioapi/BioAPI_SERVICE_UID.java \
net/qrivy/bioapi/BioAPI_VERSION.java \
net/qrivy/bioapi/SchemaArray.java \
net/qrivy/bioapi/SWIGTYPE_p_a_16__unsigned_char.java \
net/qrivy/bioapi/SWIGTYPE_p_f_p_q_const__a_16__unsigned_char_p_void_unsigned_int_unsigned_int_unsigned_int__unsigned_int.java \
net/qrivy/bioapi/SWIGTYPE_p_f_p_void_p_void__void.java \
net/qrivy/bioapi/SWIGTYPE_p_f_p_void_unsigned_int_p_void__p_void.java \
net/qrivy/bioapi/SWIGTYPE_p_f_unsigned_int_p_void__p_void.java \
net/qrivy/bioapi/SWIGTYPE_p_f_unsigned_int_unsigned_int_p_void__p_void.java \
net/qrivy/bioapi/SWIGTYPE_p_f___void.java \
net/qrivy/bioapi/SWIGTYPE_p_int.java \
net/qrivy/bioapi/SWIGTYPE_p_p_bioapi_data.java \
net/qrivy/bioapi/SWIGTYPE_p_p_bioapi_hrs_bir.java \
net/qrivy/bioapi/SWIGTYPE_p_p_p_bioapi_candidate.java \
net/qrivy/bioapi/SWIGTYPE_p_unsigned_char.java \
net/qrivy/bioapi/SWIGTYPE_p_unsigned_int.java \
net/qrivy/bioapi/SWIGTYPE_p_void.java \
net/qrivy/bioapi/verifyResult.java \
net/qrivy/jbioapi/BioApiException.java \
net/qrivy/jbioapi/BiometricServiceProvider.java \
net/qrivy/jbioapi/BiometricLoginModule.java \
net/qrivy/jbioapi/BiometricsFramework.java
dist_noinst_JAVA = Test.java $(jbioapisources)
jbioapiJardir = $(libdir)
jbioapiJar_DATA = jbioapi.jar
jbioapi.jar : $(jbioapisources)
	jar cvf jbioapi.jar ../net/
#	jar cvf jbioapi.jar -C $(JAVAROOT) net/
mostlyclean-local:
	rm jbioapi.jar
