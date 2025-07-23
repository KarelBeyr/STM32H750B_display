#include "display.h"

uint32_t x_size, y_size;

void ClearCache()
{
	// otherwise I get LCD artefacts
	SCB_CleanDCache_by_Addr(SDRAM_DEVICE_ADDR, 480*272*4);
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

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetFont(&Font32);
}

void uartSetCursorPosition(int row, int col) {
  printf("\033[%d;%dH", row, col);
}

void UartClearScreen() {
  printf("\033[2J");
  printf("\033[H"); // Move cursor to top-left corner
}

void UartRenderState(AppContext *ctx) {
  uartSetCursorPosition(1, 1);
  if (ctx->currentState == STATE_F1) {
    printf("F1: Voltage control    ");
    uartSetCursorPosition(2, 1);
    printf("Current input: %d     ", ctx->inputValue);
    uartSetCursorPosition(3, 1);
    if (ctx->voltage > 0) {
      printf("Voltage: %dV     ", ctx->voltage);
    } else {
      printf("Voltage: N/A     ");
    }
    uartSetCursorPosition(4, 1);
    if (ctx->isPwmRunning == true) {
      printf("PWM is running at %dV   ", ctx->voltage);
    } else {
      printf("PWM is OFF              ");
    }
    uartSetCursorPosition(5, 1);
    printf("%s                                                               \r\n", ctx->message);
  }
}

void DisplayRenderState(AppContext *ctx)
{
  UTIL_LCD_Clear(UTIL_LCD_COLOR_BLACK);

  if (ctx->currentState == STATE_F1) {
	char buffer[32];  // Make sure it's large enough
    UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"F1: Voltage control    ", LEFT_MODE);
    sprintf(buffer, "Current input: %d", ctx->inputValue);
    UTIL_LCD_DisplayStringAt(0, 32, (uint8_t *)buffer, LEFT_MODE);

    sprintf(buffer, "Current input: %d", ctx->inputValue);
    UTIL_LCD_DisplayStringAt(0, 32, (uint8_t *)buffer, LEFT_MODE);

    if (ctx->voltage > 0) {
      sprintf(buffer, "Voltage: %dV", ctx->voltage);
    } else {
      strcpy(buffer, "Voltage: N/A");
    }
    UTIL_LCD_DisplayStringAt(0, 64, (uint8_t *)buffer, LEFT_MODE);

    if (ctx->isPwmRunning == true) {
      sprintf(buffer, "PWM is running at %dV", ctx->voltage);
    } else {
      strcpy(buffer, "PWM is OFF");
    }
    UTIL_LCD_DisplayStringAt(0, 96, (uint8_t *)buffer, LEFT_MODE);

    UTIL_LCD_DisplayStringAt(0, 128, (uint8_t *)ctx->message, LEFT_MODE);

    ClearCache();


//    uartSetCursorPosition(5, 1);
//    printf("%s                                                               \r\n", ctx->message);
  }
}
