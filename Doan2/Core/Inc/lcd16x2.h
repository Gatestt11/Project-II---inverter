#ifndef __LCD_16x2_H__
#define __LCD_16x2_H__

#include "stm32f1xx_hal.h"
#include "string.h"

#define RS_Pin  GPIO_PIN_3
#define RW_Pin  GPIO_PIN_4
#define EN_Pin  GPIO_PIN_5
#define D4_Pin  GPIO_PIN_6
#define D5_Pin  GPIO_PIN_7
#define D6_Pin  GPIO_PIN_8
#define D7_Pin  GPIO_PIN_9

void LCD_Enable(void);
void LCD_Send4bit(uint8_t Data);
void LCD_SendCommand(uint8_t Command);
void LCD_Init(void);
void LCD_Gotoxy(uint8_t x);
void LCD_PutChar(uint8_t Data);
void LCD_Puts(char *s);
void LCD_Clear(void);



#endif
