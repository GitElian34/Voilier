#include "stm32f10x.h"
#include "adc.h"

int main(void) {
    ADC_Init(); // Initialiser l'ADC

    // Lire une seule valeur de l'ADC

    // Ici, vous pouvez v�rifier la valeur adcValue, par exemple, en utilisant un d�bogueur.
			    uint32_t adcValue=0;

    while (1) {
        // Pas de boucle infinie ici, juste une lecture unique
adcValue = ADC_Read(0);
    }
}
