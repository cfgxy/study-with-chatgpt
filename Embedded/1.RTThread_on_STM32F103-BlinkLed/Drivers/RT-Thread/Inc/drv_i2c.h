/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-04-20     RiceChen      first version
 */

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#include "drv_common.h"
#include "pin.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_I2C1
#define RT_I2C1_SCL_PIN            GET_PIN(B, 6)
#define RT_I2C1_SDA_PIN            GET_PIN(B, 7)

#define RT_I2C1_CONFIG                                         \
    {                                                          \
        .name = "i2c1",                                        \
        .scl = RT_I2C1_SCL_PIN,                                \
        .sda = RT_I2C1_SDA_PIN,                                \
    }
#endif

#ifdef RT_USING_I2C2
#define RT_I2C2_SCL_PIN            GET_PIN(B, 8)
#define RT_I2C2_SDA_PIN            GET_PIN(B, 9)

#define RT_I2C2_CONFIG                                         \
    {                                                          \
        .name = "i2c2",                                        \
        .scl = RT_I2C2_SCL_PIN,                                \
        .sda = RT_I2C2_SDA_PIN,                                \
    }
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

