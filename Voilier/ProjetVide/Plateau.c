#include "Plateau.h"


void Plateau_config(void){
// Activer l'horloge pour TIM4 et GPIOA
	RCC->APB1ENR |= (1 << 2);
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	GPIOB->CRL &= ~(0xF << (4 * 6)); // Effacer les bits pour PB6
	GPIOB->CRL |= (0xB << (4 * 6));  // Mode alternatif 50 MHz, push-pull
	
	GPIOA->CRL &= ~(0xF << (4 * 5)); // Effacer les bits pour PA2
	GPIOA->CRL |= (0x3 << (4 * 5));  //  Mode sortie push-pull 50 MHz

	// Configurer TIM4 en mode PWM
	TIM4->CCMR1 &= ~(0xF << (1 * 5));
	TIM4->CCMR1 |= (6 << 4); // PWM mode 1
	TIM4->CCMR1 |= TIM_CCMR1_OC1PE;          // Activer le preload
	
	TIM4->PSC = 24 - 1;             // Diviseur pour un timer de 24 MHz / 1000 = 24 kHz
  TIM4->ARR = 20000 - 1;             // Période totale de 20 ms (1 / 50 Hz)

	TIM4->CCER |= TIM_CCER_CC1E;             // Activer la sortie PWM sur le canal 1 (PB6)

	TIM4->CR1 |= TIM_CR1_CEN;                // Activer le timer

}

void Plateau_Set_Governail(int8_t commande) {
    if (commande < -100) commande = -100;
    if (commande > 100) commande = 100;
    uint16_t pwm = 1000 + (commande + 100) * 5; // 1.0 ms à 2.0 ms
    if (pwm < 1000) pwm = 1000;
    if (pwm > 2000) pwm = 2000;
    TIM4->CCR1 = pwm;
}

void Plateau_Sens(uint8_t sens) {
  if (sens==0) {
		//GPIOA->BRR |= (1<<3); // Mettre PA2 à 0
		GPIOA->ODR &= ~(0xF<<5);
		GPIOA->ODR |= (0<<5);
  } else {
		//GPIOA->BSRR |= (1 << 3); // Mettre PA2 à 1   
		GPIOA->ODR &= ~(0xF<<5);
		GPIOA->ODR |= (1<<5);
   }
}

float Plateau_PWM(uint8_t duty) {
    if (duty > 100) duty = 100;
    float pwm_value = (TIM4->ARR) * duty / 100.0;
    TIM4->CCR1 = (uint16_t)pwm_value;
    return pwm_value;
}