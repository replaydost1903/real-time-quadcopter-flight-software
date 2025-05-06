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
#include "KalmanFilter1D.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "task_handles.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ALPHA					( ( double )( 0.95f ) )
#define DEGREES_TO_RADIAN		(( double )((M_PI / 180.0f)))
#define RADIAN_TO_DEGREES		(( double )((180.0f / M_PI)))
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */
struct bmi160_dev bmi160={0};													/*! 	@brief variable to hold the bmi160 main data 		*/
struct bmp3_dev bmp388={0};													/*! 	@brief variable to hold the bmp388 main data 		*/
struct bmp388_interface bmp388_intf = {&htim6,&hi2c1,BMP388_DEV_ADDR};			/*! 	@brief variable to hold the bmp388 interface 		*/
struct hmc5883l_dev hmc5883l = {0};
struct hmc5883l_interface hmc5883l_intf = {&hi2c1};
double first_altitude = 0.0f ,last_altitude = 0.0f , altitude = 0.0f , filtered_altitude = 0.0f;
uint8_t key = 1U;

struct bmp3_status status = { { 0 } };
int8_t rslt = 0U;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char usb_msg[200] = {0};
float filtered_ax_f=0.0f,filtered_ay_f=0.0f,filtered_az_f=0.0f,filtered_gx_f=0.0f,filtered_gy_f=0.0f,filtered_gz_f=0.0f;
float ax_f=0.0f,ay_f=0.0f,az_f=0.0f,gx_f=0.0,gy_f=0.0f,gz_f=0.0f;
float gx_f_rad=0.0f,gy_f_rad=0.0f,gz_f_rad=0.0f;
float roll=0.0f,pitch=0.0f,yaw=0.0f;
float nonfilteredval = 0.0f , dynamic_alpha = 0.90f;
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /*!< Initialise bmi160 sensor >!*/
//  if ( bmi160_interface_init(&bmi160) != BMI160_OK)
//  {
//	  printf("BMI160 not initialised !\n");
//	  Error_Handler();
//  }

  /*!< Calibration process for bmi160 sensor >!*/
//  if ( bmi160_calibration(&bmi160,3000U) != BMI160_OK)
//  {
//	  printf("BMI160 not initialised !\n");
//	  Error_Handler();
//  }

//  Kalman_Init(&kalmanRoll);
//  Kalman_Init(&kalmanPitch);
//
//  RCFilter roll_lowpass,pitch_lowpass;
//
//  RCFilter_Init(&roll_lowpass, 5.0f,0.02f);
//  RCFilter_Init(&pitch_lowpass, 5.0f,0.02f);
//
//  // Filtrelenmiş ivme verileri
//  float ax_f = 0.0f, ay_f = 0.0f, az_f = 0.0f;
//
//  // Filtrelenmiş gyro verileri
//  float gx_f = 0.0f, gy_f = 0.0f, gz_f = 0.0f;

//  /*!< Initialise bmp388 sensor >!*/
//  if ( bmp388_interface_init(&bmp388, &bmp388_intf) != BMP3_OK )
//  {
//	  Error_Handler();
//  }
//
//  /*!< Calibration process for bmp388 sensor >!*/
//  if ( bmp388_calibration(&bmp388, 1000U) != BMP3_OK )
//  {
//	  Error_Handler();
//  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*!< Get calibrated data for bmi160 sensor >!*/
//	  if ( bmi160_get_acc_gyro(&bmi160) != BMI160_OK)
//	  {
//		  printf("BMI160 isnt get data !\n");
//		  Error_Handler();
//	  }

	  /*!< Convert int16_t to float data types >!*/
//	  ax_f = bmi160.accel_data.xd;
//	  ay_f = bmi160.accel_data.yd;
//	  az_f = bmi160.accel_data.zd;
//	  gx_f = bmi160.gyro_data.xd;
//	  gy_f = bmi160.gyro_data.yd;
//	  gz_f = bmi160.gyro_data.zd;

	  /*!< First-order simple low-pass low-pass filter applied to 3-axis accelerometer data >!*/
	  //filtered_ax_f = ALPHA * filtered_ax_f + (1 - ALPHA) * (bmi160.accel_data.xd);
	  //filtered_ay_f = ALPHA * filtered_ay_f + (1 - ALPHA) * (bmi160.accel_data.yd);
	  //filtered_az_f = ALPHA * filtered_az_f + (1 - ALPHA) * (bmi160.accel_data.zd);

	  /*!< First-order simple low-pass low-pass filter applied to 3-axis gyroscope data >!*/
	  //filtered_gx_f = ALPHA * filtered_gx_f + (1 - ALPHA) * (bmi160.gyro_data.xd);
	  //filtered_gy_f = ALPHA * filtered_gy_f + (1 - ALPHA) * (bmi160.gyro_data.yd);
	  //filtered_gz_f = ALPHA * filtered_gz_f + (1 - ALPHA) * (bmi160.gyro_data.zd);

	  /*!< (°/s) data converted to (rad/s) for angular velocity >!*/
	  //gx_f_rad = filtered_gx_f * DEGREES_TO_RADIAN;
	  // gy_f_rad = filtered_gy_f * DEGREES_TO_RADIAN;
	  //gz_f_rad = filtered_gz_f * DEGREES_TO_RADIAN;

	  //sprintf(usb_msg,"%f,%f,%f,%f,%f,%f\r\n",ax_f,ay_f,az_f,filtered_ax_f,filtered_ay_f,filtered_az_f);
	  //sprintf(usb_msg,"%f,%f,%f,%f,%f,%f\r\n",gx_f,gy_f,gz_f,filtered_gx_f,filtered_gy_f,filtered_gz_f);
	  //CDC_Transmit_FS((uint8_t*)usb_msg,strlen(usb_msg));

	  //IMU_Update(filtered_ax_f/9.81f, filtered_ay_f/9.81f, filtered_az_f/9.81f, gx_f_rad, gy_f_rad, gz_f_rad, &roll, &pitch, &yaw);

	  //sprintf(usb_msg,"%f,%f,%f,%f,%f,%f\r\n",ax_f,ay_f,az_f,filtered_ax_f,filtered_ay_f,filtered_az_f);
	  //sprintf(usb_msg,"%f,%f,%f,%f,%f,%f\r\n",gx_f,gy_f,gz_f,filtered_gx_f,filtered_gy_f,filtered_gz_f);
      //sprintf(usb_msg,"%f,%f\r\n",pitch,roll);
	  //sprintf(usb_msg,"%f,%f,%f,%f\r\n",q0,q1,q2,q3);
      //sprintf(usb_msg,"Orientation: %.2f %.2f %.2f\r\n",roll,pitch,yaw);
      //CDC_Transmit_FS((uint8_t*)usb_msg,strlen(usb_msg));


	  /*!< Get calibrated data for bmp388 sensor >!*/
//	  if ( bmp388_get_altitude(&bmp388, ALPHA) != BMP3_OK )
//	  {
//		  Error_Handler();
//	  }
//
//	  sprintf(usb_msg,"%f\r\n",(float)bmp388.pressure_data.relative_altitude);
//
//	  CDC_Transmit_FS((uint8_t*)usb_msg,strlen(usb_msg));

	  //sprintf(usb_msg,"Orientation: %.2f %.2f %.2f\r\n",roll,pitch,yaw);









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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
