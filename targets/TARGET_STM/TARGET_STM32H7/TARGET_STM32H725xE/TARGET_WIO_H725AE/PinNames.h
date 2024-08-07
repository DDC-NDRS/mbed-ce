/* mbed Microcontroller Library
 * SPDX-License-Identifier: BSD-3-Clause
 ******************************************************************************
 *
 * Copyright (c) 2016-2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 *
 * Automatically generated from STM32CubeMX/db/mcu/STM32H725AEIx.xml
 */

/* MBED TARGET LIST:  */

#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"
#include "PinNamesTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DUAL_PAD 0xF00

typedef enum {
    ALT0  = 0x100,
    ALT1  = 0x200,
    ALT2  = 0x300,
} ALTx;

typedef enum {
    PA_0       = 0x00,
    PA_0C      = PA_0  | DUAL_PAD, // dual pad
    PA_0C_ALT0 = PA_0C | ALT0, // same pin used for alternate HW
    PA_1       = 0x01,
    PA_1C      = PA_1  | DUAL_PAD, // dual pad
    PA_1C_ALT0 = PA_1C | ALT0, // same pin used for alternate HW
    PA_1_ALT0  = PA_1  | ALT0, // same pin used for alternate HW
    PA_2       = 0x02,
    PA_2_ALT0  = PA_2  | ALT0, // same pin used for alternate HW
    PA_3       = 0x03,
    PA_3_ALT0  = PA_3  | ALT0, // same pin used for alternate HW
    PA_4       = 0x04,
    PA_4_ALT0  = PA_4  | ALT0, // same pin used for alternate HW
    PA_4_ALT1  = PA_4  | ALT1, // same pin used for alternate HW
    PA_5       = 0x05,
    PA_5_ALT0  = PA_5  | ALT0, // same pin used for alternate HW
    PA_6       = 0x06,
    PA_6_ALT0  = PA_6  | ALT0, // same pin used for alternate HW
    PA_7       = 0x07,
    PA_7_ALT0  = PA_7  | ALT0, // same pin used for alternate HW
    PA_7_ALT1  = PA_7  | ALT1, // same pin used for alternate HW
    PA_7_ALT2  = PA_7  | ALT2, // same pin used for alternate HW
    PA_8       = 0x08,
    PA_8_ALT0  = PA_8  | ALT0, // same pin used for alternate HW
    PA_9       = 0x09,
    PA_9_ALT0  = PA_9  | ALT0, // same pin used for alternate HW
    PA_10      = 0x0A,
    PA_10_ALT0 = PA_10 | ALT0, // same pin used for alternate HW
    PA_11      = 0x0B,
    PA_11_ALT0 = PA_11 | ALT0, // same pin used for alternate HW
    PA_12      = 0x0C,
    PA_12_ALT0 = PA_12 | ALT0, // same pin used for alternate HW
    PA_13      = 0x0D,
    PA_14      = 0x0E,
    PA_15      = 0x0F,
    PA_15_ALT0 = PA_15 | ALT0, // same pin used for alternate HW
    PA_15_ALT1 = PA_15 | ALT1, // same pin used for alternate HW
    PB_0       = 0x10,
    PB_0_ALT0  = PB_0  | ALT0, // same pin used for alternate HW
    PB_0_ALT1  = PB_0  | ALT1, // same pin used for alternate HW
    PB_1       = 0x11,
    PB_1_ALT0  = PB_1  | ALT0, // same pin used for alternate HW
    PB_1_ALT1  = PB_1  | ALT1, // same pin used for alternate HW
    PB_2       = 0x12,
    PB_3       = 0x13,
    PB_3_ALT0  = PB_3  | ALT0, // same pin used for alternate HW
    PB_3_ALT1  = PB_3  | ALT1, // same pin used for alternate HW
    PB_4       = 0x14,
    PB_4_ALT0  = PB_4  | ALT0, // same pin used for alternate HW
    PB_4_ALT1  = PB_4  | ALT1, // same pin used for alternate HW
    PB_5       = 0x15,
    PB_5_ALT0  = PB_5  | ALT0, // same pin used for alternate HW
    PB_5_ALT1  = PB_5  | ALT1, // same pin used for alternate HW
    PB_6       = 0x16,
    PB_6_ALT0  = PB_6  | ALT0, // same pin used for alternate HW
    PB_6_ALT1  = PB_6  | ALT1, // same pin used for alternate HW
    PB_7       = 0x17,
    PB_7_ALT0  = PB_7  | ALT0, // same pin used for alternate HW
    PB_8       = 0x18,
    PB_8_ALT0  = PB_8  | ALT0, // same pin used for alternate HW
    PB_9       = 0x19,
    PB_9_ALT0  = PB_9  | ALT0, // same pin used for alternate HW
    PB_10      = 0x1A,
    PB_11      = 0x1B,
    PB_12      = 0x1C,
    PB_13      = 0x1D,
    PB_14      = 0x1E,
    PB_14_ALT0 = PB_14 | ALT0, // same pin used for alternate HW
    PB_14_ALT1 = PB_14 | ALT1, // same pin used for alternate HW
    PB_15      = 0x1F,
    PB_15_ALT0 = PB_15 | ALT0, // same pin used for alternate HW
    PB_15_ALT1 = PB_15 | ALT1, // same pin used for alternate HW
    PC_0       = 0x20,
    PC_0_ALT0  = PC_0  | ALT0, // same pin used for alternate HW
    PC_0_ALT1  = PC_0  | ALT1, // same pin used for alternate HW
    PC_1       = 0x21,
    PC_1_ALT0  = PC_1  | ALT0, // same pin used for alternate HW
    PC_1_ALT1  = PC_1  | ALT1, // same pin used for alternate HW
    PC_2       = 0x22,
    PC_2C      = PC_2  | DUAL_PAD, // dual pad
    PC_2_ALT0  = PC_2  | ALT0, // same pin used for alternate HW
    PC_2_ALT1  = PC_2  | ALT1, // same pin used for alternate HW
    PC_3       = 0x23,
    PC_3C      = PC_3  | DUAL_PAD, // dual pad
    PC_3_ALT0  = PC_3  | ALT0, // same pin used for alternate HW
    PC_4       = 0x24,
    PC_4_ALT0  = PC_4  | ALT0, // same pin used for alternate HW
    PC_5       = 0x25,
    PC_5_ALT0  = PC_5  | ALT0, // same pin used for alternate HW
    PC_6       = 0x26,
    PC_6_ALT0  = PC_6  | ALT0, // same pin used for alternate HW
    PC_7       = 0x27,
    PC_7_ALT0  = PC_7  | ALT0, // same pin used for alternate HW
    PC_8       = 0x28,
    PC_8_ALT0  = PC_8  | ALT0, // same pin used for alternate HW
    PC_9       = 0x29,
    PC_9_ALT0  = PC_9  | ALT0, // same pin used for alternate HW
    PC_10      = 0x2A,
    PC_10_ALT0 = PC_10 | ALT0, // same pin used for alternate HW
    PC_11      = 0x2B,
    PC_11_ALT0 = PC_11 | ALT0, // same pin used for alternate HW
    PC_12      = 0x2C,
    PC_13      = 0x2D,
    PC_14      = 0x2E,
    PC_15      = 0x2F,
    PD_0       = 0x30,
    PD_1       = 0x31,
    PD_2       = 0x32,
    PD_3       = 0x33,
    PD_4       = 0x34,
    PD_5       = 0x35,
    PD_6       = 0x36,
    PD_7       = 0x37,
    PD_8       = 0x38,
    PD_9       = 0x39,
    PD_10      = 0x3A,
    PD_11      = 0x3B,
    PD_12      = 0x3C,
    PD_13      = 0x3D,
    PD_14      = 0x3E,
    PD_15      = 0x3F,
    PE_0       = 0x40,
    PE_1       = 0x41,
    PE_2       = 0x42,
    PE_3       = 0x43,
    PE_4       = 0x44,
    PE_5       = 0x45,
    PE_6       = 0x46,
    PE_7       = 0x47,
    PE_8       = 0x48,
    PE_9       = 0x49,
    PE_10      = 0x4A,
    PE_11      = 0x4B,
    PE_12      = 0x4C,
    PE_13      = 0x4D,
    PE_14      = 0x4E,
    PE_15      = 0x4F,
    PF_0       = 0x50,
    PF_0_ALT0  = PF_0  | ALT0, // same pin used for alternate HW
    PF_1       = 0x51,
    PF_1_ALT0  = PF_1  | ALT0, // same pin used for alternate HW
    PF_2       = 0x52,
    PF_3       = 0x53,
    PF_4       = 0x54,
    PF_5       = 0x55,
    PF_6       = 0x56,
    PF_6_ALT0  = PF_6  | ALT0, // same pin used for alternate HW
    PF_7       = 0x57,
    PF_7_ALT0  = PF_7  | ALT0, // same pin used for alternate HW
    PF_8       = 0x58,
    PF_8_ALT0  = PF_8  | ALT0, // same pin used for alternate HW
    PF_8_ALT1  = PF_8  | ALT1, // same pin used for alternate HW
    PF_9       = 0x59,
    PF_9_ALT0  = PF_9  | ALT0, // same pin used for alternate HW
    PF_9_ALT1  = PF_9  | ALT1, // same pin used for alternate HW
    PF_10      = 0x5A,
    PF_11      = 0x5B,
    PF_12      = 0x5C,
    PF_13      = 0x5D,
    PF_14      = 0x5E,
    PF_15      = 0x5F,
    PG_0       = 0x60,
    PG_1       = 0x61,
    PG_2       = 0x62,
    PG_3       = 0x63,
    PG_4       = 0x64,
    PG_5       = 0x65,
    PG_6       = 0x66,
    PG_7       = 0x67,
    PG_8       = 0x68,
    PG_9       = 0x69,
    PG_10      = 0x6A,
    PG_11      = 0x6B,
    PG_12      = 0x6C,
    PG_13      = 0x6D,
    PG_13_ALT0 = PG_13 | ALT0, // same pin used for alternate HW
    PG_14      = 0x6E,
    PG_15      = 0x6F,
    PH_0       = 0x70,
    PH_1       = 0x71,
    PH_2       = 0x72,
    PH_3       = 0x73,
    PH_10      = 0x7A,
    PH_11      = 0x7B,
    PH_12      = 0x7C,
    PH_13      = 0x7D,
    PH_14      = 0x7E,

    /**** ADC internal channels ****/

    ADC_TEMP = 0xF0, // Internal pin virtual value
    ADC_VREF = 0xF1, // Internal pin virtual value
    ADC_VBAT = 0xF2, // Internal pin virtual value

    // STDIO for console print
#ifdef MBED_CONF_TARGET_STDIO_UART_TX
    CONSOLE_TX = MBED_CONF_TARGET_STDIO_UART_TX,
#else
    CONSOLE_TX = PD_8,
#endif
#ifdef MBED_CONF_TARGET_STDIO_UART_RX
    CONSOLE_RX = MBED_CONF_TARGET_STDIO_UART_RX,
#else
    CONSOLE_RX = PD_9,
#endif

    /**** USB HS pins ****/
    USB_OTG_HS_DM = PA_11,
    USB_OTG_HS_DP = PA_12,
    USB_OTG_HS_ID = PA_10,
    USB_OTG_HS_SOF = PA_8,
    USB_OTG_HS_ULPI_CK = PA_5,
    USB_OTG_HS_ULPI_D0 = PA_3,
    USB_OTG_HS_ULPI_D1 = PB_0,
    USB_OTG_HS_ULPI_D2 = PB_1,
    USB_OTG_HS_ULPI_D3 = PB_10,
    USB_OTG_HS_ULPI_D4 = PB_11,
    USB_OTG_HS_ULPI_D5 = PB_12,
    USB_OTG_HS_ULPI_D6 = PB_13,
    USB_OTG_HS_ULPI_D7 = PB_5,
    USB_OTG_HS_ULPI_DIR = PC_2,
    USB_OTG_HS_ULPI_DIR_ALT0 = PC_2C,
    USB_OTG_HS_ULPI_NXT = PC_3,
    USB_OTG_HS_ULPI_NXT_ALT0 = PC_3C,
    USB_OTG_HS_ULPI_STP = PC_0,
    USB_OTG_HS_VBUS = PA_9,

    /**** ETHERNET pins ****/
    ETH_COL = PH_3,
    ETH_COL_ALT0 = PA_3,
    ETH_CRS = PA_0,
    ETH_CRS_ALT0 = PA_0C,
    ETH_CRS_ALT1 = PH_2,
    ETH_CRS_DV = PA_7,
    ETH_MDC = PC_1,
    ETH_MDIO = PA_2,
    ETH_PPS_OUT = PB_5,
    ETH_PPS_OUT_ALT0 = PG_8,
    ETH_REF_CLK = PA_1,
    ETH_REF_CLK_ALT0 = PA_1C,
    ETH_RXD0 = PC_4,
    ETH_RXD1 = PC_5,
    ETH_RXD2 = PB_0,
    ETH_RXD3 = PB_1,
    ETH_RX_CLK = PA_1,
    ETH_RX_CLK_ALT0 = PA_1C,
    ETH_RX_DV = PA_7,
    ETH_RX_ER = PB_10,
    ETH_TXD0 = PG_13,
    ETH_TXD0_ALT0 = PB_12,
    ETH_TXD1 = PG_14,
    ETH_TXD1_ALT0 = PG_12,
    ETH_TXD1_ALT1 = PB_13,
    ETH_TXD2 = PC_2,
    ETH_TXD2_ALT0 = PC_2C,
    ETH_TXD3 = PE_2,
    ETH_TXD3_ALT0 = PB_8,
    ETH_TX_CLK = PC_3,
    ETH_TX_CLK_ALT0 = PC_3C,
    ETH_TX_EN = PG_11,
    ETH_TX_EN_ALT0 = PB_11,
    ETH_TX_ER = PA_9,
    ETH_TX_ER_ALT0 = PB_2,

    /**** OSCILLATOR pins ****/
    RCC_OSC32_IN = PC_14,
    RCC_OSC32_OUT = PC_15,
    RCC_OSC_IN = PH_0,
    RCC_OSC_OUT = PH_1,

    /**** DEBUG pins ****/
    DEBUG_JTCK_SWCLK = PA_14,
    DEBUG_JTDI = PA_15,
    DEBUG_JTDO_SWO = PB_3,
    DEBUG_JTMS_SWDIO = PA_13,
    DEBUG_JTRST = PB_4,
    DEBUG_TRACECLK = PE_2,
    DEBUG_TRACED0 = PE_3,
    DEBUG_TRACED0_ALT0 = PG_13,
    DEBUG_TRACED0_ALT1 = PC_1,
    DEBUG_TRACED1 = PE_4,
    DEBUG_TRACED1_ALT0 = PG_14,
    DEBUG_TRACED1_ALT1 = PC_8,
    DEBUG_TRACED2 = PE_5,
    DEBUG_TRACED2_ALT0 = PD_2,
    DEBUG_TRACED3 = PC_12,
    DEBUG_TRACED3_ALT0 = PE_6,
    DEBUG_TRGIO = PC_7,
    PWR_CSLEEP = PC_3,
    PWR_CSLEEP_ALT0 = PC_3C,
    PWR_CSTOP = PC_2,
    PWR_CSTOP_ALT0 = PC_2C,
    PWR_NDSTOP2 = PA_5,
    PWR_PVD_IN = PB_7,
    SYS_PWR_WKUP1 = PA_0,
    SYS_PWR_WKUP1_ALT0 = PA_0C,
    SYS_PWR_WKUP2 = PA_2,
    SYS_PWR_WKUP4 = PC_13,
    SYS_PWR_WKUP6 = PC_1,

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

// Standardized LED and button names
#define LED1     PF_0
#define LED2     PC_13
#define BUTTON1  PF_1

/* SD card slot MMC pins*/
#define MMC1_D0		PC_8
#define MMC1_D1		PC_9
#define MMC1_D2		PC_10 // SPI3_SCLK
#define MMC1_D3 	PC_11 // SPI3_MISO
#define MMC1_CLK    PC_12 // SPI3_MOSI
#define MMC1_CMD	PD_2

/* OSPI PSRAM pins */
#define OSPI1_SIO0  PF_8
#define OSPI1_SIO1  PF_9
#define OSPI1_SIO2  PF_7
#define OSPI1_SIO3  PF_6
#define OSPI1_SIO4  PD_4
#define OSPI1_SIO5  PD_5
#define OSPI1_SIO6  PE_9
#define OSPI1_SIO7  PD_7
#define OSPI1_DQS   PB_2
#define OSPI1_CLK   PF_10
#define OSPI1_CS    PG_6
#define OSPI1_RST   PG_3

/* QSPI Flash pins */
#define QSPI2_IO4   PG_0
#define QSPI2_IO5   PG_1
#define QSPI2_IO6   PG_10
#define QSPI2_IO7   PG_11
#define QSPI2_CLK   PF_4
#define QSPI2_CS    PG_12

/* BLE module pins */
#define  BLE_UART_TXD   PA_10  // UART RX
#define  BLE_UART_RXD   PB_14  // UART TX

/* WIFI module pins */
#define WIFI_DEBUG_TXD  PD_14 //RX
#define WIFI_DEBUG_RXD  PD_15 //TX
#define WIFI_SPI2_MISO  PC_2
#define WIFI_SPI2_MOSI  PC_1
#define WIFI_SPI2_CS    PB_12
#define WIFI_SPI2_CLK   PB_13
#define WIFI_CHIP_EN    PC_3
#define WIFI_SYNC       PF_2

/* Wio header */
#define TX      PD_9
#define RX      PD_8
#define MISO    PB_4_ALT1
#define MOSI    PB_5_ALT1
#define SCK     PG_13
#define A5      PF_13
#define A4      PC_0
#define A3      PF_12
#define A2      PC_4
#define A1      PF_11
#define A0      PA_1

#define SDA     PF_15
#define SCL     PF_14
#define CAN_RX  PH_14
#define CAN_TX  PD_1
#define D9      PA_0
#define D10     PF_3
#define D11     PE_10
#define D12     PB_3
#define D13     PE_8

#ifdef __cplusplus
}
#endif

#endif
