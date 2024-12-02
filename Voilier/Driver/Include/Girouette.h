#ifndef GIROUETTE_H
#define GIROUETTE_H

#include "stm32f10x.h" // Remplacez par la bibliothèque STM32 que vous utilisez

// Fonction pour configurer le timer et les GPIO pour l'encodeur
void Girouette_Config(void);

// Fonction pour lire la position angulaire de l'encodeur
float Girouette_Read(void);

//fonction quand I passe à 1
void EXTI2_IRQHandler (void);

#endif // GIROUETTE_H
