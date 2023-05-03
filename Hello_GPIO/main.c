#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{

	/* HAL_Init() is same as below */
	volatile unsigned int* reg = 0x40022000;
	*reg |= 16;

	SystemClock_Config();

	/* MX_GPIO_Init() is same as below */

	/* __HAL_RCC_GPIOC_CLK_ENABLE() is same as below */
	volatile unsigned int* reg2 = 0x40021018;
	*reg2 |= 16;

	/*
	  Configure GPIO pin : GPIO_LED_Pin
  	  GPIO_InitTypeDef GPIO_InitStruct = {0};
  	  GPIO_InitStruct.Pin = GPIO_LED_Pin;
  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  	  HAL_GPIO_Init(GPIO_LED_GPIO_Port, &GPIO_InitStruct);

  	  upper is same as below
	 */
	volatile unsigned int* reg3 = 0x40011004;
	*reg3 = (*reg3 & ~(15UL << 20U)) | (3U << 20U);

	volatile unsigned int* reg4 = 0x40011010;

  while (1)
  {
	  // PC13 LED on
	  *reg4 = 0x2000;
	  HAL_Delay(250);

	  // PC13 LED off
	  *reg4 = (0x2000 << 16);
	  HAL_Delay(250);
  }
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
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


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIO_LED_GPIO_Port, GPIO_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : GPIO_LED_Pin */
  GPIO_InitStruct.Pin = GPIO_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIO_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : GPIO_SW_Pin */
  GPIO_InitStruct.Pin = GPIO_SW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIO_SW_GPIO_Port, &GPIO_InitStruct);

}


void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
