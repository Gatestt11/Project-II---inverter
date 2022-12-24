#include "lcd16x2.h"


void LCD_Configure(void) 
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void LCD_Enable() 
{
    HAL_GPIO_WritePin(GPIOB, EN_Pin, 1);
    //HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOB,EN_Pin,0);
    //HAL_Delay(1);
}

void LCD_Send4bit(uint8_t Data)
{
    HAL_GPIO_WritePin(GPIOB,D4_Pin, Data&(0x01));
    HAL_GPIO_WritePin(GPIOB,D5_Pin, (Data>>1)&(0x01));
    HAL_GPIO_WritePin(GPIOB,D6_Pin, (Data>>2)&(0x01));
    HAL_GPIO_WritePin(GPIOB,D7_Pin, (Data>>3)&(0x01));
}

void LCD_SendCommand(uint8_t Command)
{
    LCD_Send4bit((Command>>4));
    LCD_Enable();
    LCD_Send4bit(Command);
    LCD_Enable();
}

void LCD_Init() 
{
    LCD_Configure();
    HAL_GPIO_WritePin(GPIOB, RS_Pin, 0);
    HAL_GPIO_WritePin(GPIOB, RW_Pin, 0);
    //HAL_Delay(30);
    LCD_SendCommand(0x02);
    LCD_SendCommand(0x28);
    LCD_SendCommand(0x0C);
    LCD_SendCommand(0x06);
    LCD_SendCommand(0x01);
}

void LCD_Gotoxy(uint8_t x)
{
    if (x==0) 
    {
        LCD_SendCommand(0x80);
    }
    else
    {
        LCD_SendCommand(0xC0);
    }
}

void LCD_PutChar(uint8_t Data)
{
    HAL_GPIO_WritePin(GPIOB, RS_Pin, 1);
    LCD_SendCommand(Data);
    HAL_GPIO_WritePin(GPIOB, RS_Pin, 0);
}

void LCD_Puts(char *s) 
{
    while(*s)
    {
        LCD_PutChar(*s);
        s++;
    }
}

void LCD_Clear(void) 
{
    LCD_SendCommand(0x01);
    //HAL_Delay(1);
}
