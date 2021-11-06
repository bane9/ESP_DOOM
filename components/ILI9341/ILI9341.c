#include "ILI9341.h"

#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "soc/gpio_struct.h"
#include "driver/gpio.h"

#define PIN_NUM_MISO 25
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  19
#define PIN_NUM_CS   22

#define PIN_NUM_DC   21
#define PIN_NUM_RST  18
#define PIN_NUM_BCKL 5

#define SPI_QUEUE_SIZE 6

typedef struct
{
    uint8_t cmd;
    uint8_t data[16];
    uint8_t databytes;
} lcd_init_cmd_t;

static spi_transaction_t transaction[SPI_QUEUE_SIZE];

DRAM_ATTR static const lcd_init_cmd_t ili_init_cmds[] =
{
    {0xCF, {0x00, 0x83, 0X30}, 3},
    {0xED, {0x64, 0x03, 0X12, 0X81}, 4},
    {0xE8, {0x85, 0x01, 0x79}, 3},
    {0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
    {0xF7, {0x20}, 1},
    {0xEA, {0x00, 0x00}, 2},
    {0xC0, {0x26}, 1},
    {0xC1, {0x11}, 1},
    {0xC5, {0x35, 0x3E}, 2},
    {0xC7, {0xBE}, 1},
    {0x36, {0x28}, 1},
    {0x3A, {0x55}, 1},
    {0xB1, {0x00, 0x1B}, 2},
    {0xF2, {0x08}, 1},
    {0x26, {0x01}, 1},
    {0xE0, {0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00}, 15},
    {0XE1, {0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F}, 15},
    {0x2A, {0x00, 0x00, 0x00, 0xEF}, 4},
    {0x2B, {0x00, 0x00, 0x01, 0x3f}, 4},
    {0x2C, {0}, 0},
    {0xB7, {0x07}, 1},
    {0xB6, {0x0A, 0x82, 0x27, 0x00}, 4},
    {0x11, {0}, 0x80},
    {0x29, {0}, 0x80},
    {0, {0}, 0xff},
};


static void lcd_cmd(spi_device_handle_t spi, const uint8_t cmd)
{
    esp_err_t ret;
    spi_transaction_t t;

    memset(&t, 0, sizeof(t));

    t.length = 8;
    t.tx_buffer = &cmd;
    t.user=(void*) 0;
    ret=spi_device_transmit(spi, &t);

    assert(ret == ESP_OK);
}

static void lcd_data(spi_device_handle_t spi, const uint8_t* data, int len)
{
    esp_err_t ret;
    spi_transaction_t t;

    if (len == 0)
	{
    	return;
	}

    memset(&t, 0, sizeof(t));

    t.length = len * 8;
    t.tx_buffer = data;
    t.user = (void*) 1;

    ret = spi_device_transmit(spi, &t);
    assert(ret == ESP_OK);
}

static void lcd_spi_pre_transfer_callback(spi_transaction_t* t)
{
    int dc = (int) t->user;
    gpio_set_level(PIN_NUM_DC, dc);
}

static spi_device_handle_t spi;
static const spi_bus_config_t buscfg =
{
	.miso_io_num = PIN_NUM_MISO,
	.mosi_io_num = PIN_NUM_MOSI,
	.sclk_io_num = PIN_NUM_CLK,
	.quadwp_io_num = -1,
	.quadhd_io_num = -1,
	.max_transfer_sz = ILI9341_HEIGHT * ILI9341_WIDTH * sizeof(uint16_t)
};

static const spi_device_interface_config_t devcfg =
{
	.clock_speed_hz = 80 * 1000 * 1000,
	.mode = 0,
	.spics_io_num = PIN_NUM_CS,
	.queue_size = SPI_QUEUE_SIZE + 1,
	.pre_cb = lcd_spi_pre_transfer_callback,
	.flags = 1 << 6
};


void ILI9341_init(void)
{
	esp_err_t ret;
	const lcd_init_cmd_t* lcd_init_cmds = ili_init_cmds;
	int cmd = 0;

	ret = spi_bus_initialize(1, &buscfg, 1);
	assert(ret == ESP_OK);

	ret = spi_bus_add_device(1, &devcfg, &spi);
	assert(ret == ESP_OK);

	gpio_set_direction(PIN_NUM_DC, GPIO_MODE_OUTPUT);
	gpio_set_direction(PIN_NUM_RST, GPIO_MODE_OUTPUT);
	gpio_set_direction(PIN_NUM_BCKL, GPIO_MODE_OUTPUT);

	gpio_set_level(PIN_NUM_RST, 0);
	vTaskDelay(100 / portTICK_RATE_MS);

	gpio_set_level(PIN_NUM_RST, 1);
	vTaskDelay(100 / portTICK_RATE_MS);

	while (lcd_init_cmds[cmd].databytes != 0xff)
	{
		lcd_cmd(spi, lcd_init_cmds[cmd].cmd);

		lcd_data(spi, lcd_init_cmds[cmd].data, lcd_init_cmds[cmd].databytes & 0x1F);

		if (lcd_init_cmds[cmd].databytes & 0x80)
		{
			vTaskDelay(100 / portTICK_RATE_MS);
		}

		cmd++;
	}

	gpio_set_level(PIN_NUM_BCKL, 0);

	for (int i = 0; i < 6; i++)
	{
		if ((i & 1) == 0)
		{
			transaction[i].length = 8;
			transaction[i].user = (void*) 0;
		}
		else
		{
			transaction[i].length = 8 * 4;
			transaction[i].user = (void*) 1;
		}

		transaction[i].flags= 1 << 3;
	}

	transaction[0].tx_data[0] = 0x2A;
	transaction[1].tx_data[0] = 0;
	transaction[1].tx_data[1] = 0;
	transaction[1].tx_data[2] = ILI9341_WIDTH >> 8;
	transaction[1].tx_data[3] = ILI9341_WIDTH & 0xff;
	transaction[2].tx_data[0] = 0x2B;
	transaction[3].tx_data[0] = 0;
	transaction[3].tx_data[1] = 0;
	transaction[3].tx_data[2] = ILI9341_HEIGHT >> 8;
	transaction[3].tx_data[3] = ILI9341_HEIGHT & 0xff;
	transaction[4].tx_data[0] = 0x2C;

	for(int i = 0; i < SPI_QUEUE_SIZE - 1; i++)
	{
		spi_device_transmit(spi, &transaction[i]);
	}

	transaction[5].length = ILI9341_WIDTH * ILI9341_HEIGHT * sizeof(uint16_t) * 8;
	transaction[5].flags = 0;
}

void ILI9341_set_buffer(uint16_t buffer[ILI9341_WIDTH * ILI9341_HEIGHT])
{
	transaction[5].tx_buffer = buffer;
}

void ILI9341_draw_buffer(void)
{
	spi_device_queue_trans(spi, &transaction[SPI_QUEUE_SIZE - 1], portMAX_DELAY);
}

void ILI9341_wait_for_draw_complete(void)
{
	spi_transaction_t* rtrans;

	spi_device_get_trans_result(spi, &rtrans, portMAX_DELAY);
}
