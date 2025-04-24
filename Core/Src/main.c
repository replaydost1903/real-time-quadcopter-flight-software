/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "complementary.h"
#include "bmi160.h"
#include "bmi160_port.h"
#include "bmp3.h"
#include "bmp3_selftest.h"
#include "bmp388_port.h"
#include "pid.h"
#include "usbd_cdc_if.h"
#include "flight_stabilization_loop.h"
#include "rtwtypes.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "task_handles.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ACCEL_SENSITIVITY		( ( double )( 2048.0f ) )
#define GYRO_SENSITIVITY		( ( double )( 16.4f) )
#define ALPHA					( ( double )( 0.1f ) )
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/**
  * @brief  BMI160 IMU Sensor Data Types
  */
struct complementary bmi160_comp = {0};
struct bmi160_dev bmi160 = {0};													/*! 	@brief variable to hold the bmi160 main data 		*/
struct bmi160_sensor_data bmi160_accel = {0};									/*! 	@brief variable to hold the bmi160 accel data 		*/
struct bmi160_sensor_data bmi160_gyro = {0};									/*! 	@brief variable to hold the bmi160 gyro data 		*/
struct bmp160_interface bmi160_intf = {0};			/*! 	@brief variable to hold the bmi160 interface 		*/

/**
  * @brief  BMP388 Pressure Sensor Data Types
  */
struct bmp3_dev bmp388 = {0};						/*! 	@brief variable to hold the bmp388 main data 		*/
struct bmp3_data bmp388_data = {0};					/*!	 	@brief variable to hold the bmp388 pressure data 	*/
struct bmp388_interface bmp388_intf = {&htim6,&hi2c2,BMP388_DEV_ADDR};			/*! 	@brief variable to hold the bmp388 interface 		*/


//TaskHandle_t task1_handle,task2_handle,task3_handle,task4_handle,task5_handle;
char usb_ch;
int flag=0;
char buffer1[] = "You sent 1,get 1 back\r\n";
char buffer2[] = "You sent 2,get 2 back\r\n";
char buffer3[] = "You sent 3,get 3 back\r\n";
double sum=0.0f;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
double pitch;
double roll;
double yaw;
double x;
double y;
double z;
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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /*!< BMI160 Init Process >!*/
  //Complementary_Init(&bmi160_comp, 0.7f, 50.0f);
  //init_bmi160_sensor_driver_interface(&bmi160);

  /*!< BMP388 Init Process >!*/
  init_bmp388_sensor_driver_interface(&bmp388,&bmp388_intf);

  /*!< Segger System View Init >!*/
//  DWT->CTRL |= (1 << 0);
//
//  SEGGER_SYSVIEW_Conf();
//
//  SEGGER_SYSVIEW_Start();
//
//  /*!< FreeRTOS Task Creation >!*/
//  configASSERT(xTaskCreate(vTask1, "Task-1", (uint16_t)496, NULL, 3U, &task1_handle));
//  configASSERT(xTaskCreate(vTask2, "Task-2", (uint16_t)496, NULL, 3U, &task2_handle));
//  configASSERT(xTaskCreate(vTask3, "Task-3", (uint16_t)496, NULL, 3U, &task3_handle));
//  configASSERT(xTaskCreate(vTask4, "Task-4", (uint16_t)496, NULL, 3U, &task4_handle));
//  configASSERT(xTaskCreate(vTask5, "Task-5", (uint16_t)496, NULL, 3U, &task5_handle));

  /* Start the scheduler so the tasks start executing. */
  //vTaskStartScheduler();

  /*
  * If all is well main() will not reach here because the scheduler will now
  * be running the created tasks. If main() does reach here then there was
  * not enough heap memory to create either the idle or timer tasks
  * (described later in this book). Chapter 3 provides more information on
  * heap memory management.
  */
  //printf("Not enough heap memory !\n");
  //Error_Handler();
    char text[100];
//  uint8_t i=0;
//
//  rtU.w1=200;
//  rtU.w2=200;
//  rtU.w3=50;
//  rtU.w4=500;
//
//  SCB->CPACR |= (0xF << 20); // CP10 ve CP11'i full erişim (11) yap
//
//  flight_stabilization_loop_initialize();
//  int count=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//	  while (i++<5)
//	  {
//		  if ( get_bmp388_sensor_data(&bmp388,&bmp388_data) != BMP3_OK  )
//		  {
//			  Error_Handler();
//		  }
//
//		  if ( get_bmp388_altitude_data(&bmp388_data) != BMP3_OK )
//		  {
//			  Error_Handler();
//		  }
//
//		  sum += bmp388_data.altitude[2];
//
//		  HAL_Delay(20);
//	  }
//
//	  sum /= i;
//	  i=0;

//	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
//	  {
//		  HAL_Delay(10);
//		  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));
//		  count^=1;
//	  }
//
//	  if(count)
//	  {
//		  flight_stabilization_loop_step();
//
//		  HAL_Delay(1000);
//		  sprintf(text,"yaw = %f\t\n",yaw);
//		  CDC_Transmit_FS((uint8_t*)text, strlen(text));
//	  }


//	  sum=0.0f;

	  calibration_bmp388_sensor(&bmp388, &bmp388_data, 50U);
	  sprintf(text,"reference %f\t\n",bmp388_data.altitude[1]);
	  CDC_Transmit_FS((uint8_t*)text, strlen(text));
	  HAL_Delay(200);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 400000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 167;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GREEN_LED_Pin|ORANGE_LED_Pin|RED_LED_Pin|BLUE_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : GREEN_LED_Pin ORANGE_LED_Pin RED_LED_Pin BLUE_LED_Pin */
  GPIO_InitStruct.Pin = GREEN_LED_Pin|ORANGE_LED_Pin|RED_LED_Pin|BLUE_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int _write(int file, char *ptr, int len)
{
  HAL_UART_Transmit(&huart2,(uint8_t*)ptr,len,HAL_MAX_DELAY);
  return len;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

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
