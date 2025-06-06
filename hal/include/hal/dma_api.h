/**
 * @file
 * \addtogroup hal
 * @{
 */
/* mbed Microcontroller Library
 * Copyright (c) 2014-2015 ARM Limited
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
#ifndef MBED_DMA_API_H
#define MBED_DMA_API_H

#include <stdint.h>

#define DMA_ERROR_OUT_OF_CHANNELS (-1)

/**
 * @brief Enumeration of possible DMA usage hints
 */
typedef enum {
    DMA_USAGE_NEVER = 0, ///< Never use DMA
    DMA_USAGE_OPPORTUNISTIC, ///< Use DMA if possible but deallocate DMA resources when not being used.
    DMA_USAGE_ALWAYS, ///< Always use DMA when possible
    DMA_USAGE_TEMPORARY_ALLOCATED, // Seems to be used as an internal state indicator for "we need to deallocate these channels."
    DMA_USAGE_ALLOCATED // Seems to be used as an internal state indicator for "we have allocated DMA channels."
} DMAUsage;

#ifdef __cplusplus
extern "C" {
#endif

void dma_init(void);

int dma_channel_allocate(uint32_t capabilities);

int dma_channel_free(int channelid);

#ifdef __cplusplus
}
#endif

#endif

/** @}*/
