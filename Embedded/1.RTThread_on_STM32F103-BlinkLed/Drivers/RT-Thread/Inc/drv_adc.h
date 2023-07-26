/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-04-20     RiceChen      first version
 */

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include "drv_common.h"
#include "adc.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_ADC1
#ifndef ADC1_CONFIG
#define ADC1_CONFIG                                                        \
    {                                                                      \
       .name                                   = "adc1",                        \
       .ADC_Handler.Instance                   = ADC1,                          \
       .ADC_Handler.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4,      \
       .ADC_Handler.Init.Resolution            = ADC_RESOLUTION_12B,            \
       .ADC_Handler.Init.DataAlign             = ADC_DATAALIGN_RIGHT,           \
       .ADC_Handler.Init.ScanConvMode          = DISABLE,                       \
       .ADC_Handler.Init.EOCSelection          = DISABLE,                       \
       .ADC_Handler.Init.ContinuousConvMode    = DISABLE,                       \
       .ADC_Handler.Init.NbrOfConversion       = 1,                             \
       .ADC_Handler.Init.DiscontinuousConvMode = DISABLE,                       \
       .ADC_Handler.Init.NbrOfDiscConversion   = 0,                             \
       .ADC_Handler.Init.ExternalTrigConv      = ADC_SOFTWARE_START,            \
       .ADC_Handler.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE, \
       .ADC_Handler.Init.DMAContinuousRequests = DISABLE,                       \
    }
#endif /* ADC1_CONFIG */
#endif /* RT_USING_ADC1 */

#ifdef __cplusplus
}
#endif

#endif /* __DRV_ADC_H__ */

