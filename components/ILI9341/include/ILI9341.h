#ifndef ILI9341_H_
#define ILI9341_H_

#include <inttypes.h>

#define ILI9341_WIDTH 320
#define ILI9341_HEIGHT 240

void ILI9341_init(void);

void ILI9341_set_buffer(uint16_t buffer[ILI9341_WIDTH * ILI9341_HEIGHT]);

void ILI9341_draw_buffer(void);

void ILI9341_wait_for_draw_complete(void);

#endif // ILI9341_H_
