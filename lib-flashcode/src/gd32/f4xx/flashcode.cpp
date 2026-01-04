/**
 * @file flashcode.cpp
 *
 */
/* Copyright (C) 2022-2025 by Arjan van Vught mailto:info@gd32-dmx.org
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

#include <cstdint>

#include "flashcode.h"
#include "gd32.h"
#include "fmc_operation.h"
#include "firmware/debug/debug_dump.h"
#include "firmware/debug/debug_debug.h"

uint32_t FlashCode::GetSize() const
{
    return FMC_SIZE * 1024U;
}

uint32_t FlashCode::GetSectorSize() const
{
    return SIZE_16KB;
}

bool FlashCode::Read(uint32_t offset, uint32_t length, uint8_t* buffer, flashcode::Result& result)
{
    DEBUG_ENTRY();
    DEBUG_PRINTF("offset=%p[%d], length=%u[%d], data=%p[%d]", offset, (((uint32_t)(offset) & 0x3) == 0), length, (((uint32_t)(length) & 0x3) == 0), data, (((uint32_t)(data) & 0x3) == 0));

    auto* src = reinterpret_cast<const uint32_t*>(offset + FLASH_BASE);
    auto* dst = reinterpret_cast<uint32_t*>(buffer);

    while (length > 0)
    {
        *dst++ = *src++;
        length -= 4;
    }

    debug::Dump((uint8_t*)(offset + FLASH_BASE), 64);
    debug::Dump(buffer, 64);

    result = flashcode::Result::kOk;

    DEBUG_EXIT();
    return 0;
}

bool FlashCode::Write(uint32_t offset, uint32_t length, const uint8_t* buffer, flashcode::Result& result)
{
    DEBUG_ENTRY();
    DEBUG_PRINTF("offset=%p[%d], length=%u[%d], data=%p[%d]", offset, (((uint32_t)(offset) & 0x3) == 0), length, (((uint32_t)(length) & 0x3) == 0), buffer, (((uint32_t)(buffer) & 0x3) == 0));

    result = flashcode::Result::kError;

    fmc_unlock();
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);

    uint32_t address = offset + FLASH_BASE;
    auto* data = reinterpret_cast<const uint32_t*>(buffer);

    while (length >= 4)
    {
        fmc_state_enum state = fmc_word_program(address, *data);

        if (FMC_READY != state)
        {
            DEBUG_PRINTF("state=%d [%p]", state, address);
            DEBUG_EXIT();
            return true;
        }

        data++;
        address += 4;
        length -= 4;
    }

    if (length > 0)
    {
        fmc_state_enum state = fmc_word_program(address, *data);

        if (FMC_READY != state)
        {
            DEBUG_PRINTF("state=%d [%p]", state, address);
            DEBUG_EXIT();
            return true;
        }
    }

    fmc_lock();

    debug::Dump(buffer, 64);
    debug::Dump((uint8_t*)(offset + FLASH_BASE), 64);

    result = flashcode::Result::kOk;

    DEBUG_EXIT();
    return true;
}

bool FlashCode::Erase(uint32_t offset, uint32_t length, flashcode::Result& result)
{
    DEBUG_ENTRY();
    DEBUG_PRINTF("offset=%p[%d], length=%x[%d]", offset, (((uint32_t)(offset) & 0x3) == 0), length, (((uint32_t)(length) & 0x3) == 0));

    result = flashcode::Result::kError;

    fmc_sector_info_struct sector_info;
    uint32_t address = offset + FLASH_BASE;

    int size = static_cast<int>(length);

    while (size > 0)
    {
        sector_info = fmc_sector_info_get(address);

        if (FMC_WRONG_SECTOR_NAME == sector_info.sector_name)
        {
            return true;
        }

        DEBUG_PRINTF("Address 0x%08X is located in the : SECTOR_NUMBER_%d", address, sector_info.sector_name);
        DEBUG_PRINTF("Sector range: 0x%08X to 0x%08X", sector_info.sector_start_addr, sector_info.sector_end_addr);
        DEBUG_PRINTF("nSector size: %d KB\n", (sector_info.sector_size / 1024));

        fmc_unlock();
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);

        if (FMC_READY != fmc_sector_erase(sector_info.sector_num))
        {
            return true;
        }

        fmc_lock();

        size -= sector_info.sector_size;
        address += sector_info.sector_size;
    }

    result = flashcode::Result::kOk;

    DEBUG_EXIT();
    return true;
}
