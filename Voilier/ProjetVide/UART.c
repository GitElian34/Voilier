#include "UART.h"

int precedent=8;

void UART_config(void){
 // Activer l'horloge pour USART1 et GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

    // Configurer PA9 (TX) en mode alternatif push-pull
    GPIOA->CRH &= ~(0xF << (1 * 4));
    GPIOA->CRH |= (0xB << (1* 4));

    // Configurer PA10 (RX) en entrée flottante
    GPIOA->CRH &= ~(0xF << (2 * 4));
    GPIOA->CRH |= (0x4 << (2 * 4));

    // Configurer USART1 : Baud rate = 9600, 8 bits, 1 stop, pas de parité
    USART1->BRR = 0x09C4; // Baud rate = 9600, clock = 24 MHz
    USART1->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; // RX, TX et USART activé

}

void UART_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE)); // Attendre que le buffer soit vide
    USART1->DR = c;
}

char UART_ReceiveChar(void) {
    while (!(USART1->SR & USART_SR_RXNE)); // Attendre un octet reçu
    return USART1->DR;
}

void UART_SendString(const char *str) {
    while (*str) {            // Tant que la chaîne n'est pas terminée
        UART_SendChar(*str);   // Envoyer un caractère de la chaîne
        str++;                 // Passer au caractère suivant
    }
}

void UART_Angle_Message(float angle){
	if((angle >=330.0 || angle <=30.0) && precedent !=0){
		UART_SendString("Le voilier navigue en vent debout\n");
		precedent =0;
	} else if (((angle >= 30.0 && angle <= 45.0)||(angle>=315.0 && angle <= 330.0))&& precedent !=1) {
			UART_SendString("Le voilier navigue au pres\n");
		precedent =1;
	} else if (((angle >= 45.0 && angle <= 70.0)||(angle>=290.0 && angle <= 315.0)) && precedent !=2) {
			UART_SendString("Le voilier navigue en bon plein\n");
		precedent = 2;
	} else if (((angle >= 70.0 && angle < 90.0)||(angle>270.0 && angle <= 290.0))&& precedent !=3) {
			UART_SendString("Le voilier navigue en petite largue\n");
		precedent =3;
	}else if ((angle == 90.0 || angle == 270.0) && precedent !=4){
		UART_SendString("Le voilier navigue en travers\n");
		precedent =4;
	} else if (((angle >90.0 && angle <= 110.0)||(angle>250.0 && angle <= 270.0)) && precedent !=5) {
			UART_SendString("Le voilier navigue en largue\n");
		precedent =5;
	} else if (((angle >=110.0 && angle <= 145.0)||(angle>=215.0 && angle <= 250.0)) && precedent !=6) {
			UART_SendString("Le voilier navigue en grande largue\n");
		precedent=6;
	} else if ((angle >= 145.0 && angle <= 215.0) && precedent !=7) {
			UART_SendString("Le voilier navigue en vent arriere\n");
		precedent =7;
	}
}