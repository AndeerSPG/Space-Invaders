/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"

int ESTADO;
int X=127;//Posicion X de la nave
int Y=165;//Posicion Y del disparo



void moverderecha(){
	if(X<239)
	{	X+= 10;
		MostrarNave(6, X, 165);
				
	}

}
void moverizquierda(){
	if(X>0)
	{
		X-= 10;
		MostrarNave(6, X, 165);
	}

}

void RutAtencionTeclado()
{	
	
	
		if (TeclaPulsada() == DERECHA)
		{	moverderecha();
			
		}
		if (TeclaPulsada() == IZQUIERDA)
		{	moverizquierda();
		}
		
	
			


						
}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	if (ESTADO == JUGANDO){
	tick++;
	if (tick==7)
	{
	seg++;
	iprintf("\x1b[1;1HTimer: %d", seg );
	
	tick=0;
	}
	if(seg == 10 )//Cuando el timer llega a 10  se borra la pantala superior, se reinician "seg" y la posicion X de la nave y se cambia al
	{		    // estado a FIN.
		iprintf("\x1b[1;1H                               ");
		consoleClear();
		ESTADO = FIN;
		X=127;
		seg=0;
	}
	}

}


void EstablecerVectorInt()
{   
    irqSet(IRQ_KEYS, RutAtencionTeclado);
    irqSet(IRQ_TIMER0, RutAtencionTempo);
    
}



