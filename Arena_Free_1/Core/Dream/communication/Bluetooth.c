/*
 * Bluetooth.c
 *
 *  Created on: Aug 25, 2020
 *      Author: Dream
 */

#include "macro.h"
#include "string.h"
#include "stdio.h"

#define BUFFER_SIZE 255

uint8_t receive_buff[BUFFER_SIZE];

extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;

void bluetooth_DMA(UART_HandleTypeDef *huart)
{
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
	HAL_UART_Receive_DMA(huart, (uint8_t*) receive_buff, BUFFER_SIZE);

}

//自己定义的DMA处理函数
//在USART1_IRQHandler()中添加本函数，用来处理串口空闲中断
void myUart_DMA(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		if (RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))  //判断是不是串口空闲中断
		{
			__HAL_UART_CLEAR_IDLEFLAG(huart);				  	  //清楚串口空闲中断标志
			myUart_DMA_Callback(huart);
		}
	}
}

void myUart_DMA_Callback(UART_HandleTypeDef *huart)
{
	HAL_UART_DMAStop(huart);

//	uint8_t buff;

	uint8_t data_length = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx); //计算收到数据的长度

	printf("length: %d", data_length);
	HAL_UART_Transmit(huart, receive_buff, data_length, 0x200);  //测试用，发出接收到的数据
	printf("/r/n");

	//添加处理接收数据的代码，接收数据存在receive_buff内

//	if (data_length == 1)                           //判断接收数据长度，1为指令模式
//	{
////		buff = receive_buff[0];
////		switch (buff)
////		{
////		case 1:
////			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//////			HAL_UART_Transmit(huart, buff, data_length, 0x200);
////			printf("%d", 22);
////			break;
////		case 2:
////			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
////			HAL_UART_Transmit(huart, buff, data_length, 0x200);
////			break;
////		case 3:
////			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
////			HAL_UART_Transmit(huart, buff, data_length, 0x200);
////			break;
////		default:
////			HAL_UART_Transmit(huart, buff, data_length, 0x200);
////		}
//	}
//	else
//	{
//		HAL_UART_Transmit(huart, receive_buff, data_length, 0x200);
//	}

	//--------------------------------------------------
	memset(receive_buff, 0, data_length);                       //清零接收缓冲区
	data_length = 0;

	HAL_UART_Receive_DMA(huart, (uint8_t*) receive_buff, 255); //重新开启DMA传输，每次255字节数
}

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 0xffff);
	return ch;
}

