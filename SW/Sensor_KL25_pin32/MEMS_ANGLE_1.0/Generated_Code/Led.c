/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Led.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VFM4
**     Component   : BitIO_LDD
**     Version     : Component 01.033, Driver 01.03, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-01-16, 10:27, # CodeGen: 89
**     Abstract    :
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : Led
**          Pin for I/O                                    : TSI0_CH5/PTA4/I2C1_SDA/TPM0_CH1/NMI_b
**          Pin signal                                     : 
**          Direction                                      : Output
**          Initialization                                 : 
**            Init. direction                              : Output
**            Init. value                                  : 0
**            Auto initialization                          : no
**          Safe mode                                      : no
**     Contents    :
**         Init   - LDD_TDeviceData* Led_Init(LDD_TUserData *UserDataPtr);
**         GetVal - bool Led_GetVal(LDD_TDeviceData *DeviceDataPtr);
**         PutVal - void Led_PutVal(LDD_TDeviceData *DeviceDataPtr, bool Val);
**         ClrVal - void Led_ClrVal(LDD_TDeviceData *DeviceDataPtr);
**         SetVal - void Led_SetVal(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file Led.c
** @version 01.03
** @brief
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup Led_module Led module documentation
**  @{
*/         

/* MODULE Led. */

/* {Default RTOS Adapter} No RTOS includes */
#include "Led.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TUserData *UserDataPtr;          /* Pointer to user data */
} Led_TDeviceData;                     /* Device data structure type */

typedef Led_TDeviceData *Led_TDeviceDataPtr ; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static Led_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/*
** ===================================================================
**     Method      :  Led_Init (component BitIO_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" is set to "yes" value then the device is also
**         enabled(see the description of the Enable() method). In this
**         case the Enable() method is not necessary and needn't to be
**         generated. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* Led_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  Led_TDeviceDataPtr DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  /* Configure pin as output */
  /* GPIOA_PDDR: PDD|=0x10 */
  GPIOA_PDDR |= GPIO_PDDR_PDD(0x10);                                   
  /* Set initialization value */
  /* GPIOA_PDOR: PDO&=~0x10 */
  GPIOA_PDOR &= (uint32_t)~(uint32_t)(GPIO_PDOR_PDO(0x10));                                   
  /* Initialization of Port Control register */
  /* PORTA_PCR4: ISF=0,MUX=1 */
  PORTA_PCR4 = (uint32_t)((PORTA_PCR4 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x01)
               ));                                  
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_Led_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}
/*
** ===================================================================
**     Method      :  Led_GetVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Returns the input/output value. If the direction is [input]
**         then the input value of the pin is read and returned. If the
**         direction is [output] then the last written value is read
**         and returned (see <Safe mode> property for limitations).
**         This method cannot be disabled if direction is [input].
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Input or output value. Possible values:
**                           <false> - logical "0" (Low level)
**                           <true> - logical "1" (High level)
*/
/* ===================================================================*/
bool Led_GetVal(LDD_TDeviceData *DeviceDataPtr)
{
  uint32_t PortData;                   /* Port data masked according to the bit used */

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  PortData = GPIO_PDD_GetPortDataOutput(Led_MODULE_BASE_ADDRESS) & Led_PORT_MASK;
  return (PortData != 0U) ? (bool)TRUE : (bool)FALSE;
}

/*
** ===================================================================
**     Method      :  Led_PutVal (component BitIO_LDD)
*/
/*!
**     @brief
**         The specified output value is set. If the direction is <b>
**         input</b>, the component saves the value to a memory or a
**         register and this value will be written to the pin after
**         switching to the output mode (using <tt>SetDir(TRUE)</tt>;
**         see <a href="BitIOProperties.html#SafeMode">Safe mode</a>
**         property for limitations). If the direction is <b>output</b>,
**         it writes the value to the pin. (Method is available only if
**         the direction = <u><tt>output</tt></u> or <u><tt>
**         input/output</tt></u>).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         Val             - Output value. Possible values:
**                           <false> - logical "0" (Low level)
**                           <true> - logical "1" (High level)
*/
/* ===================================================================*/
void Led_PutVal(LDD_TDeviceData *DeviceDataPtr, bool Val)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if (Val) {
    GPIO_PDD_SetPortDataOutputMask(Led_MODULE_BASE_ADDRESS, Led_PORT_MASK);
  } else { /* !Val */
    GPIO_PDD_ClearPortDataOutputMask(Led_MODULE_BASE_ADDRESS, Led_PORT_MASK);
  } /* !Val */
}

/*
** ===================================================================
**     Method      :  Led_ClrVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Clears (set to zero) the output value. It is equivalent to
**         the [PutVal(FALSE)]. This method is available only if the
**         direction = _[output]_ or _[input/output]_.
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure returned by <Init> method.
*/
/* ===================================================================*/
void Led_ClrVal(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  GPIO_PDD_ClearPortDataOutputMask(Led_MODULE_BASE_ADDRESS, Led_PORT_MASK);
}

/*
** ===================================================================
**     Method      :  Led_SetVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Sets (to one) the output value. It is equivalent to the
**         [PutVal(TRUE)]. This method is available only if the
**         direction = _[output]_ or _[input/output]_.
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure returned by <Init> method.
*/
/* ===================================================================*/
void Led_SetVal(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  GPIO_PDD_SetPortDataOutputMask(Led_MODULE_BASE_ADDRESS, Led_PORT_MASK);
}

/* END Led. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
