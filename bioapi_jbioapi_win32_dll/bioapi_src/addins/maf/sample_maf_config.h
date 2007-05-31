/*-----------------------------------------------------------------------
 * File: SAMPLE MAF_CONFIG.H
 *-----------------------------------------------------------------------
 */


#ifndef MAF_CONFIG_H
#define MAF_CONFIG_H

/* UUID of the addin module */
#define ADDIN_UUID							(intel_ff_dsm_uuid)

/* Major version of the addin module */
#define ADDIN_VERSION_MAJOR					1

/* Minor version of the addin module */
#define ADDIN_VERSION_MINOR					0

/* Is the addin module thread safe? */
#define ADDIN_THREAD_SAFE					1

/* Does the addin module require the writer lock during SPI functions on the load
 * tracker node (is this node being modified?) */
#define ADDIN_NEED_LOAD_WRITER_LOCK			0

/* Does the addin module require the writer lock during SPI functions on the attach
 * tracker node (is this node being modified?) */
#define ADDIN_NEED_ATTACH_WRITER_LOCK		0

/* Does the addin module require the custom ADDIN_LOAD_DATA structure (see below) */
#define ADDIN_NEED_ADDIN_LOAD_STRUCT		0

/* Does the addin module require the custom ADDIN_ATTACH_DATA structure (see below) */
#define ADDIN_NEED_ADDIN_ATTACH_STRUCT		0

/* Macro used to define if a device is valid for an addin */
#define ADDIN_IS_VALID_DEVICE(DeviceId)		((DeviceId) == 0)

#if (ADDIN_NEED_ADDIN_LOAD_STRUCT)
/*-----------------------------------------------------------------------------
 * Description:
 * Structure containing custom fields in the BioAPI_MODULE_LOAD_TRACKER structure
 *---------------------------------------------------------------------------*/
struct addin_load_data
{
	/* put custom fields here */
};
typedef struct addin_load_data ADDIN_LOAD_DATA;

#endif /* if ADDIN_NEED_ADDIN_LOAD_STRUCT */


#if (ADDIN_NEED_ADDIN_ATTACH_STRUCT)

/*-----------------------------------------------------------------------------
 * Description:
 * Structure containing custom fields in the BioAPI_MODULE_ATTACH_TRACKER structure
 *---------------------------------------------------------------------------*/
struct addin_attach_data
{
	/* put custom fields here */
};
typedef struct addin_attach_data ADDIN_ATTACH_DATA;

#endif /* if ADDIN_NEED_ADDIN_ATTACH_STRUCT */

#endif
