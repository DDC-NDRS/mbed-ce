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

#include "mbed.h"
#include "greentea-client/test_env.h"
#include "unity.h"
#include "utest.h"
#include "wifi_tests.h"

using namespace utest::v1;

#if defined(MBED_GREENTEA_WIFI_SECURE_SSID)

void wifi_connect_params_channel_fail(void)
{
    WiFiInterface *wifi = get_wifi_interface();
    TEST_ASSERT(wifi);
    if (wifi == NULL) {
        return;
    }

    if (wifi->set_channel(1) == NSAPI_ERROR_UNSUPPORTED && wifi->set_channel(36) == NSAPI_ERROR_UNSUPPORTED) {
        TEST_IGNORE_MESSAGE("set_channel() not supported");
        return;
    }

    uint8_t wrong_channel = 1 + (MBED_GREENTEA_WIFI_SECURE_CHANNEL % 10);
    nsapi_error_t error = wifi->connect(MBED_GREENTEA_WIFI_SECURE_SSID, MBED_GREENTEA_WIFI_SECURE_PASSWORD, get_wifi_security(), wrong_channel);
    TEST_ASSERT(error == NSAPI_ERROR_CONNECTION_TIMEOUT || error == NSAPI_ERROR_NO_CONNECTION);

    wifi->set_channel(0);
}

#endif // defined(MBED_GREENTEA_WIFI_SECURE_SSID)
