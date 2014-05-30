/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "colors.h"

void pintar( unsigned char* g){
	int c;
	c = VIDEO_FILS * VIDEO_COLS;
	while ( c >= 0){
		*g = C_BG_GREEN;
		g += 4;
		c--;
	}
	
	
}



