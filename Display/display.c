#include "display.h"

uint32_t x_size, y_size;

void Draw_Menu(void)
{
  UTIL_LCD_SetLayer(0);

  UTIL_LCD_Clear(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetFont(&Font32);
  for (int i = 0; i < 8; i++) {
	  UTIL_LCD_DisplayStringAt(0, i * 32, (uint8_t *)"Bumbajs ubumbananej3", LEFT_MODE);
  }
}

void InitializeLcd(void)
{
  /* Initialize the LCD */
  BSP_LCD_Init(0, LCD_ORIENTATION_LANDSCAPE);
  UTIL_LCD_SetFuncDriver(&LCD_Driver);

  /* Set Foreground Layer */
  UTIL_LCD_SetLayer(0);

  /* Clear the LCD Background layer */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_BLACK);
  BSP_LCD_GetXSize(0, &x_size);
  BSP_LCD_GetYSize(0, &y_size);
}
