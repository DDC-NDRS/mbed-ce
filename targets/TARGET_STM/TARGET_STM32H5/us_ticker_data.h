/* mbed Microcontroller Library
 * SPDX-License-Identifier: BSD-3-Clause
 ******************************************************************************
 *
 * Copyright (c) 2015-2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#ifndef __US_TICKER_DATA_H
#define __US_TICKER_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h5xx.h"
#include "stm32h5xx_ll_tim.h"
#include "cmsis_nvic.h"


#define TIM_MST      TIM3
#define TIM_MST_IRQ  TIM3_IRQn
#define TIM_MST_RCC  __TIM3_CLK_ENABLE()
#define TIM_MST_DBGMCU_FREEZE  __HAL_DBGMCU_FREEZE_TIM3()

#define TIM_MST_RESET_ON   __TIM3_FORCE_RESET()
#define TIM_MST_RESET_OFF  __TIM3_RELEASE_RESET()

#define TIM_MST_BIT_WIDTH  16 // 16 or 32

#define TIM_MST_PCLK  1 // Select the peripheral clock number (1 or 2)*/

#ifdef __cplusplus
}
#endif

#endif // __US_TICKER_DATA_H

