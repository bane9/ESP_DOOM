#include "doomgeneric.h"
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


uint16_t* DG_ScreenBuffer;

void DG_Init()
{
	esp_timer_init();

	ILI9341_init();

	DG_ScreenBuffer = malloc(ILI9341_WIDTH * ILI9341_HEIGHT * sizeof(uint16_t));

	ILI9341_set_buffer(DG_ScreenBuffer);
}

void DG_DrawFrame()
{
	ILI9341_draw_buffer();

	ILI9341_wait_for_draw_complete();
}

void DG_SleepMs(uint32_t ms)
{
	vTaskDelay(ms / portTICK_RATE_MS);
}

uint32_t DG_GetTicksMs()
{
	return esp_timer_get_time() * 1000;
}

int DG_GetKey(int* pressed, unsigned char* key)
{
	return 0;
}

void DG_SetWindowTitle(const char * title)
{

}
