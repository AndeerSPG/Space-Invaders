
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación. */

#include "fondos.h"
#include "graficos.h"
#include "Start.h"
#include "Espacio.h"
#include "Over.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria.*/
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

void visualizarEspacio() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     EspacioBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     EspacioBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarStart() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     StartBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     StartBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}
void visualizarOver() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     OverBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     OverBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

