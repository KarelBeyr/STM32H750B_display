/**
  ******************************************************************************
  * @file    Display/LTDC_Paint/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32h750b_discovery.h"
#include "stm32h750b_discovery_lcd.h"
#include "stm32h750b_discovery_ts.h"
#include "stm32h750b_discovery_sdram.h"
#include <stdlib.h>
#include "stm32_lcd.h"
#include "lcd_trace.h"
#include <stdbool.h>

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "usbh_diskio.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define CONVERTED_LINE_BUFFER                    0x24000000

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Touchscreen_Calibration (void);
uint16_t Calibration_GetX(uint16_t x);
uint16_t Calibration_GetY(uint16_t y);
uint8_t IsCalibrationDone(void);

typedef enum {
    STATE_F1,
    STATE_F2,
    STATE_F3,
} AppState;

typedef struct {
  AppState currentState;

	// F1 - screen where user enters voltage and can start/stop PWM
  uint16_t voltage; // register holding voltage that has been validated and is ready to be sent to PWM
  uint16_t inputValue; // register holding current value of "input field"
  bool isVoltageEntered; // flag if we are ready to start PWM. Maybe redundant, we can check against voltage register. But its more robust this way
  bool isPwmRunning;
  bool displayCursor;
  char message[64]; // ad hoc message to display

    // F2 - screen where user sets three calibration points - TODO later
    uint16_t calibration_points[3]; // For mapping
} AppContext;


typedef enum { // A bit atypical, but I want to be able to read data from PC connected through UART for better UX
  KEY_0 = '0',
  KEY_1 = '1',
  KEY_2 = '2',
  KEY_3 = '3',
  KEY_4 = '4',
  KEY_5 = '5',
  KEY_6 = '6',
  KEY_7 = '7',
  KEY_8 = '8',
  KEY_9 = '9',
  KEY_Enter = 'e',
  KEY_Clear = 'c',
  KEY_BkSp = 'b',
  KEY_Start = 'S',
  KEY_Stop = 's',
  KEY_ESC = '`',
  KEY_F1 = '!',
  KEY_F2 = '@',
  KEY_F3 = '#',
  KEY_F4 = '$',
  KEY_F5 = '%',
  KEY_Dot = '.',
  KEY_Lock = 'l',
  KEY_OFF = 'f',
  KEY_ON = 'n',
  KEY_NULL = 'N' // HACK - no key pressed
} KeyboardButton;

#endif /* __MAIN_H */

