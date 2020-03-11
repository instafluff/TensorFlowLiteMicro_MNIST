#ifndef __STM32_APP_H
#define __STM32_APP_H

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"

#ifdef __cplusplus
 extern "C" {
#endif

void delay( int n );
void clear_display();
void draw_text( char* text, uint32_t color );
void draw_pixel( uint32_t x, uint32_t y, uint32_t color );
void setup();
void loop();

#ifdef __cplusplus
}
#endif

#endif // __STM32_APP_H