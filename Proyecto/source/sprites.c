/*---------------------------------------------------------------------------------
Código desarrollado basado en el ejemplo "Simple sprite demo" de dovoto y en otro de Jaeden Amero.
---------------------------------------------------------------------------------*/

#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

#include "sprites.h"
#include "definiciones.h"

u16* gfxalien;
u16* gfxnave;
u16* gfxtiro;


/* Reservar memoria para cada sprite que se quiera mostrar en pantalla */
void memoriaReserva()
{
	/* Por cada sprite que se quiera incluir en la pantalla principal hay que hacer algo equivalente a lo que sigue */
	gfxalien= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxnave= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxtiro= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

/* A cada uno de los 256 valores que puede tomar un pixel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros. 
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES */
void EstablecerPaletaPrincipal() {

	SPRITE_PALETTE[	1	] = RGB15(	31	,	0	,	0	); //
SPRITE_PALETTE[	2	] = RGB15(	31	,	31	,	0	); //
SPRITE_PALETTE[	3	] = RGB15(	31	,	31	,	31	); //
SPRITE_PALETTE[	4	] = RGB15(	0	,	31	,	0	); //
SPRITE_PALETTE[	5	] = RGB15(	0	,	0	,	31	); //
SPRITE_PALETTE[	6	] = RGB15(	0	,	0	,	0	); //
SPRITE_PALETTE[	7	] = RGB15(	0	,	31	,	31	); //
SPRITE_PALETTE[	8	] = RGB15(	31	,	0	,	31	); //
SPRITE_PALETTE[	9	] = RGB15(	16	,	16	,	16	); //
SPRITE_PALETTE[	10	] = RGB15(	25	,	25	,	25	); //
SPRITE_PALETTE[	11	] = RGB15(	8	,	8	,	8	); //
SPRITE_PALETTE[	12	] = RGB15(	31	,	19	,	0	); //
SPRITE_PALETTE[	13	] = RGB15(	19	,	0	,	4	); //
SPRITE_PALETTE[	14	] = RGB15(	25	,	0	,	0	); //
SPRITE_PALETTE[	15	] = RGB15(	16	,	0	,	16	); //
SPRITE_PALETTE[	16	] = RGB15(	25	,	19	,	31	); //
SPRITE_PALETTE[	17	] = RGB15(	31	,	19	,	25	); //
SPRITE_PALETTE[	18	] = RGB15(	23	,	21	,	21	); //
SPRITE_PALETTE[	19	] = RGB15(	0	,	0	,	16	); //
SPRITE_PALETTE[	20	] = RGB15(	0	,	16	,	16	); //
SPRITE_PALETTE[	21	] = RGB15(	0	,	12	,	0	); //
SPRITE_PALETTE[	22	] = RGB15(	16	,	16	,	0	); //
SPRITE_PALETTE[	23	] = RGB15(	19	,	31	,	19	); //
SPRITE_PALETTE[	24	] = RGB15(	31	,	31	,	19	); //

}

/* definición de un sprite de 16x16 píxeles para dibujar un rombo */
/* Por la forma que tienen de trabajar los bancos de memoria, la imagen del sprite se divide en bloques de 8x8 píxeles. Los primeros 64 (8x8) píxeles que indicamos
aparecerán en el cuadrante superior izquierdo de la imagen del sprite, los siguientes 64 en el cuadrante superior derecho, los siguientes en el cuadrante inferior izquierdo y los
últimos en el cuadrante inferior derecho */

u8 alien[256] = 
{
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 23, 0, 0,
	0, 0, 0, 0, 23, 0, 0, 0, 
	0, 0, 0, 0, 0, 23, 23, 23, 
	0, 0, 0, 0, 4, 4, 4, 4, 
	0, 0, 0, 0, 4, 3, 6, 4, 
	0, 0, 0, 0, 4, 6, 6, 4, 
	0, 0, 0, 0, 4, 4, 4, 4, 
 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 23, 0, 0, 0, 0, 0, 
	0, 0, 0, 23, 0, 0, 0, 0, 
	23, 23, 23, 0, 0, 0, 0, 0, 
	4, 4, 4, 4, 0, 0, 0, 0, 
	4, 3, 6, 4, 0, 0, 0, 0, 
	4, 6, 6, 4, 0, 0, 0, 0, 
	4, 4, 4, 4, 0, 0, 0, 0, 

	0, 0, 0, 0, 0, 0, 0, 4, 
	0, 0, 0, 0, 0, 0, 4, 4, 
	0, 0, 0, 0, 0, 4, 0, 4, 
	0, 0, 0, 0, 4, 0, 0, 4, 
	0, 0, 0, 0, 0, 0, 0, 4, 
	0, 0, 0, 0, 0, 0, 4, 4, 
	0, 0, 0, 0, 0, 4, 4, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 

	4, 0, 0, 0, 0, 0, 0, 0, 
	4, 4, 0, 0, 0, 0, 0, 0, 
	4, 0, 4, 0, 0, 0, 0, 0, 
	4, 0, 0, 4, 0, 0, 0, 0, 
	4, 0, 0, 0, 0, 0, 0, 0, 
	4, 4, 0, 0, 0, 0, 0, 0, 
	0, 4, 4, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0,
};

u8 nave[256] = 
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 2, 0, 1,
	0, 0, 0, 0, 0, 12, 0, 1,
	0, 0, 0, 0, 0, 1, 1, 1,	
 
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	2, 0, 0, 0, 0, 0, 0, 0,
	12, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 2, 0, 0, 0, 0,
	1, 1, 0, 12, 0, 0, 0, 0,
	18, 1, 1, 1, 0, 0, 0, 0,

	0, 0, 0, 2, 0, 1, 1, 18,
	0, 0, 0, 12, 0, 1, 1, 18,
	0, 0, 0, 1, 1, 1, 1, 1,
	0, 0, 0, 1, 13, 0, 13, 13,
	0, 0, 0, 13, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,

	18, 18, 1, 1, 0, 2, 0, 0,
	1, 18, 1, 1, 0, 12, 0, 0,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 13, 13, 0, 13, 1, 0, 0,
	13, 0, 0, 0, 0, 13, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

u8 tiro[256] =
{ 

	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 0, 0, 0, 0, 1, 12, 
	0, 0, 0, 0, 0, 0, 1, 2, 

	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 0, 

	0, 0, 0, 0, 0, 0, 1, 12, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 

	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0,
};

/* Carga en memoria cada uno de los sprites que hemos dibujado */

void GuardarSpritesMemoria(){ 
	
int i;
	//sprite de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxalien[i] = alien[i*2] | (alien[(i*2)+1]<<8);				
	}
	//sprite de 32x32
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxnave[i] = nave[i*2] | (nave[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxtiro[i] = tiro[i*2] | (tiro[(i*2)+1]<<8);				
	}
}

/* Esta función dibuja un rombo en la posición x-y de pantalla. A cada rombo que se quiera mostrar en pantalla se le debe asignar un índice distinto, un valor entre 0 y 126 */

void MostrarAlien(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxalien,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

void MostrarNave(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxnave,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}
void MostrarTiro(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxtiro,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}
/* Esta función borra de la pantalla el Rombo con el índice indicado */
void BorrarAlien(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxalien,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void BorrarNave(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxnave,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}
void BorrarTiro(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixel location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxtiro,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}
