/* mbed Microcontroller Library
 * SPDX-License-Identifier: BSD-3-Clause
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2016-2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
*/

#ifndef MBED_CMSIS_NVIC_H
#define MBED_CMSIS_NVIC_H

#if !defined(TRUST_ZONE)
#if !defined(MBED_ROM_START)
#define MBED_ROM_START  0x8000000
#endif
#else
#if !defined(MBED_ROM_START)
#define MBED_ROM_START  0xC000000
#endif
#endif //TRUST_ZONE

#if !defined(MBED_ROM_SIZE)
#define MBED_ROM_SIZE  0x200000  // 2.0 MB
#endif

#if !defined(TRUST_ZONE)
#if !defined(MBED_RAM_START)
#define MBED_RAM_START  0x20000000
#endif
#else
#if !defined(MBED_RAM_START)
#define MBED_RAM_START  0x30000000
#endif
#endif //TRUST_ZONE

#if !defined(MBED_RAM_SIZE)
//256K SRAM1 + 64K SRAM2 + 320K SRAM3 = 640KB
#define MBED_RAM_SIZE  0xA0000
#endif

#define NVIC_NUM_VECTORS        147
#define NVIC_RAM_VECTOR_ADDRESS MBED_RAM_START

#endif
