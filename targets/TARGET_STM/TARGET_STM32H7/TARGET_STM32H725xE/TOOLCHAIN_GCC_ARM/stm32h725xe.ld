/* Linker script to configure memory regions. */
/*
 * SPDX-License-Identifier: BSD-3-Clause
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2016-2020 STMicroelectronics.
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
*/

#include "../cmsis_nvic.h"


#if !defined(MBED_APP_START)
  #define MBED_APP_START  MBED_ROM_START
#endif

#if !defined(MBED_APP_SIZE)
  #define MBED_APP_SIZE  MBED_ROM_SIZE
#endif

M_CRASH_DATA_RAM_SIZE = 0x100;

#if !defined(MBED_CONF_TARGET_BOOT_STACK_SIZE)
    /* This value is normally defined by the tools
       to 0x1000 for bare metal and 0x400 for RTOS */
    #define MBED_CONF_TARGET_BOOT_STACK_SIZE  0x400
#endif

STACK_SIZE = MBED_CONF_TARGET_BOOT_STACK_SIZE;

/* Round up MBED_VECTTABLE_RAM_SIZE to 8 bytes */
#define MBED_VECTTABLE_RAM_SIZE  (((NVIC_NUM_VECTORS * 4) + 7) & 0xFFFFFFF8)
#define MBED_RAM0_START  (MBED_RAM_START + MBED_VECTTABLE_RAM_SIZE)
#define MBED_RAM0_SIZE   (MBED_RAM_SIZE - MBED_VECTTABLE_RAM_SIZE)

MEMORY
{
    FLASH       (rx)  : ORIGIN = MBED_APP_START, LENGTH = MBED_APP_SIZE
    SRAM_DTC   (xrw)  : ORIGIN = MBED_RAM0_START, LENGTH = MBED_RAM0_SIZE
    SRAM       (xrw)  : ORIGIN = MBED_RAM1_START, LENGTH = MBED_RAM1_SIZE
    SRAM_LOWER (xrw)  : ORIGIN = 0x30000000, LENGTH = 32K
    SRAM_UPPER (xrw)  : ORIGIN = 0x38000000, LENGTH = 16K
    SRAM_ITC   (xrw)  : ORIGIN = 0x00000000, LENGTH = 64K
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
 *   _estack
 */
ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
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
    _sidata = .;

    .crash_data_ram :
    {
        . = ALIGN(8);
        __CRASH_DATA_RAM__ = .;
        __CRASH_DATA_RAM_START__ = .; /* Create a global symbol at data start */
        KEEP(*(.keep.crash_data_ram))
        *(.m_crash_data_ram)     /* This is a user defined section */
        . += M_CRASH_DATA_RAM_SIZE;
        . = ALIGN(8);
        __CRASH_DATA_RAM_END__ = .; /* Define a global symbol at data end */
    } > SRAM_UPPER

    /* .stack section doesn't contains any symbols. It is only
     * used for linker to reserve space for the isr stack section
     * WARNING: .stack should come immediately after the last secure memory
     * section.  This provides stack overflow detection. */
    .stack (NOLOAD):
    {
        __StackLimit = .;
        *(.stack*);
        . += STACK_SIZE - (. - __StackLimit);
    } > SRAM_DTC

    /* Set stack top to end of SRAM, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ADDR(.stack) + SIZEOF(.stack);
    _estack = __StackTop;
    __StackLimit = ADDR(.stack);
    PROVIDE(__stack = __StackTop);

    /* Place holder for additional heap */
    .heap_0 (COPY):
    {
        __mbed_sbrk_start_0 = .;
        . += (ORIGIN(SRAM_DTC) + LENGTH(SRAM_DTC) - .);
        __mbed_krbs_start_0 = .;
    } > SRAM_DTC

    /* Check if heap exceeds SRAM_DTC */
    ASSERT(__mbed_krbs_start_0 <= (ORIGIN(SRAM_DTC)+LENGTH(SRAM_DTC)), "Heap is too big for SRAM_DTC")

    .data : AT (__etext)
    {
        __data_start__ = .;
        _sdata = .;
        *(vtable)
        *(.data*)

        . = ALIGN(8);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(8);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(8);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        KEEP(*(.jcr*))
        . = ALIGN(8);
        /* All data end */
        __data_end__ = .;
        _edata = .;

    } > SRAM

    /* Check if data exceeds SRAM */
    ASSERT(__data_end__ <= (ORIGIN(SRAM)+LENGTH(SRAM)), "data is too big for SRAM")

    /* Uninitialized data section
     * This region is not initialized by the C/C++ library and can be used to
     * store state across soft reboots. */
    .uninitialized (NOLOAD):
    {
        . = ALIGN(32);
        __uninitialized_start = .;
        *(.uninitialized)
        KEEP(*(.keep.uninitialized))
        . = ALIGN(32);
        __uninitialized_end = .;
    } > SRAM

    .bss :
    {
        . = ALIGN(8);
        __bss_start__ = .;
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(8);
        __bss_end__ = .;
        _ebss = .;
    } > SRAM

    /* Check if bss exceeds SRAM */
    ASSERT(__bss_end__ <= (ORIGIN(SRAM)+LENGTH(SRAM)), "bss is too big for SRAM")

    .heap (COPY):
    {
        __end__ = .;
        end = __end__;
        __mbed_sbrk_start = .;
        *(.heap*)
        . += (ORIGIN(SRAM) + LENGTH(SRAM) - .);
        __mbed_krbs_start = .;
        __HeapLimit = .;
    } > SRAM

    /* Check if data + heap exceeds SRAM limit */
    ASSERT(__HeapLimit <= (ORIGIN(SRAM)+LENGTH(SRAM)), "Heap is too big for SRAM")
}
