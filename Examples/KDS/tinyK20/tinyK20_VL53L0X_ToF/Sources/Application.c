/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "VL53L0X.h"
#include "LED1.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "PORT_PDD.h"

void APP_Start(void) {
  uint8_t val=0;
  int16_t range;
  uint8_t res;
  uint16_t ambient;
  float lux;
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  /* need pull-up on UART Rx pin (PTC3) */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 3, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 3, PORT_PDD_PULL_ENABLE);
  VL_Init(); /* initialize sensor driver */
  res = VL_InitAndConfigureDevice(VL6180X_DEFAULT_I2C_ADDRESS);
  if (res!=ERR_OK) {
    CLS1_SendStr("ERROR: Failed init of TOF device: ", io->stdErr);
    CLS1_SendNum8u(VL6180X_DEFAULT_I2C_ADDRESS, io->stdErr);
    CLS1_SendStr("\r\n", io->stdErr);
  }
  for(;;) {

    LED1_Neg();
    WAIT1_Waitms(500);
  }
}
