
#ifndef VOILE_H
#define VOILE_H

#include "stm32f10x.h"

void Voile_config(void);
float Voile_Affine(float);
void Voile_Set_teta(float);
uint16_t map_angle_to_pwm(float);

#endif // GIROUETTE_H