
#include "main.h"

uint8_t Rx_Buff[20]; 											// Buffer luu chuoi nhan duoc
uint8_t Rx_Data;             							// Luu byte nhan duoc
uint8_t Tx_Buff[20] = "Hello Vietnam";    // Buffer truyen di
uint8_t _rxIndex;                         // Con tro cua Rx_Buff
uint16_t Tx_Flag =0;                      // Co bao nhan thanh cong
uint16_t tmp;                      // Co bao nhan thanh cong

UART_HandleTypeDef huart2;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void dot(void);
void dash(void);
void SoundLetter(char text);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2 )
	{
		if(Rx_Data !=13 )
			{
				Rx_Buff[_rxIndex++] = Rx_Data;  // Them du lieu vao Buffer
			}
			else if(Rx_Data == 13)
			{
				_rxIndex = 0;              // Xoa con tro 
				Tx_Flag =1;                // Bat co 
			}
		HAL_UART_Receive_IT(&huart2, &Rx_Data, 1);
	}
	
}
int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART2_UART_Init();
	
	//__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	//__HAL_UART_ENABLE_IT(&huart2, UART_IT_TC);

	//HAL_UART_Transmit(&huart2, Tx_Buff, sizeof(Tx_Buff), 100);
	

	//HAL_UART_Receive_IT(&huart2, &Rx_Data,1);
	//HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);

 while (1)
  {

		HAL_UART_Receive_IT(&huart2, &Rx_Data,1);

		HAL_Delay(1000);

			for( int i =0; i< 20; i++)
			{
			SoundLetter(Rx_Buff[i]);
			Rx_Buff[i]=0;
			}

		
  }
  /* USER CODE END 3 */
}

void dot(void)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, 0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, 1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
}

void dash(void)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, 0);
	HAL_Delay(300);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, 1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
}

void SoundLetter(char text)
{
  switch(text)
  {
    case 'E':
      dot();
      return; 
    case 'T':
      dash();
      return; 
    case 'A':
      dot();
      dash();
      return;
    case 'O':
      dash();
      dash();
      dash();
      return; 
    case 'I':
      dot();
      dot();
      return;
    case 'N':
      dash();
      dot();
      return;
    case 'S':
      dot();
      dot();
      dot();
      return;
    case 'H':
      dot();
      dot();
      dot();
      dot();
      return;
    case 'R':
      dot();
      dash();
      dot();
      return;
    case 'D':
      dash();
      dot();
      dot();
      return;
    case 'L':
      dot();
      dash();
      dot();
      dot();
      return;
    case 'C':
      dash();
      dot();
      dash();
      dot();
      return;
    case 'U':
      dot();
      dot();
      dash();
      return;
    case 'M':
      dash();
      dash();
      return;
    case 'W':
      dot();
      dash();
      dash();
      return;
    case 'F':
      dot();
      dot();
      dash();
      dot();
      return;
    case 'G':
      dash();
      dash();
      dot();
      return;
    case 'Y':
      dash();
      dot();
      dash();
      dash();
      return;
    case 'P':
      dot();
      dash();
      dash();
      dot();
      return;
    case 'B':
      dash();
      dot();
      dot();
      dot();
      return;
    case 'V':
      dot();
      dot();
      dot();
      dash();
      return;
    case 'K':
      dash();
      dot();
      dash();
      return;
    case 'J':
      dot();
      dash();
      dash();
      dash();
      return;
    case 'X':
      dash();
      dot();
      dot();
      dash();
      return;
    case 'Q':
      dash();
      dash();
      dot();
      dash();
      return;
    case 'Z':
      dash();
      dash();
      dot();
      dot();
      return;
    case ' ':
      HAL_Delay(400);
      return; 
  }
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


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


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}


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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


