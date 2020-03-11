#include "stm32_app.h"

static void SystemClock_Config( void );

void delay( int n )
{
  HAL_Delay( n );
}

void clear_display()
{
  BSP_LCD_Clear( LCD_COLOR_WHITE );
}

void draw_text( char* text, uint32_t color )
{
  BSP_LCD_SetTextColor( color );
  BSP_LCD_SetFont( &Font20 );
  BSP_LCD_DisplayStringAt( 0, 4, (uint8_t*) text, CENTER_MODE );
}

void draw_pixel( uint32_t x, uint32_t y, uint32_t color )
{
  BSP_LCD_SetTextColor( color );
  BSP_LCD_FillRect( x * 8, y * 8, 8, 8 );
}

int main( void )
{
  SCB_EnableICache();
  SCB_EnableDCache();

  HAL_Init();

  SystemClock_Config();

  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit( 0, LCD_FB_START_ADDRESS );
  BSP_LCD_DisplayOn();
  BSP_LCD_SelectLayer( 0 );

  setup();
  while (1)
  {
    loop();
  }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Activate the OverDrive to reach the 216 MHz Frequency */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
  
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }  
}