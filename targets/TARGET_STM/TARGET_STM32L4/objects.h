/* mbed Microcontroller Library
 * Copyright (c) 2016-2020 STMicroelectronics
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

#ifndef MBED_OBJECTS_H
#define MBED_OBJECTS_H

#include "cmsis.h"
#include "PortNames.h"
#include "PeripheralNames.h"
#include "PinNames.h"
#include "gpio_object.h"

#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_lpuart.h"
#include "stm32l4xx_ll_tim.h"
#include "stm32l4xx_ll_rtc.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_rcc.h"

#include "stm_dma_utils.h"
#if MBED_CONF_RTOS_PRESENT
#include "cmsis_os.h"
#include "cmsis_os2.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if DEVICE_ANALOGOUT
struct dac_s {
    DACName dac;
    PinName pin;
    uint32_t channel;
    DAC_HandleTypeDef handle;
};
#endif

struct serial_s {
    UARTName uart;
    int index; // Used by irq
    uint32_t baudrate;
    uint32_t databits;
    uint32_t stopbits;
    uint32_t parity;
    PinName pin_tx;
    PinName pin_rx;
#if DEVICE_SERIAL_ASYNCH
    uint32_t events;
#endif
#if DEVICE_SERIAL_FC
    uint32_t hw_flow_ctl;
    PinName pin_rts;
    PinName pin_cts;
#endif
};

struct flash_s {
    /*  nothing to be stored for now */
    uint32_t dummy;
};

struct analogin_s {
    ADC_HandleTypeDef handle;
    PinName pin;
    uint8_t channel;
};

struct gpio_irq_s {
    IRQn_Type irq_n;
    uint32_t irq_index;
    uint32_t event;
    PinName pin;
};

struct port_s {
    PortName port;
    uint32_t mask;
    PinDirection direction;
    __IO uint32_t *reg_in;
    __IO uint32_t *reg_out;
};

struct trng_s {
    RNG_HandleTypeDef handle;
};

#if DEVICE_CAN
struct can_s {
    CAN_HandleTypeDef CanHandle;
    int index;
    int hz;
    int rxIrqEnabled;
};
#endif

#if DEVICE_QSPI
struct qspi_s {
#if defined(OCTOSPI1)
    OSPI_HandleTypeDef handle;
    IRQn_Type qspiIRQ;
#else
    QSPI_HandleTypeDef handle;
#endif
    QSPIName qspi;
    PinName io0;
    PinName io1;
    PinName io2;
    PinName io3;
    PinName sclk;
    PinName ssel;
    bool dmaInitialized;
#if MBED_CONF_RTOS_PRESENT
    osSemaphoreId_t semaphoreId;
    osRtxSemaphore_t semaphoreMem;
#endif
};
#endif

#if DEVICE_OSPI
struct ospi_s {
    OSPI_HandleTypeDef handle;
    IRQn_Type ospiIRQ;
    OSPIName ospi;
    PinName io0;
    PinName io1;
    PinName io2;
    PinName io3;
    PinName io4;
    PinName io5;
    PinName io6;
    PinName io7;
    PinName sclk;
    PinName ssel;
    PinName dqs;
    bool dmaInitialized;
#if MBED_CONF_RTOS_PRESENT
    osSemaphoreId_t semaphoreId;
    osRtxSemaphore_t semaphoreMem;
#endif
};
#endif

#define HAL_CRC_IS_SUPPORTED(polynomial, width) ((width) == 7 || (width) == 8 || (width) == 16 || (width) == 32)

#ifdef __cplusplus
}
#endif

#endif
