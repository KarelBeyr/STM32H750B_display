#ifndef FLEXIKEYBOARD_FLEXIKEYBOARD_H_
#define FLEXIKEYBOARD_FLEXIKEYBOARD_H_


#include "main.h"

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
  KEY_ON = 'n'
} KeyboardButton;

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} GPIOPin;

#define NUM_ROWS 5
#define NUM_COLS 5





void ReadFlexiKeyboard(void);
void InitFlexiKeyboard(void);


#endif /* FLEXIKEYBOARD_FLEXIKEYBOARD_H_ */
