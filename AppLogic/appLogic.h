#ifndef AL_H_
#define AL_H_
#include "main.h"

bool handle_event(AppContext *ctx, KeyboardButton key, CallbackWithParam startPwmCallback, CallbackFunction stopPwmCallback);
void InitializeAppContext(AppContext* ctx);

#endif
