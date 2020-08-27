/*
 * Bluetooth.h
 *
 *  Created on: Aug 25, 2020
 *      Author: Dream
 */

#ifndef DREAM_COMMUNICATION_BLUETOOTH_H_
#define DREAM_COMMUNICATION_BLUETOOTH_H_

void bluetooth_DMA(UART_HandleTypeDef *huart);
void myUart_DMA(UART_HandleTypeDef *huart);
void myUart_DMA_Callback(UART_HandleTypeDef *huart);

#endif /* DREAM_COMMUNICATION_BLUETOOTH_H_ */
