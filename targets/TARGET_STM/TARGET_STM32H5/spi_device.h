/* mbed Microcontroller Library
 * SPDX-License-Identifier: BSD-3-Clause
 ******************************************************************************
 *
 * Copyright (c) 2015-2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#ifndef MBED_SPI_DEVICE_H
#define MBED_SPI_DEVICE_H

#include "stm32h5xx_ll_rcc.h"
#include "stm32h5xx_ll_spi.h"

#define SPI_IP_VERSION_V2

// Defines the word legnth capability of the device where Nth bit allows for N window size
#define STM32_SPI_CAPABILITY_WORD_LENGTH (0xFFFFFFF8)

// We have DMA support
#define STM32_SPI_CAPABILITY_DMA 1

#endif
