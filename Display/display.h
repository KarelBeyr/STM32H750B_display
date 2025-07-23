#ifndef D_H_
#define D_H_
#include "main.h"

void Draw_Menu(void);
void InitializeLcd(void);
void UartRenderState(AppContext *ctx);
void UartClearScreen();
void DisplayRenderState(AppContext *ctx);

#endif
