#include "Girouette.h"
#include <stdio.h>

volatile uint8_t interruption = 0;

 void Girouette_Config (void) {
 // Enable clock for TIM2 and GPIOA (assuming encoder connected to PAO and PAl for example)
 RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 
	 
 // Configure GPIO PAO and PAl as input floating for encoder interface 
GPIOA->CRL &= ~ ((0xF << (0 * 4)) | (0xF << (1 * 4)));
GPIOA->CRL |= ((0x4 << (0 * 4)) | (0x4 << (1 * 4)));
	 
 //configue I
 GPIOA->CRL &= ~(0xF << (4 * 4));
 GPIOA->CRL |= (0x8 << (4 * 4));
	 GPIOA->ODR |= (1<<4);
	 
// Configure TIM2 for Encoder mode 3 (count on both TIl and TI2 edges) 
TIM2-> SMCR &= ~TIM_SMCR_SMS; 
 TIM2->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
TIM2->CCMR1 &= ~ (TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
 TIM2->CCMR1 |= (TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0);
 TIM2->CCER &= ~ (TIM_CCER_CC1P | TIM_CCER_CC2P);
TIM2->ARR = 0xFFFF ;
 TIM2-> CR1 |= TIM_CR1_CEN;
 
// Configurer une interruption externe sur PA2 pour le "top zéro"
// Lier PA2 à EXTI2
AFIO->EXTICR[1] &= ~(0xF << (4 * 4));
//AFIO->EXTICR[1] |= (0x0 << (4 * 4));

// Configurer EXTI2 pour front montant
EXTI->IMR |= EXTI_IMR_MR4; // Activer l'interruption pour PA4
EXTI->RTSR |= EXTI_RTSR_TR4; // Activer le déclenchement sur front montant
//EXTI->FTSR &= ~EXTI_FTSR_TR2; // Désactiver le déclenchement sur front descendant

// Activer l'interruption EXTI2 dans le NVIC
NVIC_EnableIRQ(EXTI4_IRQn);

}
float Girouette_Read(void){
	float alpha = ((TIM2->CNT /4) % 360) *1.0;
	return alpha;

}

void EXTI4_IRQHandler (void) {
	if (EXTI->PR & EXTI_PR_PR4) { // Vérifier si l'interruption est due à PA4
		if(!interruption){
			TIM2->CNT = 0; // Réinitialiser le compteur
			interruption = 1;
			EXTI->IMR &= ~EXTI_IMR_MR4;
		}
		EXTI->PR |= EXTI_PR_PR4; // Effacer le drapeau d'interruption
	}
	}
