/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/


#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"

//Definicion de variables


bool valorasignado=false;//Booleano para verificar si a X2 se le ha asignado ya el valor de X.
int X2;//Posicion X del disparo

void disparar(){
	MostrarTiro(7, X, Y);
	if (valorasignado==false)//Si no se le ha asignado el valor de X a X2 se le asigna en el momento en el que se dispara, así el disparo seguira recto hacia
	{			//arriba en la posicion X en la que se encontraba la nave al pulsar A y la nave se podra mover sin alterar la posicion del disparo.
		X2=X;
		valorasignado=true;
	}
	if(Y >16)
	{
		Y =16;
		MostrarTiro(7, X2, Y);
	}
		
	if( Y==16) // Cuando el disparo llega a la altura maxima primero se verifica si esta en los rangos de X de los aliens y despues se comprueba individualmente
		   // a que alien corresponde. Después de comprobar si se le ha dado a algun alien(independientemente de si se le ha dado o no) se borra el disparo y se 			   //reinicializa su posicion y la variable "pulsada" que verifica si hemos disparado o no.
	{
		if((X2>16 && X2<36) || (X2>76 && X2<96) || (X2>126 && X2<146) || (X2>166 && X2<186) || (X2>216 && X2<236))
		{
			if(X2>16 && X2<36)
			{
				BorrarAlien(1,20,16);
			}
			if(X2>76 && X2<96)
			{
				BorrarAlien(2,80,16);
			}	
			if(X2>126 && X2<146)
			{
				BorrarAlien(3,130,16);
			}
			if(X2>166 && X2<186)
			{
				BorrarAlien(4,170,16);
			}
			if(X2>216 && X2<236)
			{
				BorrarAlien(5,220,16);
			}
		}
		BorrarTiro(7, X2,Y);
		Y = 165;
		valorasignado=false;
			
					
	}


}

void IniciarAliens()
{
		MostrarAlien(1,20,16);
		MostrarAlien(2,80,16);
		MostrarAlien(3, 130, 16);
		MostrarAlien(4, 170, 16);
		MostrarAlien(5, 220, 16);
}
void visualizarpantalla2() //El estado pasa a jugando y se muestran todos los sprites y el fondo del espacio.
{
	ESTADO=JUGANDO;
	visualizarEspacio();
	IniciarAliens();
	MostrarNave(6, 127, 165);
	
}
void visualizarpantalla3() //Se borran todos los Sprites y se visualiza el Game Over
{
	BorrarNave(6, X, 165);
	BorrarAlien(1,20,16);
	BorrarAlien(2,80,16);
	BorrarAlien(3, 130, 16);
	BorrarAlien(4, 170, 16);
	BorrarAlien(5, 220, 16);
	BorrarTiro(7, X,Y);
	visualizarOver();
	iprintf("\x1b[15;1HToca la pantalla tactil");
	iprintf("\x1b[16;1Hpara reiniciar");

}


		
int TactilTocada() //Verifica si se ha tocado la pantalla tactil
{
touchPosition pos_pantalla;
 touchRead(&pos_pantalla);
 return !(pos_pantalla.px==0 && pos_pantalla.py==0);
} 
void juego()
{	EstablecerVectorInt();
	ConfigurarTeclado(0x4030);
	ConfigurarTemporizador(46811, 0x0042);
	HabilitarIntTempo();
	HabilitarIntTeclado();
	PonerEnMarchaTempo();
	
	
	
	
	ESTADO = INICIO;
	
	while(1)
	{
        	if (ESTADO == INICIO)
        	{	
			iprintf("\x1b[22;1HEl juego acabara cuando el");
			iprintf("\x1b[23;1H timer llegue a 10");
            		visualizarStart();
			if(TeclaDetectada())
			{
            			if (TeclaPulsada()==START)
            			{
					consoleClear();
               				visualizarpantalla2();
            			}
			}	
		}
		if(ESTADO == JUGANDO)
		{	
			if(TeclaDetectada() )
			{
				if(TeclaPulsada() == A)
				{	      
					disparar();
				}
			}
			
			

		}
		if(ESTADO == FIN)
		{
			visualizarpantalla3();
			if(TactilTocada() == 1)//Si se ha tocado la pantalla tactil cuando el estado es fin se reinicia el juego
			{		
				consoleClear();		
				ESTADO = INICIO;
			}
		}
	}
	PararTempo();
	InhibirIntTeclado();
}



