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

void uartSetCursorPosition(int row, int col) {
  printf("\033[%d;%dH", row, col);
}

void uartClearScreen() {
  printf("\033[2J");
  printf("\033[H"); // Move cursor to top-left corner
}

void UartRenderState(AppContext *ctx) {
  uartClearScreen();
  uartSetCursorPosition(1, 1);
  if (ctx->currentState == STATE_F1) {
    printf("Voltage control");
    uartSetCursorPosition(2, 1);
    printf("Current input: %d", ctx->inputValue);
    uartSetCursorPosition(3, 1);
    if (ctx->voltage > 0) {
      printf("Voltage: %dV", ctx->voltage);
    } else {
      printf("Voltage: N/A");
    }
    uartSetCursorPosition(4, 1);
    if (ctx->isPwmRunning == true) {
      printf("PWM is running at %dV", ctx->voltage);
    } else {
      printf("PWM is OFF");
    }
    uartSetCursorPosition(5, 1);
    printf(ctx->message);
  }

  uartSetCursorPosition(7, 1);
}
