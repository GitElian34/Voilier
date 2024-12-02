
#define TIMER_H
#include "stm32f10x.h"

typedef struct 
{
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;

/*
*****************************************************************************************
* @brie f
* @param -> Paramè t r e sous forme d ’ une s t r u c t u r e ( son a d re s se ) con ten an t l e s
i n f o rm a ti o n s de base
* @Note -> F onc ti on à l a n c e r s y s t ématiquement avan t d ’ a l l e r pl u s en dé t a i l dans l e s
con f pl u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init( MyTimer_Struct_TypeDef * Timer1 ) ;
#define MyTimer_Base_Start(Timer1) ( Timer1->CR1 |= (0x1<<0) )
#define MyTimer_Base_Stop(Timer1) ( Timer1->CR1 &= ~(0x1<<0) )

//handler des timers
void TIM1_UP_IRQHandler(void);
void TIM2_IRQHandler( void );
void TIM3_IRQHandler (void);
void TIM4_IRQHandler (void);


/*
**************************************************************************************************
* @brief
* @param : - TIM_TypeDef * Timer : Timer conce rne
- char Prio : de 0 a 15
* @Note : La f o n c ti o n MyTime r_Base_ Ini t d oi t a v oir ete la n cee au p r e al a bl e
**************************************************************************************************
*/
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void (*IT_function) (void)) ;


void MyTimer_Rapport_Cyclique (TIM_TypeDef * Timer , char Channel, int cycle);
/**
* @brie f
* @param . . . .
* @Note A c ti v e l e channel sp é c i f i é suTimerr l e time r spé c i f i é
* l a g e s ti o n de l a c o n fi g u r a ti o n I /O n ’ e s t pas f a i t e dans c e t t e f o n c ti o n
* ni l e r é gl a ge de l a pé ri o d e de l a PWM (ARR, PSC)
*/
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) ;