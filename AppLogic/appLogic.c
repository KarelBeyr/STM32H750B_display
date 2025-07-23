#include "appLogic.h"


void clearInput(AppContext *ctx) {
  ctx->inputValue = 0;
}

void clearVoltage(AppContext *ctx) {
  ctx->voltage = 0;
  ctx->isVoltageEntered = false;
}

void backspace(AppContext *ctx) {
  ctx->inputValue = ctx->inputValue / 10;
}

void stopPWM(AppContext *ctx) {
  ctx->isPwmRunning = false;
  //__HAL_TIM_SET_COMPARE(&htim11, TIM_CHANNEL_1, 0);
  // TODO callbakc
}

void startPWM(AppContext *ctx) {
  ctx->isPwmRunning = true;
  //__HAL_TIM_SET_COMPARE(&htim11, TIM_CHANNEL_1, ctx->voltage / 4);
  // TODO callbakc
}

void setSTATE_F2(AppContext *ctx) {
  ctx->currentState = STATE_F2;
}

void setSTATE_F1(AppContext *ctx) {
  ctx->currentState = STATE_F1;
}

void validateAndSetVoltage(AppContext *ctx) {
  if (ctx->inputValue < 80 || ctx->inputValue > 400)
  {
    strcpy(ctx->message, "Input voltage has to be in range 80 - 400. Resetting, try again!");
    clearInput(ctx);
    return;
  }
  ctx->isVoltageEntered = true;
  ctx->voltage = ctx->inputValue;
  ctx->inputValue = 0;
  sprintf(ctx->message, "Voltage %d has been successfully entered", ctx->voltage);

}

void updateInput(AppContext *ctx, KeyboardButton key) {
  uint8_t digit = key - '0';
  ctx->inputValue = ctx->inputValue * 10 + digit;
  if (ctx->inputValue > 400) {
    strcpy(ctx->message, "Input set too high, resetting. Try again");
    clearInput(ctx);
  }
}

bool handle_event(AppContext *ctx, KeyboardButton key)
{
  if (key == KEY_NULL) return false;;
  strcpy(ctx->message, "");

  if (ctx->currentState == STATE_F1) {
	if (ctx->isPwmRunning == true)
	{
	  if (key == KEY_Stop) stopPWM(ctx);
	  return false; // when PWM is running, we can only press the "STOP" button
	}

	if (ctx->isVoltageEntered == true) // valid voltage has been entered
	{
	  if (key == KEY_Start) startPWM(ctx);
	}

	if (key >= KEY_0 && key <= KEY_9) updateInput(ctx, key);
	if (key == KEY_Clear) clearVoltage(ctx);
	if (key == KEY_Enter) validateAndSetVoltage(ctx);
	if (key == KEY_BkSp) backspace(ctx);
	if (key == KEY_F2) setSTATE_F2(ctx);
	if (key == KEY_ESC) clearInput(ctx);
  }

  if (ctx->currentState == STATE_F2) {
	if (key == KEY_F1) setSTATE_F1(ctx);
  }
  return true;
}

void InitializeAppContext(AppContext* ctx) {
	ctx->currentState = STATE_F1;
	ctx->isVoltageEntered = false;
	ctx->isPwmRunning = false;
	ctx->voltage = 0;
	ctx->inputValue = 0;
}
