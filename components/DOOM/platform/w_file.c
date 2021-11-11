//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	WAD I/O functions.
//

#include <stdio.h>
#include <string.h>

#include "config.h"

#include "doomtype.h"
#include "m_argv.h"

#include "w_file.h"

#include "esp_timer.h"

extern const void* wad_partition_ptr;
extern uint32_t wad_partition_size;

/*
#ifdef _WIN32
extern wad_file_class_t win32_wad_file;
#endif
*/

#ifdef HAVE_MMAP
extern wad_file_class_t posix_wad_file;
#endif 

wad_file_t wad_file;


wad_file_t *W_OpenFile(char *path)
{
	wad_file.file_class = NULL;
	wad_file.length = wad_partition_size;
	wad_file.mapped = (byte*) wad_partition_ptr;

    return &wad_file;
}

void W_CloseFile(wad_file_t *wad)
{

}

size_t W_Read(wad_file_t *wad, unsigned int offset,
              void *buffer, size_t buffer_len)
{
	memcpy(buffer, wad_partition_ptr + offset, buffer_len);

    return buffer_len;
}

