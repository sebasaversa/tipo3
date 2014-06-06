/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "colors.h"

void pintar(){
	
	memoria_video* vd = (memoria_video*) (0xb8000);

	
	//unsigned char* v = (unsigned char*) mem_vid;
	
	int f = 0;
	int c;
	while(f < VIDEO_FILS ){
		c = 0;
		while (c < VIDEO_COLS){
			if (c <= 50){
				vd->fondo = C_FG_GREEN;
			}
			vd->ascii = (unsigned char) 0x0;
			vd++;	
			c++;
		}
		f++;
	}
}

void mostrar_int(int error){
	//printf("¡Hola, mundo!\n");
}

