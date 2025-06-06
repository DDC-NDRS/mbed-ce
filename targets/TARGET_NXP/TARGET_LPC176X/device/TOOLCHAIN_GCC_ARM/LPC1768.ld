/* mbed Microcontroller Library
 * Copyright (c) 2025 Jamie Smith
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
  
#include "../cmsis_nvic.h"

#if !defined(MBED_CONF_TARGET_BOOT_STACK_SIZE)
    #define MBED_CONF_TARGET_BOOT_STACK_SIZE 0x400
#endif

STACK_SIZE = MBED_CONF_TARGET_BOOT_STACK_SIZE;

#define VTORS_NEEDED_SPACE NVIC_NUM_VECTORS * 4

/* Linker script to configure memory regions. */
MEMORY
{
  FLASH (rx) : ORIGIN = MBED_CONFIGURED_ROM_BANK_IROM1_START, LENGTH = MBED_CONFIGURED_ROM_BANK_IROM1_SIZE
  RAM (rwx) : ORIGIN = MBED_RAM_BANK_IRAM1_START + VTORS_NEEDED_SPACE, LENGTH = (MBED_RAM_BANK_IRAM1_SIZE - VTORS_NEEDED_SPACE - 32)  /* topmost 32 bytes used by IAP functions */
  AHBSRAM(rwx) : ORIGIN = MBED_RAM_BANK_IRAM2_START, LENGTH = MBED_RAM_BANK_IRAM2_SIZE
}

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 * 
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */
ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))

#if MBED_CONFIGURED_ROM_BANK_IROM1_START == MBED_ROM_BANK_IROM1_START
        /* Code Read Protect data, if this is at the start of flash*/
        . = 0x000002FC ;
        KEEP(*(.CRPSection))
#endif

        /* End of Code Read Protect */
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        *(.rodata*)

        KEEP(*(.eh_frame*))
		
		
    } > FLASH

    .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;

    __etext = .;
        
    .data : AT (__etext)
    {
        __data_start__ = .;
        Image$$RW_IRAM1$$Base = .;
        *(vtable)
        *(.data*)

        . = ALIGN(8);
        /* preinit data */
        PROVIDE (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE (__preinit_array_end = .);

        . = ALIGN(8);
        /* init data */
        PROVIDE (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE (__init_array_end = .);


        . = ALIGN(8);
        /* finit data */
        PROVIDE (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE (__fini_array_end = .);

        . = ALIGN(8);
        /* All data end */
        __data_end__ = .;

    } > RAM

    
    .bss (NOLOAD):
    {
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
        Image$$RW_IRAM1$$ZI$$Limit = . ;
    } > RAM

    .heap_0 (NOLOAD): ALIGN(8)
    {
        __end__ = .;
        end = __end__;
        __mbed_sbrk_start_0 = .;
        . = (ORIGIN(RAM) + LENGTH(RAM) - STACK_SIZE);
        __mbed_krbs_start_0 = .;
    } > RAM

    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack_dummy (NOLOAD):
    {
        . += STACK_SIZE;
    } > RAM

    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ORIGIN(RAM) + LENGTH(RAM);
    __StackLimit = __StackTop - STACK_SIZE;
    PROVIDE(__stack = __StackTop);
    
    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= __end__, "region RAM overflowed with stack")


    /* Code can explicitly ask for data to be 
       placed in this higher RAM bank where
       they will be left uninitialized. 
    */
    .AHBSRAM_bss (NOLOAD):
    {
        *(AHBSRAM)
    } > AHBSRAM

    /* Fill remaining space in AHBSRAM with additional heap */
    .heap (NOLOAD): ALIGN(8)
    {
        __mbed_sbrk_start = .;
        . = ORIGIN(AHBSRAM) + LENGTH(AHBSRAM);
        __mbed_krbs_start = .;
    } > AHBSRAM
}
