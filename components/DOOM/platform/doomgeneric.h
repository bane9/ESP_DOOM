#ifndef DOOM_GENERIC
#define DOOM_GENERIC

#include <stdlib.h>
#include <stdint.h>

#include "../../ILI9341/include/ILI9341.h"

#define DOOMGENERIC_RESX ILI9341_WIDTH
#define DOOMGENERIC_RESY ILI9341_HEIGHT


extern uint16_t* DG_ScreenBuffer;


void DG_Init();
void DG_DrawFrame();
void DG_SleepMs(uint32_t ms);
uint32_t DG_GetTicksMs();
int DG_GetKey(int* pressed, unsigned char* key);
void DG_SetWindowTitle(const char * title);

#endif //DOOM_GENERIC
