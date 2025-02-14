/* mbed Microcontroller Library
 * Copyright (c) 2017 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#if DEVICE_FLASH
#include "mbed_critical.h"

#include "flash_api.h"
#include "mbed_assert.h"
#include "cmsis.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#define MEMMAP     (*((volatile unsigned long *) 0x400FC040))

#define PLL0CON    (*((volatile unsigned long *) 0x400FC080))
#define PLL0CFG    (*((volatile unsigned long *) 0x400FC084))
#define PLL0STAT   (*((volatile unsigned long *) 0x400FC088))
#define PLL0FEED   (*((volatile unsigned long *) 0x400FC08C))
#define CCLKSEL    (*((volatile unsigned long *) 0x400FC104))
#define CLKSRCSEL  (*((volatile unsigned long *) 0x400FC10C))

#define STACK_SIZE 64 // Stack Size

#define SET_VALID_CODE 1 // Set Valid User Code Signature
/* IAP Call */
typedef void (*IAP_Entry) (unsigned long *cmd, unsigned long *stat);
#define IAP_Call ((IAP_Entry) 0x1FFF1FF1)

typedef struct flash_s flash_t;
unsigned long CCLK; // CCLK in kHz

struct sIAP { // IAP Structure
    unsigned long cmd;// Command
    unsigned long par[4];// Parameters
    unsigned long stat;// Status
    unsigned long res[2];// Result
}IAP;

/*
 * Get Sector Number
 *    Parameter:      address:  Sector Address
 *    Return Value:   Sector Number
 */

unsigned long GetSecNum (unsigned long address)
{
    unsigned long n;

    n = address >> 12; // 4kB Sector
    if (n >= 0x10) {
        n = 0x0E + (n >> 3); // 32kB Sector
    }

    return (n); // Sector Number
}
int32_t flash_init(flash_t *obj)
{
    CCLK = SystemCoreClock / 1000; // CCLK value is in kHz, clk in Hz

    MEMMAP = 0x01;// User Flash Mode

    return (0);
}

int32_t flash_free(flash_t *obj)
{
    return 0;
}

int32_t flash_erase_sector(flash_t *obj, uint32_t address)
{
    unsigned long n;

    n = GetSecNum(address); // Get Sector Number

    core_util_critical_section_enter();
    IAP.cmd = 50;// Prepare Sector for Erase
    IAP.par[0] = n;// Start Sector
    IAP.par[1] = n;// End Sector
    IAP_Call (&IAP.cmd, &IAP.stat);// Call IAP Command
    if (IAP.stat) {
        return (1); // Command Failed
    }

    IAP.cmd = 52; // Erase Sector
    IAP.par[0] = n;// Start Sector
    IAP.par[1] = n;// End Sector
    IAP.par[2] = CCLK;// CCLK in kHz
    IAP_Call (&IAP.cmd, &IAP.stat);// Call IAP Command
    core_util_critical_section_exit();
    if (IAP.stat) {
        return (1); // Command Failed
    }

    return (0); // Finished without Errors

}

int32_t flash_program_page(flash_t *obj, uint32_t address,
        const uint8_t *data, uint32_t size)
{
    unsigned long n;
    const uint32_t pageSize = flash_get_page_size(obj);
    uint8_t *tempBuffer, *source;

    tempBuffer = 0;
    source = (uint8_t *)data;
    
    // On LPC1768, the first RAM bank starts at 0x1000000, so anywhere below that has to be flash.
    // The IAP firmware does not support flash to flash copies, so if the source data is in flash
    // it must be buffered in RAM.
    // Additionally, there seems to be an issue where the IAP ROM won't operate if a source page to be copied
    // crosses the boundary between AHBSRAM0 and AHBSRAM1
    const bool startsInAHBSRAM1 = ((uint32_t)data) >= MBED_CONFIGURED_RAM_BANK_IRAM2_START && ((uint32_t)data) < (MBED_CONFIGURED_RAM_BANK_IRAM2_START + 16384);
    const bool endsInAHBSRAM2 = startsInAHBSRAM1 && ((((uint32_t)data) + size) >= MBED_CONFIGURED_RAM_BANK_IRAM2_START + 16384);
    const bool sourceAddressPageAligned = (((uint32_t)data) % pageSize) == 0;
    bool mustBuffer = ((ptrdiff_t)(data) < MBED_CONFIGURED_RAM_BANK_IRAM1_START) || (startsInAHBSRAM1 && endsInAHBSRAM2 && !sourceAddressPageAligned);

    // printf("Flash program: flash address = 0x%" PRIx32 ", source data = 0x%" PRIx32 ", size = 0x%" PRIx32 ", startsInAHBSRAM1 = %d, endsInAHBSRAM2=%d, mustBuffer=%d\n",
    //         address, (ptrdiff_t)data, size, !!startsInAHBSRAM1, !!endsInAHBSRAM2, !!mustBuffer);

    // check word boundary
    if (mustBuffer) {
        // always malloc outside critical section
        tempBuffer = malloc(pageSize);
        if (tempBuffer == 0) {
            return -1;
        }
    }

    n = GetSecNum(address); // Get Sector Number

    core_util_critical_section_enter();

    for(size_t pageIdx = 0; pageIdx < (size / pageSize); ++pageIdx)
    {
        uint8_t * pageSourceAddr = source + (pageIdx * pageSize);
        if (mustBuffer) {
            memcpy(tempBuffer, pageSourceAddr, pageSize);
            pageSourceAddr = tempBuffer;
        }

        /*
        Prepare_Sector_for_Write command must be exected before
        Copy_RAM_to_Flash command.
        */
        IAP.cmd = 50;    // Prepare Sector for Write
        IAP.par[0] = n;  // Start Sector
        IAP.par[1] = n;  // End Sector
        IAP_Call (&IAP.cmd, &IAP.stat); // Call IAP Command
        if (IAP.stat) {
            core_util_critical_section_exit();
            return -1; // Command Failed
        }

        IAP.cmd = 51; // Copy RAM to Flash
        IAP.par[0] = address; // Destination Flash Address
        IAP.par[1] = (unsigned long)pageSourceAddr; // Source RAM Address
        IAP.par[2] = pageSize; // number of bytes to be written
        IAP.par[3] = CCLK; // CCLK in kHz
        IAP_Call (&IAP.cmd, &IAP.stat); // Call IAP Command
        if (IAP.stat) {
            core_util_critical_section_exit();
            //printf("IAP copy failed, address=0x%lx, pageSourceAddr=0x%lx, pageSize=%u\n", address, pageSourceAddr, pageSize);
            return -1; // Command Failed
        }

        address += pageSize;
    }

    core_util_critical_section_exit();

    if(tempBuffer != 0) { // We allocated our own memory
        free(tempBuffer);
    }

    return (0); // Finished without Errors
}

uint32_t flash_get_sector_size(const flash_t *obj, uint32_t address)
{
    if (address < flash_get_start_address(obj) || address >= flash_get_start_address(obj) +flash_get_size(obj)) {
        return MBED_FLASH_INVALID_SIZE;
    }
    if(GetSecNum(address)>=0x10) {
        return 0x8000;
    } else {
        return 0x1000;
    }
}

uint32_t flash_get_page_size(const flash_t *obj)
{
    return 1024;
}

uint32_t flash_get_start_address(const flash_t *obj)
{
    return LPC_FLASH_BASE;
}

uint32_t flash_get_size(const flash_t *obj)
{
    return 0x80000;
}

uint8_t flash_get_erase_value(const flash_t *obj)
{
    (void)obj;

    return 0xFF;
}

#endif
