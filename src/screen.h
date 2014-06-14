/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50	
#define VIDEO_COLS 80	
#define mem_vid 0xb8000

typedef struct str_memoria_video {
	unsigned char   ascii:8;
	unsigned char   caracter:3;
	unsigned char   brillante:1;
	unsigned char   fondo:3;
    unsigned char   blink:1; 
} __attribute__((__packed__)) memoria_video;


void pintar();
void pintarTablero();
void mostrar_int(int i);
void mostrar_num(int n);

#endif  /* !__SCREEN_H__ */
