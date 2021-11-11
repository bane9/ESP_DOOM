#include "doomgeneric.h"
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "doomkeys.h"

uint16_t* DG_ScreenBuffer;
static uint32_t time_since_last_key;

void DG_Init()
{
	esp_timer_init();

	time_since_last_key = DG_GetTicksMs();

	ILI9341_init();

	DG_ScreenBuffer = calloc(ILI9341_WIDTH * ILI9341_HEIGHT, sizeof(uint16_t));


	ILI9341_set_buffer(DG_ScreenBuffer);
}

static int drew_first_frame = 0;

void DG_DrawFrame()
{
	ILI9341_draw_buffer();

	ILI9341_wait_for_draw_complete();

	drew_first_frame = 1;
}

void DG_SleepMs(uint32_t ms)
{
	vTaskDelay(ms / portTICK_RATE_MS);
}

uint32_t DG_GetTicksMs()
{
	return esp_timer_get_time() / 1000;
}

const int a[][2] = {
		{KEY_ENTER,         1},
		{KEY_ENTER,         0},
		{KEY_ENTER,         1},
		{KEY_ENTER,         0},
		{KEY_ENTER,         1},
		{KEY_ENTER,         0},
		{KEY_ENTER,         1},
		{KEY_ENTER,         0},
		{KEY_ENTER,         1},
		{KEY_ENTER,         0},
};
int index1 = 0;

int DG_GetKey(int* pressed, unsigned char* key)
{
	if(!drew_first_frame)
	{
		return 0;
	}
	if(index1 == sizeof(a) / sizeof(a[0]))
	{
		return 0;
	}
	if(DG_GetTicksMs() - time_since_last_key > 100)
	{
		*pressed = a[index1][1];
		*key = a[index1][0];
		time_since_last_key = DG_GetTicksMs();
		++index1;
		return 1;
	}
	return 0;
}

void DG_SetWindowTitle(const char * title)
{

}
