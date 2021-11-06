/* SPI Master example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "../components/ILI9341/include/ILI9341.h"
#include <stdlib.h>
#include <math.h>
#include "esp_timer.h"
#include "esp_system.h"

void app_main(void)
{
    ILI9341_init();

    uint16_t* buffer = malloc(ILI9341_WIDTH * ILI9341_HEIGHT * sizeof(uint16_t));

    while(1)
    {
		for(int i = 0; i < ILI9341_HEIGHT * ILI9341_WIDTH; i++)
		{
			buffer[i] = rand();
		}

		ILI9341_draw_buffer(buffer);

		ILI9341_wait_for_draw_complete();
    }
}
