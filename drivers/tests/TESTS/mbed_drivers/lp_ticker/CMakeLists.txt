# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

if(NOT "DEVICE_LPTICKER=1" IN_LIST MBED_TARGET_DEFINITIONS)
	set(TEST_SKIPPED "Low power ticker not supported for this target")
endif()

mbed_greentea_add_test(
    TEST_NAME
        mbed-drivers-lp-ticker
    TEST_SOURCES
        main.cpp
    TEST_SKIPPED
        ${TEST_SKIPPED}
)
