//
// Created by cfgxy on 2023/7/26.
//

#ifndef _BUTTON_H_
#define _BUTTON_H_


#include "rtthread.h"

#define MY_BUTTON_DOWN_MS        50
#define MY_BUTTON_HOLD_MS        1000
#define MY_BUTTON_SCAN_SPACE_MS  50
#define MY_BUTTON_LIST_MAX       256

typedef void (*my_button_callback)(void *args);

enum my_button_event
{
  BUTTON_EVENT_CLICK_DOWN, /* 按键单击按下事件 */
  BUTTON_EVENT_CLICK_UP,   /* 按键单击结束事件 */
  BUTTON_EVENT_HOLD,       /* 按键长按开始事件 */
  BUTTON_EVENT_HOLD_CYC,   /* 按键长按周期性触发事件 */
  BUTTON_EVENT_HOLD_UP,    /* 按键长按结束事件 */
  BUTTON_EVENT_NONE        /* 无按键事件 */
};

struct my_button
{
  rt_int8_t   event_start;        /* 按键触发事件的起始标志 */
  rt_uint8_t  press_logic_level;  /* 按键按下时的电平 */
  rt_uint8_t  release_logic_level;/* 按键释放时的电平 */
  rt_uint16_t cnt;                /* 连续扫描到按下状态的次数 */
  rt_uint16_t hold_cyc_period;    /* 长按周期回调的周期 */
  rt_uint16_t pin;                /* 按键对应的 pin 编号 */

  enum my_button_event event;     /* 按键的触发的事件 */

  my_button_callback cb;          /* 按键触发事件回调函数 */
};

struct my_button_manage
{
  rt_uint8_t num;                 /* 已注册的按键的数目 */
  rt_timer_t timer;               /* 按键扫描用到的定时器 */
  struct my_button *button_list[MY_BUTTON_LIST_MAX];  /* 存储按键指针的数组 */
};


int my_button_register(struct my_button *button);

#endif //_BUTTON_H_
