/**
  ******************************************************************************
  * @file    stm32u5xx_hal_irda_ex.h
  * @author  MCD Application Team
  * @brief   Header file of IRDA HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * This software component is provided to you as part of a software package and
  * applicable license terms are in the  Package_license file. If you received this
  * software component outside of a package or without applicable license terms,
  * the terms of the Apache-2.0 license shall apply. 
  * You may obtain a copy of the Apache-2.0 at:
  * https://opensource.org/licenses/Apache-2.0
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_IRDA_EX_H
#define STM32U5xx_HAL_IRDA_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup IRDAEx IRDAEx
  * @brief IRDA Extended HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup IRDAEx_Extended_Exported_Constants IRDAEx Extended Exported Constants
  * @{
  */

/** @defgroup IRDAEx_Word_Length IRDAEx Word Length
  * @{
  */
#define IRDA_WORDLENGTH_7B                  USART_CR1_M1   /*!< 7-bit long frame */
#define IRDA_WORDLENGTH_8B                  0x00000000U    /*!< 8-bit long frame */
#define IRDA_WORDLENGTH_9B                  USART_CR1_M0   /*!< 9-bit long frame */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/** @defgroup IRDAEx_Private_Macros IRDAEx Private Macros
  * @{
  */

/** @brief  Report the IRDA clock source.
  * @param  __HANDLE__ specifies the IRDA Handle.
  * @param  __CLOCKSOURCE__ output variable.
  * @retval IRDA clocking source, written in __CLOCKSOURCE__.
  */
#if defined(USART6)
#define IRDA_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__)        \
  do {                                                         \
    if((__HANDLE__)->Instance == USART1)                       \
    {                                                          \
      switch(__HAL_RCC_GET_USART1_SOURCE())                    \
      {                                                        \
        case RCC_USART1CLKSOURCE_PCLK2:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK2;          \
          break;                                               \
        case RCC_USART1CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_USART1CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_USART1CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == USART2)                  \
    {                                                          \
      switch(__HAL_RCC_GET_USART2_SOURCE())                    \
      {                                                        \
        case RCC_USART2CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_USART2CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_USART2CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_USART2CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == USART3)                  \
    {                                                          \
      switch(__HAL_RCC_GET_USART3_SOURCE())                    \
      {                                                        \
        case RCC_USART3CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_USART3CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_USART3CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_USART3CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == UART4)                   \
    {                                                          \
      switch(__HAL_RCC_GET_UART4_SOURCE())                     \
      {                                                        \
        case RCC_UART4CLKSOURCE_PCLK1:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_UART4CLKSOURCE_HSI:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_UART4CLKSOURCE_SYSCLK:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_UART4CLKSOURCE_LSE:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == UART5)                   \
    {                                                          \
      switch(__HAL_RCC_GET_UART5_SOURCE())                     \
      {                                                        \
        case RCC_UART5CLKSOURCE_PCLK1:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_UART5CLKSOURCE_HSI:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_UART5CLKSOURCE_SYSCLK:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_UART5CLKSOURCE_LSE:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == USART6)                  \
    {                                                          \
      switch(__HAL_RCC_GET_USART6_SOURCE())                    \
      {                                                        \
        case RCC_USART6CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_USART6CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_USART6CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_USART6CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else                                                       \
    {                                                          \
      (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;          \
    }                                                          \
  } while(0U)
#elif defined(USART2)
#define IRDA_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__)        \
  do {                                                         \
    if((__HANDLE__)->Instance == USART1)                       \
    {                                                          \
      switch(__HAL_RCC_GET_USART1_SOURCE())                    \
      {                                                        \
        case RCC_USART1CLKSOURCE_PCLK2:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK2;          \
          break;                                               \
        case RCC_USART1CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_USART1CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_USART1CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == USART2)                  \
    {                                                          \
      switch(__HAL_RCC_GET_USART2_SOURCE())                    \
      {                                                        \
        case RCC_USART2CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_USART2CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_USART2CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_USART2CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == USART3)                  \
    {                                                          \
      switch(__HAL_RCC_GET_USART3_SOURCE())                    \
      {                                                        \
        case RCC_USART3CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_USART3CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_USART3CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_USART3CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == UART4)                   \
    {                                                          \
      switch(__HAL_RCC_GET_UART4_SOURCE())                     \
      {                                                        \
        case RCC_UART4CLKSOURCE_PCLK1:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_UART4CLKSOURCE_HSI:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_UART4CLKSOURCE_SYSCLK:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_UART4CLKSOURCE_LSE:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == UART5)                   \
    {                                                          \
      switch(__HAL_RCC_GET_UART5_SOURCE())                     \
      {                                                        \
        case RCC_UART5CLKSOURCE_PCLK1:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_UART5CLKSOURCE_HSI:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_UART5CLKSOURCE_SYSCLK:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_UART5CLKSOURCE_LSE:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else                                                       \
    {                                                          \
      (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;          \
    }                                                          \
  } while(0U)
#else
#define IRDA_GETCLOCKSOURCE(__HANDLE__,__CLOCKSOURCE__)        \
  do {                                                         \
    if((__HANDLE__)->Instance == USART1)                       \
    {                                                          \
      switch(__HAL_RCC_GET_USART1_SOURCE())                    \
      {                                                        \
        case RCC_USART1CLKSOURCE_PCLK2:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK2;          \
          break;                                               \
        case RCC_USART1CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_USART1CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_USART1CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == USART3)                  \
    {                                                          \
      switch(__HAL_RCC_GET_USART3_SOURCE())                    \
      {                                                        \
        case RCC_USART3CLKSOURCE_PCLK1:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_USART3CLKSOURCE_HSI:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_USART3CLKSOURCE_SYSCLK:                       \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_USART3CLKSOURCE_LSE:                          \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == UART4)                   \
    {                                                          \
      switch(__HAL_RCC_GET_UART4_SOURCE())                     \
      {                                                        \
        case RCC_UART4CLKSOURCE_PCLK1:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_UART4CLKSOURCE_HSI:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_UART4CLKSOURCE_SYSCLK:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_UART4CLKSOURCE_LSE:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else if((__HANDLE__)->Instance == UART5)                   \
    {                                                          \
      switch(__HAL_RCC_GET_UART5_SOURCE())                     \
      {                                                        \
        case RCC_UART5CLKSOURCE_PCLK1:                         \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_PCLK1;          \
          break;                                               \
        case RCC_UART5CLKSOURCE_HSI:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_HSI;            \
          break;                                               \
        case RCC_UART5CLKSOURCE_SYSCLK:                        \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_SYSCLK;         \
          break;                                               \
        case RCC_UART5CLKSOURCE_LSE:                           \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_LSE;            \
          break;                                               \
        default:                                               \
          (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;      \
          break;                                               \
      }                                                        \
    }                                                          \
    else                                                       \
    {                                                          \
      (__CLOCKSOURCE__) = IRDA_CLOCKSOURCE_UNDEFINED;          \
    }                                                          \
  } while(0U)
#endif /* USART6 */

/** @brief  Compute the mask to apply to retrieve the received data
  *         according to the word length and to the parity bits activation.
  * @param  __HANDLE__ specifies the IRDA Handle.
  * @retval None, the mask to apply to the associated UART RDR register is stored in (__HANDLE__)->Mask field.
  */
#define IRDA_MASK_COMPUTATION(__HANDLE__)                             \
  do {                                                                \
    if ((__HANDLE__)->Init.WordLength == IRDA_WORDLENGTH_9B)          \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == IRDA_PARITY_NONE)              \
      {                                                               \
        (__HANDLE__)->Mask = 0x01FFU ;                                \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU ;                                \
      }                                                               \
    }                                                                 \
    else if ((__HANDLE__)->Init.WordLength == IRDA_WORDLENGTH_8B)     \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == IRDA_PARITY_NONE)              \
      {                                                               \
        (__HANDLE__)->Mask = 0x00FFU ;                                \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x007FU ;                                \
      }                                                               \
    }                                                                 \
    else if ((__HANDLE__)->Init.WordLength == IRDA_WORDLENGTH_7B)     \
    {                                                                 \
      if ((__HANDLE__)->Init.Parity == IRDA_PARITY_NONE)              \
      {                                                               \
        (__HANDLE__)->Mask = 0x007FU ;                                \
      }                                                               \
      else                                                            \
      {                                                               \
        (__HANDLE__)->Mask = 0x003FU ;                                \
      }                                                               \
    }                                                                 \
    else                                                              \
    {                                                                 \
      (__HANDLE__)->Mask = 0x0000U;                                   \
    }                                                                 \
  } while(0U)

/** @brief Ensure that IRDA frame length is valid.
  * @param __LENGTH__ IRDA frame length.
  * @retval SET (__LENGTH__ is valid) or RESET (__LENGTH__ is invalid)
  */
#define IS_IRDA_WORD_LENGTH(__LENGTH__) (((__LENGTH__) == IRDA_WORDLENGTH_7B) || \
                                         ((__LENGTH__) == IRDA_WORDLENGTH_8B) || \
                                         ((__LENGTH__) == IRDA_WORDLENGTH_9B))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_HAL_IRDA_EX_H */

