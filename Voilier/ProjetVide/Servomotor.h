#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include "stm32f10x.h" // Inclure le header correspondant à votre microcontrôleur

void Servo_Config(void);         // Configuration initiale du servomoteur
float Servo_Angle_To_PWM(float angle); // Convertir un angle (0°-180°) en largeur d'impulsion (1ms-2ms)
void Servo_Set_Angle(float angle);     // Positionner le servomoteur à un angle donné

#endif // SERVOMOTOR_H