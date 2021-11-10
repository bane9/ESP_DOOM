#include <stdio.h>
#include <stdlib.h>

#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_partition.h"

const void* wad_partition_ptr; // I cannot include nvs_flash and esp_partition in components for some reason so this lives here..
uint32_t wad_partition_size;

void app_main(void)
{
	spi_flash_mmap_handle_t map_handle;
	const esp_partition_t* partition;

	partition = esp_partition_find_first(66, 6, NULL); // Type and subtype for the wad partition defined in patition.csv
	// espressif guys were creative with the number here

	assert(partition);

	ESP_ERROR_CHECK(
			esp_partition_mmap(partition, 0, partition->size, SPI_FLASH_MMAP_DATA, &wad_partition_ptr, &map_handle));

	wad_partition_size = partition->size;

	extern int doom_main(int argc, char **argv);

	char* argv[] = {"doom", "-mb", "3","-iwad", "doom1.wad", NULL};
	int argc = sizeof(argv) / sizeof(argv[0]) - 1;

	doom_main(argc, argv);
}
