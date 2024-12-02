#ifndef UART_H
#define UART_H

#include "stm32f10x.h"

void UART_config(void);
void UART_SendChar(char);
char UART_ReceiveChar(void);
void UART_SendString(const char *);
void UART_Angle_Message(float);


#endif // UART_H