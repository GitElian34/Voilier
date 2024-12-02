#include "Batterie.h"
#include "core_cm3.h"
#include "stdio.h"
#include "UART.h"

#define ADC_CHANNEL_BATTERY 0  // Exemple : ADC sur le canal 0 (connecté au pont diviseur)
#define ADC_MAX_VALUE 4095     // Résolution 12 bits : 0 - 4095
#define ADC_REFERENCE_VOLTAGE 3.3 // Tension de référence (en volts)
#define DIVIDER_RATIO 13       // Facteur du pont diviseur

int batterie_a=-1;

void ADC_Config(void) {
    // Activer l'horloge pour l'ADC et le GPIO correspondant
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  // Activer l'horloge ADC1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Activer l'horloge GPIOA

    // Configurer PA6 (canal ADC6) comme entrée analogique
    GPIOA->CRL &= ~(0xF << (4 * 6)); // Effacer la configuration des bits pour PA6
    // Aucun autre réglage nécessaire : mode analogique activé par défaut avec cette configuration

    // Configuration de l'ADC
    ADC1->CR2 |= ADC_CR2_CAL; // Lancer la calibration de l'ADC 

    ADC1->CR2 |= ADC_CR2_ADON; // Activer l'ADC
    ADC1->SQR1 &= ~ADC_SQR1_L; // Conversion pour 1 canal
    ADC1->SQR3 = 6; // Sélectionner le canal ADC6 (PA6)
}

uint16_t ADC_Read(void) {
    ADC1->CR2 |= ADC_CR2_ADON; // Lancer la conversion
    while (!(ADC1->SR & ADC_SR_EOC)); // Attendre la fin de la conversion
    return ADC1->DR; // Lire la valeur convertie
}

int Batterie_read(void) {
    uint16_t adc_value = ADC_Read(); // Lire la valeur brute de l'ADC
    float adc_voltage = (adc_value / (float)ADC_MAX_VALUE) * ADC_REFERENCE_VOLTAGE; // Convertir en tension
    float battery_voltage = adc_voltage * DIVIDER_RATIO; // Calculer la tension réelle
    return (int)battery_voltage;
}

void Batterie_write(int batterie){
		char buffer[50]; // Tampon pour contenir la chaîne formatée
    sprintf(buffer, "Batterie : %d\n", batterie); // Formater la chaîne
	if(batterie!= batterie_a){
    UART_SendString(buffer); // Envoyer la chaîne via UART
		batterie_a=batterie;
	}
}