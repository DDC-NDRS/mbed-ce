/* Copyright (c) 2017 ARM Limited
 * Copyright (c) 2017 STMicroelectronics
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

#ifndef STM32_EMAC_H_
#define STM32_EMAC_H_

#include "EMAC.h"
#include "rtos/Mutex.h"

class STM32_EMAC : public EMAC {
public:
    STM32_EMAC();

    static STM32_EMAC &get_instance();

    /**
     * Return maximum transmission unit
     *
     * @return     MTU in bytes
     */
    virtual uint32_t get_mtu_size() const;

    /**
     * Gets memory buffer alignment preference
     *
     * Gets preferred memory buffer alignment of the Emac device. IP stack may or may not
     * align link out memory buffer chains using the alignment.
     *
     * @return         Memory alignment requirement in bytes
     */
    virtual uint32_t get_align_preference() const;

    /**
     * Return interface name
     *
     * @param name Pointer to where the name should be written
     * @param size Maximum number of character to copy
     */
    virtual void get_ifname(char *name, uint8_t size) const;

    /**
     * Returns size of the underlying interface HW address size.
     *
     * @return     HW address size in bytes
     */
    virtual uint8_t get_hwaddr_size() const;

    /**
     * Return interface-supplied HW address
     *
     * Copies HW address to provided memory, @param addr has to be of correct size see @a get_hwaddr_size
     *
     * HW address need not be provided if this interface does not have its own HW
     * address configuration; stack will choose address from central system
     * configuration if the function returns false and does not write to addr.
     *
     * @param addr HW address for underlying interface
     * @return     true if HW address is available
     */
    virtual bool get_hwaddr(uint8_t *addr) const;

    /**
     * Set HW address for interface
     *
     * Provided address has to be of correct size, see @a get_hwaddr_size
     *
     * Called to set the MAC address to actually use - if @a get_hwaddr is provided
     * the stack would normally use that, but it could be overridden, eg for test
     * purposes.
     *
     * @param addr Address to be set
     */
    virtual void set_hwaddr(const uint8_t *addr);

    /**
     * Sends the packet over the link
     *
     * That can not be called from an interrupt context.
     *
     * @param buf  Packet to be send
     * @return     True if the packet was send successfully, False otherwise
     */
    virtual bool link_out(emac_mem_buf_t *buf);

    /**
     * Initializes the HW
     *
     * @return True on success, False in case of an error.
     */
    virtual bool power_up();

    /**
     * Deinitializes the HW
     *
     */
    virtual void power_down();

    /**
     * Sets a callback that needs to be called for packets received for that interface
     *
     * @param input_cb Function to be register as a callback
     */
    virtual void set_link_input_cb(emac_link_input_cb_t input_cb);

    /**
     * Sets a callback that needs to be called on link status changes for given interface
     *
     * @param state_cb Function to be register as a callback
     */
    virtual void set_link_state_cb(emac_link_state_change_cb_t state_cb);

    /** Add device to a multicast group
     *
     * @param address  A multicast group hardware address
     */
    virtual void add_multicast_group(const uint8_t *address);

    /** Remove device from a multicast group
     *
     * @param address  A multicast group hardware address
     */
    virtual void remove_multicast_group(const uint8_t *address);

    /** Request reception of all multicast packets
     *
     * @param all True to receive all multicasts
     *            False to receive only multicasts addressed to specified groups
     */
    virtual void set_all_multicast(bool all);

    /** Sets memory manager that is used to handle memory buffers
     *
     * @param mem_mngr Pointer to memory manager
     */
    virtual void set_memory_manager(EMACMemoryManager &mem_mngr);

    // Called from driver functions
    ETH_HandleTypeDef EthHandle;
    osThreadId_t thread; /**< Processing thread */

private:
    bool low_level_init_successful();
    void packet_rx();
    int low_level_input(emac_mem_buf_t **buf);
    static void thread_function(void *pvParameters);
    static void rmii_watchdog_thread_function(void *pvParameters);
    void phy_task();
    void enable_interrupts();
    void disable_interrupts();

    // Populate multicast filter registers with the contents of mcastMacs.
    // Uses the perfect filter registers first, then the hash filter.
    void populateMcastFilterRegs();

    // Write a MAC address into a high and low register pair on the MAC.
    static void writeMACAddress(uint8_t const * MAC, uint32_t volatile * addrHighReg, uint32_t volatile * addrLowReg);

    mbed_rtos_storage_thread_t thread_cb;
#if defined (STM32F767xx) || defined (STM32F769xx) || defined (STM32F777xx)\
    || defined (STM32F779xx)
    mbed_rtos_storage_thread_t rmii_watchdog_thread_cb;
    osThreadId_t rmii_watchdog_thread; /**< Watchdog processing thread */
#endif
    rtos::Mutex TXLockMutex;/**< TX critical section mutex */
    rtos::Mutex RXLockMutex;/**< RX critical section mutex */
    emac_link_input_cb_t emac_link_input_cb; /**< Callback for incoming data */
    emac_link_state_change_cb_t emac_link_state_cb; /**< Link state change callback */
    EMACMemoryManager *memory_manager; /**< Memory manager */

    uint32_t phy_status;
    int phy_task_handle; /**< Handle for phy task event */

    // Multicast subscribe information
    std::array<uint8_t, 6> mcastMacs[MBED_CONF_STM32_EMAC_MAX_MCAST_SUBSCRIBES];
    size_t numSubscribedMcastMacs;
};

#endif /* STM32_EMAC_H_ */
