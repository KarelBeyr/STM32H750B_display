#include "display.h"
#include "appLogic.h"

uint32_t x_size, y_size;
#define LCD_LINE_WIDTH 24

void ClearCache()
{
	// otherwise I get LCD artefacts
	SCB_CleanDCache_by_Addr((void *)SDRAM_DEVICE_ADDR, 480*272*4);
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

void displayPaddedLine(uint16_t y, const char *text)
{
	// the sole purpose of this helper method is to overwrite the whole row so that we do not need to rely on clear screen

    char padded[LCD_LINE_WIDTH];
    memset(padded, ' ', LCD_LINE_WIDTH);

    // Copy up to 24 characters from text
    size_t len = strlen(text);
    if (len > LCD_LINE_WIDTH) len = LCD_LINE_WIDTH;
    memcpy(padded, text, len);

    // Display the padded string
    UTIL_LCD_DisplayStringAt(0, y*32, (uint8_t *)padded, LEFT_MODE);
}

char getCursor(AppContext *ctx)
{
	return ctx->displayCursor ? '_' : ' ';
}

const char* getValueWithCursor(AppContext *ctx) {
    static char result[7];  // adjust size as needed
    if (ctx->inputValue != 0)
        sprintf(result, "%d%c", ctx->inputValue, getCursor(ctx));
    else
        sprintf(result, "%c", getCursor(ctx));
    return result;
}

void DrawCalibrationLine(AppContext *ctx, uint16_t voltage, uint8_t idx)
{
	char buffer[LCD_LINE_WIDTH+1];
    if (ctx->calibrationIndex == idx)
    	sprintf(buffer, "PWM %% for %dV: %s", voltage, getValueWithCursor(ctx));
    else
    	sprintf(buffer, "PWM %% for %dV: %d", voltage, ctx->calibrationPoints[idx]);
    displayPaddedLine(idx+1, buffer);
}

void DisplayRenderState(AppContext *ctx)
{
  char buffer[LCD_LINE_WIDTH+1];

  if (ctx->currentState == STATE_F1) {
	displayPaddedLine(0, "F1: Voltage control");
    if (ctx->isPwmRunning == true) {
        sprintf(buffer, "PWM is running at %dV", ctx->voltage);
        displayPaddedLine(1, buffer);

        sprintf(buffer, "PWM duty %d%%", GetPwmForVoltage(ctx));
        displayPaddedLine(2, buffer);

      displayPaddedLine(3, "Press STOP");
    }
    else if (ctx->isVoltageEntered)
    {
	  sprintf(buffer, "Voltage: %dV", ctx->voltage);
      displayPaddedLine(1, buffer);
      displayPaddedLine(2, "Press START or Clear");
      displayPaddedLine(3, "");
    }
    else
    {
	  sprintf(buffer, "Enter voltage: %s", getValueWithCursor(ctx));
      displayPaddedLine(1, buffer);
      displayPaddedLine(2, "Press Enter");
      displayPaddedLine(3, "");
    }
  }
  else if (ctx->currentState == STATE_F2)
  {
    displayPaddedLine(0, "F2: Calibration");

    DrawCalibrationLine(ctx, 80, 0);
    DrawCalibrationLine(ctx, 200, 1);
    DrawCalibrationLine(ctx, 400, 2);

    uint16_t cx = 50;
    uint16_t cy = 250;
    uint16_t dx = 400;
    uint16_t dy = 80;

    UTIL_LCD_FillRect(cx+1, cy-dy, dx, dy, UTIL_LCD_COLOR_BLACK);
    ClearCache();

    UTIL_LCD_DrawLine(cx, cy, cx+dx, cy, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DrawLine(cx, cy, cx, cy-dy, UTIL_LCD_COLOR_WHITE);

    UTIL_LCD_DrawLine(cx+(dx / 5), cy, cx+(dx / 5), cy-5, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DrawLine(cx+(dx / 2), cy, cx+(dx / 2), cy-5, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DrawLine(cx+dx, cy, cx+dx, cy-5, UTIL_LCD_COLOR_WHITE);

    uint16_t y0 = cy - (ctx->calibrationPoints[0] * dy / 100);
    uint16_t y1 = cy - (ctx->calibrationPoints[1] * dy / 100);
    uint16_t y2 = cy - (ctx->calibrationPoints[2] * dy / 100);

    UTIL_LCD_DrawLine(cx, y0, cx+5, y0, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DrawLine(cx, y1, cx+5, y1, UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DrawLine(cx, y2, cx+5, y2, UTIL_LCD_COLOR_WHITE);

    UTIL_LCD_SetFont(&Font16);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_DisplayStringAt(cx+(dx/5)-15, cy+8, (uint8_t *)"80V", LEFT_MODE);
    UTIL_LCD_DisplayStringAt(cx+(dx/2)-20, cy+8, (uint8_t *)"200V", LEFT_MODE);
    UTIL_LCD_DisplayStringAt(cx+dx-25, cy+8, (uint8_t *)"400V", LEFT_MODE);

    sprintf(buffer, "%d%%", ctx->calibrationPoints[0]);
    UTIL_LCD_DisplayStringAt(cx-35, y0-6, (uint8_t *)buffer,LEFT_MODE);
    sprintf(buffer, "%d%%", ctx->calibrationPoints[1]);
    UTIL_LCD_DisplayStringAt(cx-35, y1-6, (uint8_t *)buffer,LEFT_MODE);
    sprintf(buffer, "%d%%", ctx->calibrationPoints[2]);
    uint16_t shift = 0;
    if (ctx->calibrationPoints[2] == 100) shift = -2;
    UTIL_LCD_DisplayStringAt(cx-35+shift, y2-6, (uint8_t *)buffer,LEFT_MODE);

    UTIL_LCD_DrawLine(cx+(dx / 5), y0, cx+(dx / 2), y1, UTIL_LCD_COLOR_ST_GRAY_LIGHT);
    UTIL_LCD_DrawLine(cx+(dx / 5), y0+1, cx+(dx / 2), y1+1, UTIL_LCD_COLOR_ST_GRAY_LIGHT);

    UTIL_LCD_DrawLine(cx+(dx / 2), y1, cx+dx, y2, UTIL_LCD_COLOR_ST_GRAY_LIGHT);
    UTIL_LCD_DrawLine(cx+(dx / 2), y1+1, cx+dx, y2+1, UTIL_LCD_COLOR_ST_GRAY_LIGHT);

    UTIL_LCD_SetFont(&Font32);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);

    //UTIL_LCD_DrawLine(cx, cy, cx, 140, UTIL_LCD_COLOR_WHITE);
  }
  else if (ctx->currentState == STATE_F3)
  {
	displayPaddedLine(0, "F3: Voltage and current");
    displayPaddedLine(1, "");
    displayPaddedLine(2, "");
    displayPaddedLine(3, "");
  }

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
  displayPaddedLine(4, ctx->message);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);

  ClearCache();
}
