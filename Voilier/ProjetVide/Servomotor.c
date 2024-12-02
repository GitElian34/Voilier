#include "Servomotor.h"

void Servo_Config(void) {
    // Activer l'horloge pour TIM3 et GPIOA
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Configurer PA3 en mode sortie alternative push-pull
    GPIOA->CRL &= ~(0xF << (3 * 4)); // Effacer les bits pour PA3
    GPIOA->CRL |= (0xB << (3 * 4)); // Mode alternatif 50 MHz, push-pull

    // Configurer TIM3 en mode PWM sur le canal 4
    TIM3->CCMR2 &= ~TIM_CCMR2_OC4M;          // Effacer les bits de configuration du canal 4
    TIM3->CCMR2 |= (6 << 12);                // PWM mode 1
    TIM3->CCMR2 |= TIM_CCMR2_OC4PE;          // Activer le preload

    TIM3->CCER |= TIM_CCER_CC4E;             // Activer la sortie PWM sur le canal 4 (PA3)

    TIM3->PSC = 72 - 1;                      // Diviseur pour un timer de 1 MHz (72 MHz / 72)
    TIM3->ARR = 20000 - 1;                   // Période de 20 ms (50 Hz)

    TIM3->CCR4 = 1500;                       // Valeur initiale de 1.5 ms (position neutre)

    TIM3->CR1 |= TIM_CR1_CEN;                // Activer le timer
}

uint16_t Servo_Angle_To_PWM(float angle) {
    // Convertir un angle (0° à 180°) en largeur d'impulsion PWM (1000-2000)
  float ms = 2.0- (angle/90.0);
	uint16_t ticks = (uint16_t) (ms*1000);
	return ticks;
}

void Servo_Set_Angle(float angle) {
    // Convertir l'angle en valeur PWM et mettre à jour CCR4

    TIM3->CCR4 = Servo_Angle_To_PWM(angle);
}