# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

if(${MBED_TOOLCHAIN} STREQUAL "GCC_ARM")
    set(STARTUP_FILE TOOLCHAIN_GCC_ARM/startup_stm32h745xx.S)
elseif(${MBED_TOOLCHAIN} STREQUAL "ARM")
    set(STARTUP_FILE TOOLCHAIN_ARM/startup_stm32h745xx.S)
endif()

add_library(mbed-stm32h745xi-cm4 INTERFACE)

target_sources(mbed-stm32h745xi-cm4
    INTERFACE
        ${STARTUP_FILE}
)

target_link_libraries(mbed-stm32h745xi-cm4 INTERFACE mbed-stm32h745xi)
