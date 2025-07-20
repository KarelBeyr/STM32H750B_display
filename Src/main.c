/**
  ******************************************************************************
  * @file    Display/LTDC_Paint/Src/main.c 
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "save.h"
#include "color.h"
#include <stdbool.h>
/** @addtogroup STM32H7xx_HAL_Applications
  * @{
  */

/** @addtogroup LTDC_Paint
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {
  APPLICATION_IDLE = 0,  
  APPLICATION_RUNNIG    
}MSC_ApplicationTypeDef;


typedef enum {
    STATE_F1,
    STATE_F2,
    STATE_F3,
} AppState;

typedef enum { // A bit atypical, but I want to be able to read data from PC connected through UART for better UX
  KEY_0 = '0',
  KEY_1 = '1',
  KEY_2 = '2',
  KEY_3 = '3',
  KEY_4 = '4',
  KEY_5 = '5',
  KEY_6 = '6',
  KEY_7 = '7',
  KEY_8 = '8',
  KEY_9 = '9',
  KEY_Enter = 'e',
  KEY_Clear = 'c',
  KEY_BkSp = 'b',
  KEY_Start = 'S',
  KEY_Stop = 's',
  KEY_ESC = '`',
  KEY_F1 = '!',
  KEY_F2 = '@',
  KEY_F3 = '#',
  KEY_F4 = '$',
  KEY_F5 = '%',
  KEY_Dot = '.',
  KEY_Lock = 'l',
  KEY_OFF = 'f',
  KEY_ON = 'n'
} KeyboardButton;

typedef struct {
	AppState currentState;

	// F1 - screen where user enters voltage and can start/stop PWM
  uint16_t voltage; // register holding voltage that has been validated and is ready to be sent to PWM
  uint16_t inputValue; // register holding current value of "input field"
  bool isVoltageEntered; // flag if we are ready to start PWM. Maybe redundant, we can check against voltage register. But its more robust this way
  bool isPwmRunning;
  char message[64]; // ad hoc message to display

    // F2 - screen where user sets three calibration points - TODO later
    uint16_t calibration_points[3]; // For mapping
} AppContext;

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} GPIOPin;


#define NUM_ROWS 5
#define NUM_COLS 5

GPIOPin rowPins[NUM_ROWS] = {
    { GPIOG, GPIO_PIN_3 }, //D2
    { GPIOA, GPIO_PIN_6 }, //D3
    { GPIOK, GPIO_PIN_1 }, //D4
    { GPIOA, GPIO_PIN_8 }, //D5
    { GPIOE, GPIO_PIN_6 }
};

GPIOPin colPins[NUM_COLS] = {
    { GPIOI, GPIO_PIN_8 },
    { GPIOE, GPIO_PIN_3 },
    { GPIOH, GPIO_PIN_15 },
    { GPIOB, GPIO_PIN_4 },
	{ GPIOB, GPIO_PIN_15 }
};

const char keymap[5][5] = {
    {KEY_ESC,   KEY_6,    KEY_8,     KEY_Lock, KEY_F1},
    {KEY_3,     KEY_5,    KEY_7,     KEY_F5,   KEY_OFF},
    {KEY_2,     KEY_4,    KEY_Enter, KEY_F4,   KEY_ON},
    {KEY_1,     KEY_Clear,KEY_Dot,   KEY_F3,   KEY_Stop},
    {KEY_BkSp,  KEY_9,    KEY_0,     KEY_F2,   KEY_Start}
};

volatile int lastRow = -1;
volatile int lastCol = -1;
volatile uint32_t lastTriggerTime = 0;
uint8_t receivedChar;


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

 DMA2D_HandleTypeDef hdma2d_discovery;

uint16_t x = 0, y = 0;
 uint32_t x_size, y_size;
TS_Init_t *hTS;
UART_HandleTypeDef huart3;

const uint32_t aBMPHeader[14]=         
{0x13A64D42, 0x00000004, 0x00360000, 0x00280000, 0x01A40000, 0x00D40000, 0x00010000, 
 0x00000018, 0xF5400000, 0x00000006, 0x00000000, 0x00000000, 0x00000000, 0x0000};

/* Variable to save the state of USB */
MSC_ApplicationTypeDef Appli_state = APPLICATION_IDLE;

uint8_t workBuffer[_MAX_SS];

/* Private function prototypes -----------------------------------------------*/
static void Draw_Menu(void);
static void SystemClock_Config(void);
static void Error_Handler(void);
static void CPU_CACHE_Enable(void);
static void CPU_CACHE_Disable(void);
static void MPU_Config(void);
static void GPIO_Init(void);
static void MX_USART3_UART_Init(void);
void readFlexiKeyboard();

int __io_putchar(int ch) {
  if (HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY) != HAL_OK) {
    return -1;
  }
  return ch;
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(huart->Instance==USART3)
  {
  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3;
    PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }

}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Configure the MPU attributes as Write Through for SDRAM*/
  MPU_Config();
  
  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

  /* STM32H7xx HAL library initialization:
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();
  
  /* Configure the system clock to 400 MHz */
  SystemClock_Config(); 

  GPIO_Init();
  MX_USART3_UART_Init();

 printf("Hi there :)!\r\n");

  /* Configure LED1 */
  BSP_LED_Init(LED1);

  /*##-1- LCD Initialization #################################################*/
  /* Initialize the LCD */
  BSP_LCD_Init(0, LCD_ORIENTATION_LANDSCAPE);
  UTIL_LCD_SetFuncDriver(&LCD_Driver);

  /* Set Foreground Layer */
  UTIL_LCD_SetLayer(0);

  /* Clear the LCD Background layer */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_BLACK);
  BSP_LCD_GetXSize(0, &x_size);
  BSP_LCD_GetYSize(0, &y_size);

  hTS->Width = x_size;
  hTS->Height = y_size;
  hTS->Orientation =TS_SWAP_XY ;
  hTS->Accuracy = 5;
  /* Touchscreen initialization */
  BSP_TS_Init(0, hTS);


  /*##-6- Draw the menu ######################################################*/
  //CPU_CACHE_Disable();
  Draw_Menu();
  CPU_CACHE_Enable();
  /* Infinite loop */  
  while (1)
  {

	  HAL_Delay(100);
	  readFlexiKeyboard(); // approx 25ms blocking code to scan the keyboard

//	  GPIO_PinState l = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
//	  printf("Level %d\r\n", l);
  }
}

void setAllRowsInactive(void)
{
    for (int i = 0; i < NUM_ROWS; i++) {
        HAL_GPIO_WritePin(rowPins[i].port, rowPins[i].pin, GPIO_PIN_SET);
    }
}

void setRowActive(int row)
{
    if (row < 0 || row >= NUM_ROWS)
        return;

    setAllRowsInactive();
    HAL_GPIO_WritePin(rowPins[row].port, rowPins[row].pin, GPIO_PIN_RESET);
}

void readFlexiKeyboard(void)
{
    for (int row = 0; row < NUM_ROWS; row++)
    {
        setRowActive(row);    // Set current row LOW, others HIGH
        HAL_Delay(5);         // Small delay for settling

        for (int col = 0; col < NUM_COLS; col++)
        {
        	//if (col == 3) break;
            if (HAL_GPIO_ReadPin(colPins[col].port, colPins[col].pin) == GPIO_PIN_RESET)
            {
//                uint32_t now = HAL_GetTick();
//
//                // Debounce/repeat suppression
//                if (lastRow == row && lastCol == col && (now - lastTriggerTime < 300)) {
//                    return;
//                }
//
//                lastRow = row;
//                lastCol = col;
//                lastTriggerTime = now;

                // Key at (row, col) pressed!
                receivedChar = keymap[row][col];
                printf("Pressed row %d and col %d hopefully it is %c\r\n", row, col, receivedChar);



//                AppEvent evt = {
//                    .type = EVENT_KEY_PRESSED,
//                    .key = receivedChar
//                };

                // handle_event(&ctx, &evt); // Uncomment if needed
                break; // Optionally break to avoid multiple key detections per scan
            }
        }

        //setAllRowsInactive();  // Set all rows HIGH before next row scan
    }
}

static void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	 __HAL_RCC_GPIOI_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOK_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOJ_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOF_CLK_ENABLE();


//	  /*Configure GPIO pin Output Level */
//	  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET);
//
//	  /*Configure GPIO pin Output Level */
//	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
//
//	  /*Configure GPIO pin Output Level */
//	  HAL_GPIO_WritePin(GPIOK, GPIO_PIN_1, GPIO_PIN_RESET);
//
//	  /*Configure GPIO pin Output Level */
//	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
//
//	  /*Configure GPIO pin Output Level */
//	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);


	    // --- Configure row pins as OUTPUT ---
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	    for (int i = 0; i < NUM_ROWS; i++) {
	        GPIO_InitStruct.Pin = rowPins[i].pin;
	        HAL_GPIO_Init(rowPins[i].port, &GPIO_InitStruct);

	        // Set initial output state (HIGH = inactive)
	        HAL_GPIO_WritePin(rowPins[i].port, rowPins[i].pin, GPIO_PIN_RESET);
	    }

	    // --- Configure column pins as INPUT with PULL-UP ---
	    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;

	    for (int i = 0; i < NUM_COLS; i++) {
	        GPIO_InitStruct.Pin = colPins[i].pin;
	        HAL_GPIO_Init(colPins[i].port, &GPIO_InitStruct);
	    }
}

/**
  * @brief  Draws the menu.
  * @param  None
  * @retval None
  */
static void Draw_Menu(void)
{ 
  UTIL_LCD_SetLayer(0);
  
  UTIL_LCD_Clear(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetFont(&Font32);
  for (int i = 0; i < 8; i++) {
	  UTIL_LCD_DisplayStringAt(0, i * 32, (uint8_t *)"Hello Jaja! Hello zabak", LEFT_MODE);
  }
}

static void MX_USART3_UART_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  while(1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 400000000 (CPU Clock)
  *            HCLK(Hz)                       = 200000000 (AXI and AHBs Clock)
  *            AHB Prescaler                  = 2
  *            D1 APB3 Prescaler              = 2 (APB3 Clock  100MHz)
  *            D2 APB1 Prescaler              = 2 (APB1 Clock  100MHz)
  *            D2 APB2 Prescaler              = 2 (APB2 Clock  100MHz)
  *            D3 APB4 Prescaler              = 2 (APB4 Clock  100MHz)
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 5
  *            PLL_N                          = 160
  *            PLL_P                          = 2
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;

  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInitStruct.PLL3.PLL3M = 5;
  PeriphClkInitStruct.PLL3.PLL3N = 96;
  PeriphClkInitStruct.PLL3.PLL3P = 2;
  PeriphClkInitStruct.PLL3.PLL3Q = 10;
  PeriphClkInitStruct.PLL3.PLL3R = 18;
  
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_2;

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL3;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  
  /* Select PLL as system clock source and configure  bus clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 | \
                                 RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_D3PCLK1);

  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
  if(ret != HAL_OK)
  {
    Error_Handler();
  }
  /*activate CSI clock mondatory for I/O Compensation Cell*/
  __HAL_RCC_CSI_ENABLE() ;

  /* Enable SYSCFG clock mondatory for I/O Compensation Cell */
  __HAL_RCC_SYSCFG_CLK_ENABLE() ;

  /* Enables the I/O Compensation Cell */
  HAL_EnableCompensationCell();
}
/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

static void CPU_CACHE_Disable(void)
{
  /* Enable I-Cache */
  SCB_DisableICache();

  /* Enable D-Cache */
  SCB_DisableDCache();
}

/**
  * @brief  Clock Config.
  * @param  hltdc: LTDC handle
  * @param  Params: Pointer to void
  * @note   This API is called by BSP_LCD_Init()
  *         Being __weak it can be overwritten by the application
  * @retval None
  */
HAL_StatusTypeDef MX_LTDC_ClockConfig(LTDC_HandleTypeDef *hltdc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hltdc);

  static RCC_PeriphCLKInitTypeDef  periph_clk_init_struct;

  /* RK043FN48H LCD clock configuration */
  /* LCD clock configuration */
  /* PLL3_VCO Input = HSE_VALUE/PLL3M = 5 Mhz */
  /* PLL3_VCO Output = PLL3_VCO Input * PLL3N = 800 Mhz */
  /* PLLLCDCLK = PLL3_VCO Output/PLL3R = 800/83 = 9.63 Mhz */
  /* LTDC clock frequency = PLLLCDCLK = 9.63 Mhz */
  periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  periph_clk_init_struct.PLL3.PLL3M = 5;
  periph_clk_init_struct.PLL3.PLL3N = 192;
  periph_clk_init_struct.PLL3.PLL3P = 2;
  periph_clk_init_struct.PLL3.PLL3Q = 20;
  periph_clk_init_struct.PLL3.PLL3R = 99;

  return HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct);
}
/**
  * @brief  Configure the MPU attributes as Write Through for External SDRAM.
  * @note   The Base Address is 0xD0000000 .
  *         The Configured Region Size is 32MB because same as SDRAM size.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SDRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = SDRAM_DEVICE_ADDR;
  MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

