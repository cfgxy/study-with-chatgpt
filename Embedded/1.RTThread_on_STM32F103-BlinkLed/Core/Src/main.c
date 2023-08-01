/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtdbg.h"
#include <rtthread.h>
#include "time.h"
#include "pin.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED0_PIN    GET_PIN(C, 12)
#define BUTTON_PIN  GET_PIN(C, 13)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
rt_thread_t thread_blink_led = RT_NULL;
rt_uint8_t gLedBlinking = 0;
rt_uint64_t gButtonHolding = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static void key_cb(void *args);
static void blink_led(void *args);
static void button_holding(void *args);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  /* user app entry */
  LOG_D("Hello RT-Thread!");
  rt_thread_t tid = rt_thread_create(
    "blink_led",
    blink_led,
    RT_NULL,
    RT_MAIN_THREAD_STACK_SIZE,
    10,
    20
  );
  rt_thread_startup(tid);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // 让出时间片
    rt_thread_delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */


/**
 * 这个函数在 rt_hw_board_init() 阶段被自动调用
 * @brief 系统时钟设置
 * @retval None
 */
__USED void SystemClock_Config(void)
{

  /**
   * 配置时钟源
   */
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** 配置时钟分频和输出 */
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * 这个函数在 rt_components_board_init() 阶段被自动调用
 * @brief GPIO初始化
 * @retval None
 */
static int uart_gpio_port_C(void)
{
  // LED 针脚初始化
  rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
  rt_pin_attach_irq(BUTTON_PIN, PIN_IRQ_MODE_RISING_FALLING, key_cb, RT_NULL);
  rt_pin_irq_enable(BUTTON_PIN, PIN_IRQ_ENABLE);
  return 0;
}
INIT_BOARD_EXPORT(uart_gpio_port_C);

/**
 * 闪灯逻辑
 */
static void blink_led(void *args)
{
  while (1) {
    if (gLedBlinking) {
      rt_pin_write(LED0_PIN, PIN_HIGH);
      rt_thread_delay(500);
      rt_pin_write(LED0_PIN, PIN_LOW);
      rt_thread_delay(500);
    } else {
      rt_thread_delay(100);
    }
  }
}

static void button_holding(void *args)
{
  rt_uint64_t start = gButtonHolding;

  rt_thread_delay(500);
  if (gButtonHolding == 0) {
    return;
  }

  while (1) {
    if (gButtonHolding == 0) {
      rt_kprintf("Button released!\n");
      break;
    }

    if (gButtonHolding != start) {
      rt_kprintf("Button released!\n");
      start = gButtonHolding;
    }

    time_t now = rt_tick_get() * 1000 / RT_TICK_PER_SECOND;
    rt_kprintf("Button hold %dms!\n", (int)(now - start));
    rt_thread_delay(2000);
  }
}

/**
 * 按钮事件回调
 * @param button
 */
static void key_cb(void *args)
{
  // 处理长按事件
  int pinValue = rt_pin_read(BUTTON_PIN);
  if (pinValue == PIN_HIGH) {
    gButtonHolding = rt_tick_get() * 1000 / RT_TICK_PER_SECOND;

    rt_thread_t tid = RT_NULL;
    tid = rt_thread_find("button_holding");

    if (tid == RT_NULL) {
      tid = rt_thread_create(
        "button_holding",
        button_holding,
        RT_NULL,
        RT_MAIN_THREAD_STACK_SIZE,
        10,
        20
      );
      rt_thread_startup(tid);
    }
  } else {
    // 闪灯开关
    gLedBlinking = !gLedBlinking;
    if (gLedBlinking) {
      rt_kprintf("Start Led Blinking!\n");
    } else {
      rt_kprintf("Stop Led Blinking!\n");
    }

    // 停止长按监测
    gButtonHolding = 0;
  }
}

/* USER CODE END 4 */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
