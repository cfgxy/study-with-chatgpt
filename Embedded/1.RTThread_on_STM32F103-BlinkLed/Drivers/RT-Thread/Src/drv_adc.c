/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-21     RiceChen     the first version
 */

#include "../Inc/drv_adc.h"

#ifdef RT_USING_ADC

struct rt_i2c_config
{
    char *name;
    ADC_HandleTypeDef ADC_Handler;
};

struct rt_i2c_config adc_config[] =
{
#ifdef RT_USING_ADC1
    ADC1_CONFIG,
#endif
};

struct stm32_adc
{
    struct rt_i2c_config *config;
    struct rt_adc_device stm32_adc_device;
};

static struct stm32_adc stm32_adc_obj[sizeof(adc_config) / sizeof(adc_config[0])];

static rt_err_t stm32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    ADC_HandleTypeDef *stm32_adc_handler;
    RT_ASSERT(device != RT_NULL);
    stm32_adc_handler = (ADC_HandleTypeDef *)device->user_data;

    rt_kprintf("%d: 0x%08x\r\n", __LINE__, stm32_adc_handler);

    if (enabled)
    {
        ADC_Enable(stm32_adc_handler);
    }
    else
    {
        ADC_Disable(stm32_adc_handler);
    }

    return RT_EOK;
}

static rt_uint32_t stm32_adc_get_channel(rt_uint32_t channel)
{
    rt_uint32_t stm32_channel = 0;

    switch (channel)
    {
    case  0:
        stm32_channel = ADC_CHANNEL_0;
        break;
    case  1:
        stm32_channel = ADC_CHANNEL_1;
        break;
    case  2:
        stm32_channel = ADC_CHANNEL_2;
        break;
    case  3:
        stm32_channel = ADC_CHANNEL_3;
        break;
    case  4:
        stm32_channel = ADC_CHANNEL_4;
        break;
    case  5:
        stm32_channel = ADC_CHANNEL_5;
        break;
    case  6:
        stm32_channel = ADC_CHANNEL_6;
        break;
    case  7:
        stm32_channel = ADC_CHANNEL_7;
        break;
    case  8:
        stm32_channel = ADC_CHANNEL_8;
        break;
    case  9:
        stm32_channel = ADC_CHANNEL_9;
        break;
    case 10:
        stm32_channel = ADC_CHANNEL_10;
        break;
    case 11:
        stm32_channel = ADC_CHANNEL_11;
        break;
    case 12:
        stm32_channel = ADC_CHANNEL_12;
        break;
    case 13:
        stm32_channel = ADC_CHANNEL_13;
        break;
    case 14:
        stm32_channel = ADC_CHANNEL_14;
        break;
    case 15:
        stm32_channel = ADC_CHANNEL_15;
        break;
    }

    return stm32_channel;
}

static rt_err_t stm32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    ADC_ChannelConfTypeDef ADC_ChanConf;
    ADC_HandleTypeDef *stm32_adc_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    stm32_adc_handler = (ADC_HandleTypeDef *)device->user_data;

    rt_memset(&ADC_ChanConf, 0, sizeof(ADC_ChanConf));

    if (channel <= 18)
    {
        /* set stm32 ADC channel */
        ADC_ChanConf.Channel =  stm32_adc_get_channel(channel);
    }
    else
    {
        rt_kprintf("ADC channel must be between 0 and 18.");
        return -RT_ERROR;
    }

    ADC_ChanConf.Rank = 1;
    ADC_ChanConf.SamplingTime = ADC_SAMPLETIME_247CYCLES_5;
    ADC_ChanConf.Offset = 0;
    ADC_ChanConf.OffsetNumber = ADC_OFFSET_NONE;
    ADC_ChanConf.SingleDiff = LL_ADC_SINGLE_ENDED;
    HAL_ADC_ConfigChannel(stm32_adc_handler, &ADC_ChanConf);

    if (HAL_ADCEx_Calibration_Start(stm32_adc_handler, ADC_ChanConf.SingleDiff) != HAL_OK)
    {
        rt_kprintf("ADC calibration error!\n");
        return -RT_ERROR;
    }
    /* start ADC */
    HAL_ADC_Start(stm32_adc_handler);

    /* Wait for the ADC to convert */
    HAL_ADC_PollForConversion(stm32_adc_handler, 100);

    /* get ADC value */
    *value = (rt_uint32_t)HAL_ADC_GetValue(stm32_adc_handler);

    return RT_EOK;
}

rt_uint32_t rt_adc_read(rt_adc_device_t dev, rt_uint32_t channel)
{
    rt_uint32_t value;

    RT_ASSERT(dev);

    stm32_get_adc_value(dev, channel, &value);

    return value;
}

rt_err_t rt_adc_enable(rt_adc_device_t dev, rt_uint32_t channel)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev);

    result = stm32_adc_enabled(dev, channel, RT_TRUE);

    return result;
}

rt_err_t rt_adc_disable(rt_adc_device_t dev, rt_uint32_t channel)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev);

    result = stm32_adc_enabled(dev, channel, RT_FALSE);

    return result;
}

struct rt_adc_device *rt_adc_device_find(const char *name)
{
    int i = 0;
    for (i = 0; i < sizeof(adc_config) / sizeof(adc_config[0]); i++)
    {
        if(rt_strncmp(stm32_adc_obj[i].config->name, name, RT_NAME_MAX) == 0)
        {
            return &stm32_adc_obj[i].stm32_adc_device;
        }
    }
    return RT_NULL;
}

static int rt_hw_adc_init(void)
{
    int i = 0;
    for (i = 0; i < sizeof(adc_config) / sizeof(adc_config[0]); i++)
    {
        stm32_adc_obj[i].config = &adc_config[i];
        stm32_adc_obj[i].stm32_adc_device.user_data = (uint8_t *)&stm32_adc_obj[i].config->ADC_Handler;
        rt_kprintf("%d: 0x%08x\r\n", __LINE__, &stm32_adc_obj[i].config->ADC_Handler);

        rt_kprintf("%d: 0x%08x\r\n", __LINE__, ADC1);
        rt_kprintf("%d: 0x%08x\r\n", __LINE__, stm32_adc_obj[i].config->ADC_Handler.Instance);

        if (HAL_ADC_Init(&stm32_adc_obj[i].config->ADC_Handler) != HAL_OK)
        {
            rt_kprintf("%s init failed", stm32_adc_obj[i].config->name);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}
INIT_APP_EXPORT(rt_hw_adc_init);

void adc_get_obj(void)
{
    int32_t value = 0;
    struct rt_adc_device *dev = RT_NULL;
    dev = rt_adc_device_find("adc1");
    if(dev == RT_NULL)
    {
        rt_kprintf("%s not found\r\n", "adc1");
        return;
    }
    else
    {
        rt_adc_enable(dev, 3);
        value = rt_adc_read(dev, 3);
        rt_kprintf("adc value: %d\r\n", value);
    }
}
MSH_CMD_EXPORT(adc_get_obj, adc_get_obj);

#endif /* RT_USING_ADC */
