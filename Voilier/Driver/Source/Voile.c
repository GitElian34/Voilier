#include "Voile.h"

void Voile_config(void){
// Activer l'horloge pour TIM3 et GPIOA
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRL &= ~(0xF << (1 * 4)); // Effacer les bits pour PB1
	GPIOB->CRL |= (0xB << (1 * 4));  // Mode alternatif 50 MHz, push-pull

	// Configurer TIM3 en mode PWM
	TIM3->CCMR2 &= ~(0xF << (1 * 12));
	TIM3->CCMR2 |= (6 << 12); // PWM mode 1
	TIM3->CCMR2 |= TIM_CCMR2_OC4PE;          // Activer le preload

	TIM3->CCER |= TIM_CCER_CC4E;             // Activer la sortie PWM sur le canal 4 (PB1)

	TIM3->PSC = 24 - 1;             // Diviseur pour un timer de 72 MHz / 1000 = 72 kHz
  TIM3->ARR = 20000 - 1;             // Période totale de 20 ms (1 / 50 Hz)

	TIM3->CR1 |= TIM_CR1_CEN;                // Activer le timer

}


float Voile_Affine(float alpha){
	float teta = 0;
	if (alpha <= 180.0 && alpha >45.0){
		teta = (2./3.) * alpha - 30.;
	}
	else if (alpha > 180.0 && alpha < 315.0){
		teta = -(2./3.)*alpha + 210.;
		//float ecart = alpha -180.;
		//teta = 360. - (-(2./3.) * ecart + 90.) ;
	}else{
		teta = 0.;
	}
	return teta;
}

void Voile_Set_teta(float alpha){
	float teta = Voile_Affine(alpha);
	TIM3->CCR4 = map_angle_to_pwm(teta);
}

uint16_t map_angle_to_pwm(float teta) {
	teta = ((int) (teta/5.0)) *5.0;
	if (teta < 0) teta = 0;       // Limiter l'angle minimum
  if (teta > 90) teta = 90;     // Limiter l'angle maximum
  float ms = 2.0 - (teta / 90.0); // Map 0-90° à 1.0-2.0 ms
  return (uint16_t)(ms * 1000);  // Convertir en unité de timer
}