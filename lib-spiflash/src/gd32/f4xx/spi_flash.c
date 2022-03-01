/**
 * @file spi_flash.c
 *
 */
/* Copyright (C) 2022 by Arjan van Vught mailto:info@gd32-dmx.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "gd32.h"
#include "fmc_operation.h"

#include "debug.h"

const char *spi_flash_get_name(void) {
	return GD32_MCU_NAME;
}

uint32_t spi_flash_get_size(void) {
	return FMC_SIZE * 1024U;;
}

uint32_t spi_flash_get_sector_size(void) {
	return SIZE_16KB;
}

int spi_flash_probe(__attribute__((unused)) unsigned int cs, __attribute__((unused)) unsigned int max_hz, __attribute__((unused)) unsigned int spi_mode) {
	return 1;
}

int spi_flash_cmd_read_fast(uint32_t offset, size_t len, void *data) {
	DEBUG_ENTRY
	DEBUG_PRINTF("offset=%p[%d], len=%u[%d], data=%p[%d]", offset, (((uint32_t)(offset) & 0x3) == 0), len, (((uint32_t)(len) & 0x3) == 0), data, (((uint32_t)(data) & 0x3) == 0));

	const uint32_t *src = (uint32_t *)(offset + FLASH_BASE);
	uint32_t *dst = (uint32_t *)data;

	while (len > 0) {
		*dst++ = *src++;
		len -= 4;
	}

	debug_dump((uint8_t *)(offset + FLASH_BASE), 64);
	debug_dump(data, 64);

	DEBUG_EXIT
	return 0;
}

int spi_flash_cmd_write_multi(uint32_t offset, size_t len, const void *buf) {
	DEBUG_ENTRY
	DEBUG_PRINTF("offset=%p[%d], len=%u[%d], data=%p[%d]", offset, (((uint32_t)(offset) & 0x3) == 0), len, (((uint32_t)(len) & 0x3) == 0), buf, (((uint32_t)(buf) & 0x3) == 0));

    fmc_unlock();
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);

	uint32_t address = offset + FLASH_BASE;
	const uint32_t *data = (uint32_t *)buf;

	while (len >= 4) {
		fmc_state_enum state = fmc_word_program(address, *data);

		if (FMC_READY != state) {
			DEBUG_PRINTF("state=%d [%p]", state, address);
			DEBUG_EXIT
			return -state;
		}

		data++;
		address += 4;
		len -= 4;
	}

	if (len > 0) {
		fmc_state_enum state = fmc_word_program(address, *data);

		if (FMC_READY != state) {
			DEBUG_PRINTF("state=%d [%p]", state, address);
			DEBUG_EXIT
			return -state;
		}
	}

	fmc_lock();

	debug_dump(buf, 64);
	debug_dump((uint8_t *)(offset + FLASH_BASE), 64);

	DEBUG_EXIT
	return 0;
}

int spi_flash_cmd_erase(uint32_t offset, size_t len) {
	DEBUG_ENTRY
	DEBUG_PRINTF("offset=%p[%d], len=%x[%d]", offset, (((uint32_t)(offset) & 0x3) == 0), len, (((uint32_t)(len) & 0x3) == 0));

	fmc_sector_info_struct sector_info;
	uint32_t address = offset + FLASH_BASE;

	int size = (int) len;

	while (size > 0) {
		sector_info = fmc_sector_info_get(address);

		if (FMC_WRONG_SECTOR_NAME == sector_info.sector_name) {
			return -1;
		}

		DEBUG_PRINTF("Address 0x%08X is located in the : SECTOR_NUMBER_%d", address, sector_info.sector_name);
		DEBUG_PRINTF("Sector range: 0x%08X to 0x%08X", sector_info.sector_start_addr, sector_info.sector_end_addr);
		DEBUG_PRINTF("nSector size: %d KB\n", (sector_info.sector_size/1024));

		fmc_unlock();
		fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);

		if (FMC_READY != fmc_sector_erase(sector_info.sector_num)) {
			return -1;
		}

		fmc_lock();

		size -= sector_info.sector_size;
		address += sector_info.sector_size;
	}

	DEBUG_EXIT
	return 0;
}
