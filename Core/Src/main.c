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
#include "bmi160_port.h"
#include "bmi160.h"
#include "bmp3.h"
#include "bmp3_selftest.h"
#include "bmp388_port.h"
#include "pid.h"
#include "usbd_cdc_if.h"
#include "rtwtypes.h"
#include "QuadcopterModel.h"
#include "hmc5883l.h"
#include "MadgwickAHRS.h"
#include "RCFilter.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "task_handles.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ACCEL_SENSITIVITY		( ( double )( 16384.0f ) )
#define GYRO_SENSITIVITY		( ( double )( 16.4f) )
#define ALPHA					( ( double )( 0.1f ) )
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */

/**
  * @brief  BMI160 IMU Sensor Data Types
  */
struct complementary euler_angles = {0};
struct bmi160_dev bmi160 = {0};													/*! 	@brief variable to hold the bmi160 main data 		*/
struct bmi160_sensor_data bmi160_accel = {0};									/*! 	@brief variable to hold the bmi160 accel data 		*/
struct bmi160_sensor_data bmi160_gyro = {0};									/*! 	@brief variable to hold the bmi160 gyro data 		*/
struct bmp160_interface bmi160_intf = {0};										/*! 	@brief variable to hold the bmi160 interface 		*/

/**
  * @brief  BMP388 Pressure Sensor Data Types
  */
struct bmp3_dev bmp388 = {0};													/*! 	@brief variable to hold the bmp388 main data 		*/
struct bmp3_data bmp388_data = {0};												/*!	 	@brief variable to hold the bmp388 pressure data 	*/
struct bmp388_interface bmp388_intf = {&htim6,&hi2c1,BMP388_DEV_ADDR};			/*! 	@brief variable to hold the bmp388 interface 		*/

/**
  * @brief  HMC5883L Magnetometer Sensor Data Types
  */
struct hmc5883l_dev hmc5883l = {0};
struct hmc5883l_dev_intf hmc5883l_intf = {&hi2c1};
struct hmc5883l_data hmc5883l_mag = {0};

char usb_msg[100];

float acc_x = 0.0f , acc_y = 0.0f , acc_z = 0.0f , gyro_x = 0.0f , gyro_y = 0.0f , gyro_z = 0.0f;

RCFilter lowpassfilter = {0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM6_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /*!< Flight Hardware Object Initilization >!*/
  struct FlightControlData_t quadcopter_obj = {0};
  quadcopter_obj.pBMI160   = 	(struct bmi160_dev*)&bmi160;
  quadcopter_obj.pBMP388   = 	(struct bmp3_dev*)&bmp388;
  quadcopter_obj.pHMC5883L =	(struct hmc5883l_dev*)&hmc5883l;
  quadcopter_obj.pHardware->pBMI160Interface->hi2c = (I2C_HandleTypeDef*)&hi2c1;
  quadcopter_obj.pHardware->pBMI160Interface->htim = (I2C_HandleTypeDef*)&htim6;
  quadcopter_obj.pHardware->pBMP388Interface->hi2c = (I2C_HandleTypeDef*)&hi2c1;
  quadcopter_obj.pHardware->pBMP388Interface->htim = (I2C_HandleTypeDef*)&htim6;
  quadcopter_obj.pHardware->pHMC5883LInterface->hi2c = (I2C_HandleTypeDef*)&hi2c1;

























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

  //  SCB->CPACR |= (0xF << 20); // CP10 ve CP11'i full erişim (11) yap
  //
  //  rtU.w1=100;
  //  rtU.w2=50;
  //  rtU.w3=50;
  //  rtU.w4=200;
  //
  //  QuadcopterModel_initialize();

  //  /*!< BMP388 Init Process >!*/
  //  init_bmp388_sensor_driver_interface(&bmp388,&bmp388_intf);
  //  calibration_bmp388_sensor(&bmp388, &bmp388_data, 1000U);

  /*!< Complementary Filter Init >!*/
  //Complementary_Init(&euler_angles, 0.0f, 1.0f);

  /*!< BMI160 Init >!*/
  //bmi160_interface_init(&bmi160);

  /*
   * Accelerometer and Gyroscope Calibration
   * Kalibrasyon sırasında sensör hareketsiz bir şekilde düz bir zeminde durmalı !!!
   */


  /*!< HMC5883L Init Process >!*/
  hmc5883l_dev.intfptr = &hmc5883l_intf;
  hmc5883l_dev.read_func = hmc5883l_read;
  hmc5883l_dev.write_func = hmc5883l_write;

  if ( hmc5883l_init(&hmc5883l_dev) != HMC5883L_OK)
  {
	  printf("HMC5883L init error !\n");
	  Error_Handler();
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  hmc5883l_get_data(&hmc5883l_dev, &hmc5883l_mag);

	  sprintf(usb_msg,"%f,%f,%f\r\n",hmc5883l_mag.mx,hmc5883l_mag.my,hmc5883l_mag.mz);
	  CDC_Transmit_FS((uint8_t*)usb_msg,strlen(usb_msg));
	  HAL_Delay(1);

//	  if( bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL),&bmi160_accel, &bmi160_gyro, &bmi160) != BMI160_OK)
//	  {
//		  printf("BMI160 sensor data failed !\n");
//		  Error_Handler();
//	  }

//	  acc_x = (double)bmi160_accel.x/ACCEL_SENSITIVITY - acc_x_offset;
//	  acc_y = (double)bmi160_accel.y/ACCEL_SENSITIVITY - acc_y_offset;
//	  acc_z = (double)bmi160_accel.z/ACCEL_SENSITIVITY - acc_z_offset;
//
//	  gyro_x = (double)bmi160_gyro.x/GYRO_SENSITIVITY - gyr_x_offset;
//	  gyro_y = (double)bmi160_gyro.y/GYRO_SENSITIVITY - gyr_y_offset;
//	  gyro_z = (double)bmi160_gyro.z/GYRO_SENSITIVITY - gyr_z_offset;
//
//	  Complementary_Update(&euler_angles,acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z,0,0,0);



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  hi2c1.Init.ClockSpeed = 100000;
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

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
//int _write(int file, char *ptr, int len)
//{
//  HAL_UART_Transmit(&huart2,(uint8_t*)ptr,len,HAL_MAX_DELAY);
//  return len;
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, 1U);
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
