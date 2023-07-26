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
#include "pin.h"
#include "button.h"

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static void key_cb(struct my_button *button);

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
  /** 注册按钮回调 */
  static struct my_button key = {0};
  key.press_logic_level = PIN_HIGH;
  key.hold_cyc_period = 100;
  key.cb = (my_button_callback)key_cb;
  key.pin = BUTTON_PIN;
  my_button_register(&key);

  LOG_D("Hello RT-Thread!");

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
  return 0;
}
INIT_BOARD_EXPORT(uart_gpio_port_C);

/**
 * 闪灯逻辑
 */
static void blink_led()
{
  rt_pin_write(LED0_PIN, PIN_HIGH);
  rt_thread_delay(500);
  rt_pin_write(LED0_PIN, PIN_LOW);
}

/**
 * 按钮事件回调
 * @param button
 */
static void key_cb(struct my_button *button)
{
  switch (button->event)
  {
    case BUTTON_EVENT_CLICK_UP:
      rt_kprintf("This is click up callback!\n");

      rt_thread_t tid;
      tid = rt_thread_find("blink_led");
      if (tid == RT_NULL) {
        tid = rt_thread_create("blink_led", blink_led, RT_NULL,
                               RT_MAIN_THREAD_STACK_SIZE, 10, 20);
        rt_thread_startup(tid);
      } else {
        LOG_D("last blink not finished.");
      }

      break;
    case BUTTON_EVENT_HOLD_CYC:
      rt_kprintf("This is hold cyc callback!\n");
      break;
    default:
      ;
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
