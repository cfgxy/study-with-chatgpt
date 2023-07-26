/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-22     RiceChen      first version
 */

#ifndef __ADC_H__
#define __ADC_H__
#include "rtthread.h"

struct rt_adc_device
{
  uint8_t *user_data;
};
typedef struct rt_adc_device *rt_adc_device_t;

typedef enum
{
  RT_ADC_CMD_ENABLE,
  RT_ADC_CMD_DISABLE,
} rt_adc_cmd_t;

struct rt_adc_device *rt_adc_device_find(const char *name);
rt_uint32_t rt_adc_read(rt_adc_device_t dev, rt_uint32_t channel);
rt_err_t rt_adc_enable(rt_adc_device_t dev, rt_uint32_t channel);
rt_err_t rt_adc_disable(rt_adc_device_t dev, rt_uint32_t channel);

#endif /* __ADC_H__ */
