/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "colors.h"

void pintar(){
	
	unsigned char* v = (unsigned char*) mem_vid;
	
	int f = 0;
	int c;
	while(f < VIDEO_FILS ){
		c = 0;
		while (c < VIDEO_COLS){
			if (c <= 50){
				*v = C_BG_GREEN;
				}
			v++;
			*v = ' ';
			v++;
			
			c++;
		}
		f++;
	}
}


