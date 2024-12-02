#ifndef PLATEAU_H
#define PLATEAU_H

#include "stm32f10x.h"

void Plateau_config(void);
void Plateau_Set_Governail(int8_t);
void Plateau_Sens(uint8_t);
float Plateau_PWM(uint8_t);

#endif // PLATEAU_H