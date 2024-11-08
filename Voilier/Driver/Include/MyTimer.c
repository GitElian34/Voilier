#include "MyTimer.h"
#include "core_cm3.h"
#include "stdio.h"


//typedef struct 
//{
//	TIM_TypeDef * Timer ; // TIM1 à TIM4
//	unsigned short ARR ;
//	unsigned short PSC ;
//} MyTimer_Struct_TypeDef ;

//fonctions pour les callbacks
void (*f1) (void) = NULL;
void (*f2) (void)= NULL;
void (*f3) (void);
void (*f4) (void);


void MyTimer_Base_Init( MyTimer_Struct_TypeDef * Timer1 ) {
	//on met à 1 le bit correspondant au timer pour le rendre enable
	if(Timer1->Timer == TIM1){
		RCC->APB2ENR |= (0x1<<11);
	}
	
	if(Timer1->Timer == TIM2){
		RCC->APB1ENR |= (0x1);
	}
	
	if(Timer1->Timer == TIM3){
		RCC->APB1ENR|= (0x1<<1);
	}
	
	if(Timer1->Timer == TIM4){
		RCC->APB1ENR |= (0x2<<11);
	}

	
	Timer1->Timer->PSC = Timer1->PSC;
	Timer1->Timer->ARR = Timer1->ARR;
	
	Timer1->Timer->CNT=0;
}


void TIM1_UP_IRQHandler (void){
	TIM1->SR &= ~(0x1<<0); 
	f1();
}


//ca ne fonctionne pas, la led ne clignote pas, comme si les handlers n'étaient pas liés
void TIM2_IRQHandler(void){
	if (f2 != NULL){
		f2();
	}
	TIM2->SR &= ~(0x1<<0);
}

void TIM3_IRQHandler (void){
	TIM3->SR &= ~(0x1<<0);
	f3();
}

void TIM4_IRQHandler (void){
	TIM4->SR &= ~(0x1<<0);
	f4();
}


void MyTimer_ActiveIT ( TIM_TypeDef * Timer1 , char Prio, void (*f) (void)) {
	Timer1->DIER |= (0x1<<8);
	Timer1->DIER |= (0x1<<0);
	
	if(Timer1 == TIM1){
		f1=f;
		NVIC_SetPriority(TIM1_UP_IRQn, Prio);
		NVIC_EnableIRQ(TIM1_UP_IRQn);
	}
	
	if(Timer1 == TIM2){
		f2=f;
		NVIC_SetPriority(TIM2_IRQn, Prio);
		NVIC_EnableIRQ(TIM2_IRQn);
	}
	
	if(Timer1 == TIM3){
		f3=f;
		NVIC_SetPriority(TIM3_IRQn, Prio);
		NVIC_EnableIRQ(TIM3_IRQn);
	}
	
	if(Timer1 == TIM4){
		f4=f;
		NVIC_SetPriority(TIM4_IRQn, Prio);
		NVIC_EnableIRQ(TIM4_IRQn);
	}
}

void MyTimer_Rapport_Cyclique(TIM_TypeDef * TimerBis, char Channel, int cycle){
	
	if(Channel == 1){
		TimerBis->CCR1 = cycle;
	}
	
	if(Channel == 2){
		TimerBis->CCR2 = cycle;
	}
	
	if(Channel == 3){
		TimerBis->CCR3 = cycle;
	}
	
	if(Channel == 4){
		TimerBis->CCR4 = cycle;
	}
}



void MyTimer_PWM( TIM_TypeDef * TimerBis, char Channel ){
	
	if(Channel == 1){
		TimerBis->CCR1 = TimerBis->ARR/2;
		TimerBis->CCMR1 &= ~(0x1<<4);
		TimerBis->CCMR1 |= (0x6<<4);
		TimerBis->CCER |= (0x1 <<0);
	}
	
	if(Channel == 2){
		TimerBis->CCR2 = TimerBis->ARR/2;
		TimerBis->CCMR1 &= ~(0x1<<12);
		TimerBis->CCMR1 |= (0x6<<12);
		TimerBis->CCER |= (0x1 <<4);
	}
	
	if(Channel == 3){
		TimerBis->CCR3 = TimerBis->ARR/2;
		TimerBis->CCMR2 &= ~(0x1<<4);
		TimerBis->CCMR2 |= (0x6<<4);
		TimerBis->CCER |= (0x1 <<8);
	}
	
	if(Channel == 4){
		TimerBis->CCR4 = TimerBis->ARR/2;
		TimerBis->CCMR2 &= ~(0x1<<12);
		TimerBis->CCMR2 |= (0x6<<12);
		TimerBis->CCER |= (0x1 <<12);
	}
	
}

