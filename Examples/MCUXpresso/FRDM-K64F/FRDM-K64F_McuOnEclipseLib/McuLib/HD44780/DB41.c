/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : DB41.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : SDK_BitIO
**     Version     : Component 01.025, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-01-21, 15:52, # CodeGen: 379
**     Abstract    :
**          GPIO component usable with NXP SDK
**     Settings    :
**          Component name                                 : DB41
**          SDK                                            : McuLib
**          GPIO Name                                      : GPIOA
**          PORT Name                                      : PORTA
**          Pin Number                                     : 0
**          Pin Symbol                                     : LED_RED
**          Do Pin Muxing                                  : no
**          Init Direction                                 : Output
**          Pull Resistor                                  : no pull resistor
**          Init Value                                     : 0
**     Contents    :
**         GetDir    - bool DB41_GetDir(void);
**         SetDir    - void DB41_SetDir(bool Dir);
**         SetInput  - void DB41_SetInput(void);
**         SetOutput - void DB41_SetOutput(void);
**         GetVal    - bool DB41_GetVal(void);
**         PutVal    - void DB41_PutVal(bool Val);
**         ClrVal    - void DB41_ClrVal(void);
**         SetVal    - void DB41_SetVal(void);
**         NegVal    - void DB41_NegVal(void);
**         Init      - void DB41_Init(void);
**         Deinit    - void DB41_Deinit(void);
**
** * Copyright (c) 2015-2019, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file DB41.h
** @version 01.00
** @brief
**          GPIO component usable with NXP SDK
*/         
/*!
**  @addtogroup DB41_module DB41 module documentation
**  @{
*/         

/* MODULE DB41. */

#include "DB41.h"
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if DB41_CONFIG_DO_PIN_MUXING
  #include "fsl_port.h" /* include SDK header file for port muxing */
  #endif
  #include "fsl_gpio.h" /* include SDK header file for GPIO */
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  #include "fsl_gpio_driver.h" /* include SDK header file for GPIO */
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  #include "pins_gpio_hw_access.h"
  #include "pins_driver.h" /* include SDK header file for GPIO */
#else
  #error "Unsupported SDK!"
#endif

#if McuLib_CONFIG_NXP_SDK_2_0_USED

  static const gpio_pin_config_t DB41_configOutput = {
    kGPIO_DigitalOutput,  /* use as output pin */
    DB41_CONFIG_INIT_PIN_VALUE,  /* initial value */
  };

  static const gpio_pin_config_t DB41_configInput = {
    kGPIO_DigitalInput,  /* use as input pin */
    DB41_CONFIG_INIT_PIN_VALUE,  /* initial value */
  };
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  const gpio_output_pin_user_config_t DB41_OutputConfig[] = {
    {
      .pinName = DB41_CONFIG_PIN_SYMBOL,
      .config.outputLogic = DB41_CONFIG_INIT_PIN_VALUE,
    #if FSL_FEATURE_PORT_HAS_SLEW_RATE
      .config.slewRate = kPortSlowSlewRate,
    #endif
    #if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
      .config.isOpenDrainEnabled = true,
    #endif
    #if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
      .config.driveStrength = kPortLowDriveStrength,
    #endif
    },
    {
      .pinName = GPIO_PINS_OUT_OF_RANGE,
    }
  };

  const gpio_input_pin_user_config_t DB41_InputConfig[] = {
    {
      .pinName = DB41_CONFIG_PIN_SYMBOL,
    #if FSL_FEATURE_PORT_HAS_PULL_ENABLE
      #if DB41_CONFIG_PULL_RESISTOR==0 /* 0: no pull resistor, 1: pull-up, 2: pull-down, 3: pull-up or no pull, 4: pull-down or no pull: 4: autoselect-pull */
      .config.isPullEnable = false,
      #else
      .config.isPullEnable = true,
      #endif
    #endif
    #if FSL_FEATURE_PORT_HAS_PULL_SELECTION
      #if DB41_CONFIG_PULL_RESISTOR==1
      .config.pullSelect = kPortPullUp,
      #else
      .config.pullSelect = kPortPullDown,
      #endif
    #endif
    #if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
      .config.isPassiveFilterEnabled = true,
    #endif
    #if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
      .config.isDigitalFilterEnabled = true,
    #endif
    #if FSL_FEATURE_GPIO_HAS_INTERRUPT_VECTOR
      .config.interrupt = kPortIntDisabled
    #endif
    },
    {
      .pinName = GPIO_PINS_OUT_OF_RANGE,
    }
  };
#endif

static bool DB41_isOutput = false;
/*
** ===================================================================
**     Method      :  ClrVal (component SDK_BitIO)
**
**     Description :
**         Clears the pin value (sets it to a low level)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DB41_ClrVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  GPIO_PortClear(DB41_CONFIG_GPIO_NAME, 1<<DB41_CONFIG_PIN_NUMBER);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_ClearPinOutput(DB41_CONFIG_PIN_SYMBOL);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  PINS_GPIO_WritePin(DB41_CONFIG_PORT_NAME, DB41_CONFIG_PIN_NUMBER, 0);
#endif
}

/*
** ===================================================================
**     Method      :  SetVal (component SDK_BitIO)
**
**     Description :
**         Sets the pin value to a high value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DB41_SetVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  GPIO_PortSet(DB41_CONFIG_GPIO_NAME, 1<<DB41_CONFIG_PIN_NUMBER);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_SetPinOutput(DB41_CONFIG_PIN_SYMBOL);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  PINS_GPIO_WritePin(DB41_CONFIG_PORT_NAME, DB41_CONFIG_PIN_NUMBER, 1);
#endif
}

/*
** ===================================================================
**     Method      :  NegVal (component SDK_BitIO)
**
**     Description :
**         Toggles/negates the pin value
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DB41_NegVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  GPIO_PortToggle(DB41_CONFIG_GPIO_NAME, 1<<DB41_CONFIG_PIN_NUMBER);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_TogglePinOutput(DB41_CONFIG_PIN_SYMBOL);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  pins_channel_type_t val;

  val = PINS_GPIO_GetPinsOutput(DB41_CONFIG_PORT_NAME);
  if (val&(1<<DB41_CONFIG_PIN_NUMBER)) {
    PINS_GPIO_WritePin(DB41_CONFIG_PORT_NAME, DB41_CONFIG_PIN_NUMBER, 0);
  } else {
    PINS_GPIO_WritePin(DB41_CONFIG_PORT_NAME, DB41_CONFIG_PIN_NUMBER, 1);
  }
#endif
}

/*
** ===================================================================
**     Method      :  GetVal (component SDK_BitIO)
**
**     Description :
**         Returns the pin value
**     Parameters  : None
**     Returns     :
**         ---             - Returns the value of the pin:
**                           FALSE/logical level '0' or TRUE/logical
**                           level '1'
** ===================================================================
*/
bool DB41_GetVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  return GPIO_ReadPinInput(DB41_CONFIG_GPIO_NAME, DB41_CONFIG_PIN_NUMBER)!=0;
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  return GPIO_DRV_ReadPinInput(DB41_CONFIG_PIN_SYMBOL)!=0;
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  return (PINS_DRV_ReadPins(DB41_CONFIG_PORT_NAME)&(1<<DB41_CONFIG_PIN_NUMBER))!=0;
#else
  return FALSE;
#endif
}

/*
** ===================================================================
**     Method      :  GetDir (component SDK_BitIO)
**
**     Description :
**         Return the direction of the pin (input/output)
**     Parameters  : None
**     Returns     :
**         ---             - FALSE if port is input, TRUE if port is
**                           output
** ===================================================================
*/
bool DB41_GetDir(void)
{
  return DB41_isOutput;
}

/*
** ===================================================================
**     Method      :  SetDir (component SDK_BitIO)
**
**     Description :
**         Sets the direction of the pin (input or output)
**     Parameters  :
**         NAME            - DESCRIPTION
**         Dir             - FALSE: input, TRUE: output
**     Returns     : Nothing
** ===================================================================
*/
void DB41_SetDir(bool Dir)
{
  if (Dir) {
    DB41_SetOutput();
  } else {
    DB41_SetInput();
  }
}

/*
** ===================================================================
**     Method      :  SetInput (component SDK_BitIO)
**
**     Description :
**         Sets the pin as input
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DB41_SetInput(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  GPIO_PinInit(DB41_CONFIG_GPIO_NAME, DB41_CONFIG_PIN_NUMBER, &DB41_configInput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_SetPinDir(DB41_CONFIG_PIN_SYMBOL, kGpioDigitalInput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  pins_channel_type_t val;

  val = PINS_GPIO_GetPinsDirection(DB41_CONFIG_PORT_NAME); /* bit 0: pin is input; 1: pin is output */
  val &= ~(1<<DB41_CONFIG_PIN_NUMBER); /* clear bit ==> input */
  PINS_DRV_SetPinsDirection(DB41_CONFIG_PORT_NAME, val);
#endif
  DB41_isOutput = false;
}

/*
** ===================================================================
**     Method      :  SetOutput (component SDK_BitIO)
**
**     Description :
**         Sets the pin as output
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DB41_SetOutput(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  GPIO_PinInit(DB41_CONFIG_GPIO_NAME, DB41_CONFIG_PIN_NUMBER, &DB41_configOutput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_SetPinDir(DB41_CONFIG_PIN_SYMBOL, kGpioDigitalOutput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  pins_channel_type_t val;

  val = PINS_GPIO_GetPinsDirection(DB41_CONFIG_PORT_NAME); /* bit 0: pin is input; 1: pin is output */
  val |= (1<<DB41_CONFIG_PIN_NUMBER); /* set bit ==> output */
  PINS_DRV_SetPinsDirection(DB41_CONFIG_PORT_NAME, val);
#endif
  DB41_isOutput = true;
}

/*
** ===================================================================
**     Method      :  PutVal (component SDK_BitIO)
**
**     Description :
**         Sets the pin value
**     Parameters  :
**         NAME            - DESCRIPTION
**         Val             - Value to set. FALSE/logical '0' or
**                           TRUE/logical '1'
**     Returns     : Nothing
** ===================================================================
*/
void DB41_PutVal(bool Val)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  if (Val) {
    GPIO_SetPinsOutput(DB41_CONFIG_GPIO_NAME, 1<<DB41_CONFIG_PIN_NUMBER);
  } else {
    GPIO_ClearPinsOutput(DB41_CONFIG_GPIO_NAME, 1<<DB41_CONFIG_PIN_NUMBER);
  }
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_WritePinOutput(DB41_CONFIG_PIN_SYMBOL, Val);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  PINS_DRV_WritePin(DB41_CONFIG_PORT_NAME, DB41_CONFIG_PIN_NUMBER, Val);
#endif
}

/*
** ===================================================================
**     Method      :  Init (component SDK_BitIO)
**
**     Description :
**         Driver initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DB41_Init(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if DB41_CONFIG_DO_PIN_MUXING
  PORT_SetPinMux(DB41_CONFIG_PORT_NAME, DB41_CONFIG_PIN_NUMBER, kPORT_MuxAsGpio); /* mux as GPIO */
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  /*! \todo Pin Muxing not implemented */
  GPIO_DRV_Init(DB41_InputConfig, DB41_OutputConfig);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  /* the following needs to be called in the application first:
  PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
  */
#endif
#if DB41_CONFIG_INIT_PIN_DIRECTION == DB41_CONFIG_INIT_PIN_DIRECTION_INPUT
  DB41_SetInput();
#elif DB41_CONFIG_INIT_PIN_DIRECTION == DB41_CONFIG_INIT_PIN_DIRECTION_OUTPUT
  DB41_SetOutput();
#endif
}

/*
** ===================================================================
**     Method      :  Deinit (component SDK_BitIO)
**
**     Description :
**         Driver de-initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DB41_Deinit(void)
{
  /* nothing needed */
}

/* END DB41. */

/*!
** @}
*/