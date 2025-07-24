#include "appLogic.h"

uint32_t lastCursorTime = 0;

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

void stopPWM(AppContext *ctx, CallbackFunction stopPwmCallback) {
  ctx->isPwmRunning = false;
  stopPwmCallback();
}

void startPWM(AppContext *ctx, CallbackWithParam startPwmCallback) {
  ctx->isPwmRunning = true;
  startPwmCallback(ctx->voltage / 4);
}

void setSTATE_F3(AppContext *ctx) {
  ctx->currentState = STATE_F3;
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
    strcpy(ctx->message, "Not in range 80 - 400!");
    clearInput(ctx);
    return;
  }
  ctx->isVoltageEntered = true;
  ctx->voltage = ctx->inputValue;
  ctx->inputValue = 0;
}

void updateInput(AppContext *ctx, KeyboardButton key) {
  uint8_t digit = key - '0';
  if (ctx->inputValue > 40) {
    strcpy(ctx->message, "Input too high!");
    return;
  }
  ctx->inputValue = ctx->inputValue * 10 + digit;
}

bool handle_event(AppContext *ctx, KeyboardButton key, CallbackWithParam startPwmCallback, CallbackFunction stopPwmCallback)
{
  if (key == KEY_NULL)
  {
	  // cursor logic
	  uint32_t now = HAL_GetTick();
	  if (now - lastCursorTime > 500)
	  {
		  ctx->displayCursor = !ctx->displayCursor;
		  lastCursorTime = now;
		  return true;
	  }
	  return false;
  }
  strcpy(ctx->message, "");

  if (ctx->currentState == STATE_F1) {
	if (ctx->isPwmRunning == true)
	{
	  if (key == KEY_Stop) stopPWM(ctx, stopPwmCallback);
	  return false; // when PWM is running, we can only press the "STOP" button
	}

	if (ctx->isVoltageEntered == true) // valid voltage has been entered
	{
	  if (key == KEY_Start) {
		  startPWM(ctx, startPwmCallback);
	  }
      if (key == KEY_Clear) clearVoltage(ctx);
	} else
	{
	  if (key >= KEY_0 && key <= KEY_9) updateInput(ctx, key);
	  if (key == KEY_Enter) validateAndSetVoltage(ctx);
	  if (key == KEY_BkSp) backspace(ctx);
	  if (key == KEY_ESC) clearInput(ctx);
	}

    if (key == KEY_F2) setSTATE_F2(ctx);
    if (key == KEY_F3) setSTATE_F3(ctx);
  }

  if (ctx->currentState == STATE_F2) {
	if (key == KEY_F1) setSTATE_F1(ctx);
	if (key == KEY_F3) setSTATE_F3(ctx);
  }

  if (ctx->currentState == STATE_F3) {
	if (key == KEY_F1) setSTATE_F1(ctx);
	if (key == KEY_F2) setSTATE_F2(ctx);
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
