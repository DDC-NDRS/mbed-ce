/*
 * Copyright (c) 2015-2016, Nuvoton Technology Corporation
 *
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

#include "dma_api.h"
#include "string.h"
#include "cmsis.h"
#include "mbed_assert.h"
#include "PeripheralNames.h"
#include "nu_modutil.h"
#include "nu_bitutil.h"
#include "dma.h"

#define NU_PDMA_CH_MAX      PDMA_CH_MAX     /* Specify maximum channels of PDMA */
#define NU_PDMA_CH_Pos      0               /* Specify first channel number of PDMA */
#define NU_PDMA_CH_Msk      (((1 << NU_PDMA_CH_MAX) - 1) << NU_PDMA_CH_Pos)

struct nu_dma_chn_s {
    void        (*handler)(uint32_t, uint32_t);
    uint32_t    id;
    uint32_t    event;
};

static int dma_inited = 0;
static uint32_t dma_chn_mask = 0;
static struct nu_dma_chn_s dma_chn_arr[NU_PDMA_CH_MAX];

static void pdma_vec(void);
static const struct nu_modinit_s dma_modinit = {DMA_0, PDMA_MODULE, 0, 0, PDMA_RST, PDMA_IRQn, (void *) pdma_vec};


void dma_init(void)
{
    if (dma_inited) {
        return;
    }

    dma_inited = 1;
    dma_chn_mask = ~NU_PDMA_CH_Msk;
    memset(dma_chn_arr, 0x00, sizeof (dma_chn_arr));

    // Enable IP clock
    CLK_EnableModuleClock(dma_modinit.clkidx);

    // Reset this module
    SYS_ResetModule(dma_modinit.rsetidx);

    PDMA_Open(dma_modbase(), 0);

    NVIC_SetVector(dma_modinit.irq_n, (uint32_t) dma_modinit.var);
    NVIC_EnableIRQ(dma_modinit.irq_n);
}

int dma_channel_allocate(uint32_t capabilities)
{
    if (! dma_inited) {
        dma_init();
    }

    int i = nu_cto(dma_chn_mask);
    if (i != 32) {
        dma_chn_mask |= 1 << i;
        memset(dma_chn_arr + i - NU_PDMA_CH_Pos, 0x00, sizeof (struct nu_dma_chn_s));
        return i;
    }

    // No channel available
    return DMA_ERROR_OUT_OF_CHANNELS;
}

int dma_channel_free(int channelid)
{
    PDMA_T * pdma = dma_modbase();

    // Make sure channel is disabled
    pdma->CHCTL &= ~(1 << channelid);

    // Also clear the request source for a channel in case still enabled.
    // This allows this request source to be assigned to a different channel later.
    PDMA_SetTransferMode(pdma,
                        channelid,
                        PDMA_MEM, // No peripheral
                        0,  // Scatter-gather disabled
                        0); // Scatter-gather descriptor address

    if (channelid != DMA_ERROR_OUT_OF_CHANNELS) {
        dma_chn_mask &= ~(1 << channelid);
    }

    return 0;
}

void dma_set_handler(int channelid, uint32_t handler, uint32_t id, uint32_t event)
{
    MBED_ASSERT(dma_chn_mask & (1 << channelid));

    dma_chn_arr[channelid - NU_PDMA_CH_Pos].handler = (void (*)(uint32_t, uint32_t)) handler;
    dma_chn_arr[channelid - NU_PDMA_CH_Pos].id = id;
    dma_chn_arr[channelid - NU_PDMA_CH_Pos].event = event;

    // Set interrupt vector if someone has removed it.
    NVIC_SetVector(dma_modinit.irq_n, (uint32_t) dma_modinit.var);
    NVIC_EnableIRQ(dma_modinit.irq_n);
}

PDMA_T *dma_modbase(void)
{
    return (PDMA_T *) NU_MODBASE(dma_modinit.modname);
}

static void pdma_vec(void)
{
    uint32_t intsts = PDMA_GET_INT_STATUS(dma_modbase());

    // Abort
    if (intsts & PDMA_INTSTS_ABTIF_Msk) {
        uint32_t abtsts = PDMA_GET_ABORT_STS(dma_modbase());
        // Clear all Abort flags
        PDMA_CLR_ABORT_FLAG(dma_modbase(), abtsts);

        while (abtsts) {
            int chn_id = nu_ctz(abtsts) - PDMA_ABTSTS_ABTIF0_Pos + NU_PDMA_CH_Pos;
            if (dma_chn_mask & (1 << chn_id)) {
                struct nu_dma_chn_s *dma_chn = dma_chn_arr + chn_id - NU_PDMA_CH_Pos;
                if (dma_chn->handler && (dma_chn->event & DMA_EVENT_ABORT)) {
                    dma_chn->handler(dma_chn->id, DMA_EVENT_ABORT);
                }
            }
            abtsts &= ~(1 << (chn_id - NU_PDMA_CH_Pos + PDMA_ABTSTS_ABTIF0_Pos));
        }
    }

    // Transfer done
    if (intsts & PDMA_INTSTS_TDIF_Msk) {
        uint32_t tdsts = PDMA_GET_TD_STS(dma_modbase());
        // Clear all transfer done flags
        PDMA_CLR_TD_FLAG(dma_modbase(), tdsts);

        while (tdsts) {
            int chn_id = nu_ctz(tdsts) - PDMA_TDSTS_TDIF0_Pos + NU_PDMA_CH_Pos;
            if (dma_chn_mask & (1 << chn_id)) {
                struct nu_dma_chn_s *dma_chn = dma_chn_arr + chn_id - NU_PDMA_CH_Pos;
                if (dma_chn->handler && (dma_chn->event & DMA_EVENT_TRANSFER_DONE)) {
                    dma_chn->handler(dma_chn->id, DMA_EVENT_TRANSFER_DONE);
                }
            }
            tdsts &= ~(1 << (chn_id - NU_PDMA_CH_Pos + PDMA_TDSTS_TDIF0_Pos));
        }
    }

    // Timeout
    uint32_t reqto = intsts & (PDMA_INTSTS_REQTOF0_Msk | PDMA_INTSTS_REQTOF1_Msk);
    if (reqto) {
        // Clear all Timeout flags
        PDMA->INTSTS = reqto;

        while (reqto) {
            int chn_id = nu_ctz(reqto) - PDMA_INTSTS_REQTOF0_Pos + NU_PDMA_CH_Pos;
            if (dma_chn_mask & (1 << chn_id)) {
                struct nu_dma_chn_s *dma_chn = dma_chn_arr + chn_id - NU_PDMA_CH_Pos;
                if (dma_chn->handler && (dma_chn->event & DMA_EVENT_TIMEOUT)) {
                    dma_chn->handler(dma_chn->id, DMA_EVENT_TIMEOUT);
                }
            }
            reqto &= ~(1 << (chn_id - NU_PDMA_CH_Pos + PDMA_INTSTS_REQTOF0_Pos));
        }
    }
}
