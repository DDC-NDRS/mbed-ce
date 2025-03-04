/*
 * Copyright (c) 2017, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#if defined(MBED_CONF_RTOS_PRESENT)

#include "mbed.h"
#include "mbed_trace.h"
#include "greentea-client/test_env.h"
#include "unity.h"
#include "utest.h"

#include "NetworkInterface.h"
#include "EMAC.h"
#include "EmacTestNetworkStack.h"
#include "emac_tests.h"
#include "emac_util.h"
#include "greentea_get_network_interface.h"

using namespace utest::v1;

void test_emac_initialize()
{
    worker_loop_init();
    mbed_trace_init();

    // Set memory manager parameters
    EmacTestMemoryManager::get_instance().set_alloc_unit(256); // Use a relatively small allocation unit size so packets have to be split up into a lot of buffers
    EmacTestMemoryManager::get_instance().set_pool_size(10); // Start with 10 buffers in the Rx pool. One max-len Eth packet uses 6 256-byte buffers, and some MACs need up to 4 extra ones.

    static NetworkInterface *network_interface = get_network_interface();

    // Power up the interface and emac driver
    TEST_ASSERT_EQUAL_INT(NSAPI_ERROR_OK, network_interface->connect());

    worker_loop_link_up_wait();
}

#endif // defined(MBED_CONF_RTOS_PRESENT)
