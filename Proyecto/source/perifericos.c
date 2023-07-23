/*-------------------------------------
perifericos.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"


int tecla; //variable para guardar la tecla pulsada



int TeclaDetectada() 
{
	//Devuelve TRUE si detecta que se ha pulsado alguna tecla.
	if ((~TECLAS_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int TeclaPulsada() 
{
if ((~TECLAS_DAT & 0x0001)!=0)       return (0);
else if ((~TECLAS_DAT & 0x0002)!=0)return (1);
else if ((~TECLAS_DAT & 0x0004)!=0) return (2);
else if ((~TECLAS_DAT & 0x0008)!=0)return (3);
else if((~TECLAS_DAT & 0x0010)!=0)  return (4);
else if ((~TECLAS_DAT & 0x0020)!=0) return (5);
else if ((~TECLAS_DAT & 0x0040)!=0) return (6) ;
else if ((~TECLAS_DAT & 0x0080)!=0) return (7);
else if ((~TECLAS_DAT & 0x0100)!=0) return (8);
else if ((~TECLAS_DAT & 0x0200)!=0) return (9);

	//Devuelve el código de la tecla pulsada utilizando para ello las constantes definidas en 
	//definiciones.h:  A=0;B=1;SELECT=2;START=3;IZQUIERDA=4;DERECHA=5;
	//ARRIBA=6;ABAJO=7;R=8;L=9;

}

void ConfigurarTeclado(int Conf_Tec)
{
        
	TECLAS_CNT= TECLAS_CNT | Conf_Tec ;
	
}

void ConfigurarTemporizador(int Latch, int Conf_Tempo)
{	
	TIMER0_DAT = Latch;
	TIMER0_CNT= TIMER0_CNT | Conf_Tempo;

	
}

void HabilitarIntTeclado()
{
	//Habilitar las interrupciones del teclado
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;
        IE= IE | 0x00001000; 
	
	IME=1;
}

void InhibirIntTeclado()
{

	//Deshabilitar las interrupciones del teclado
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 

	IME=0;
	IE= IE & 0xFFFFEFFF;

	IME=1;
}  

void HabilitarIntTempo()
{


	//Habilitar las interrupciones del temporizador (timer0)
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;
	IE= IE | 0x00000008; 
	
	IME=1;
}

void InhibirIntTempo()
{

	//Deshabilitar las interrupciones del temporizado (timer0)
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;
	
        IE= IE & 0xFFFFFFF7; 
	
	IME=1;

}

void PonerEnMarchaTempo()
{
	TIMER0_CNT = TIMER0_CNT | 0x0080;//ESCRIBID AQUÍ VUESTRO CÓDIGO
	
}

void PararTempo()
{
	TIMER0_CNT = TIMER0_CNT & 0xFF7F;//ESCRIBID AQUÍ VUESTRO CÓDIGO
	
}
