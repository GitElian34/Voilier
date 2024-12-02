#define BATTERIE_H
#include "stm32f10x.h"

int Batterie_read(void);
void Batterie_write(int batterie);
void ADC_Config(void);
uint16_t ADC_Read(void);