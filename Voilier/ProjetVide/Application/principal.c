#include "stm32f10x.h"
#include "Girouette.h"
#include "Voile.h"
#include "Plateau.h"
#include "UART.h"
#include <stdlib.h>
#include "Batterie.h"

float angle = 0;
float teta = 0;
float vitesse = 0.0;
uint8_t sens;

int main(void) {
	Girouette_Config();
	Voile_config();
	Plateau_config();
	UART_config();
	ADC_Config();
	
	while (1){
		angle = Girouette_Read();
		UART_Angle_Message(angle);
		Batterie_write(Batterie_read());
		
		teta = Voile_Affine(angle);
		Voile_Set_teta(angle);
		
		int8_t commande = (int8_t) UART_ReceiveChar();
		//commande = -1;
		
		sens = (uint8_t) 0;
		if(commande<0){
			sens =(uint8_t) 1;
		}
		
		Plateau_Sens(sens);
		vitesse = Plateau_PWM(abs(commande));
	
		//Plateau_Set_Governail(commande);
		commande =0;

		

	}
}

