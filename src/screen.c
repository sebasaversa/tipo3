/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "colors.h"
/*
void pintar(){
	
	memoria_video* vd = (memoria_video*) (0xb8000);

	
	int f = 0;
	int c;
	while(f < 50 ){
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
*/
void pintarTablero(){

	memoria_video* vd = (memoria_video*) (0xb8000);

	
	int f = 0;
	int c;
	while(f < VIDEO_FILS ){
		c = 0;
		while (c < VIDEO_COLS){
			if (c <= 50){
				vd->fondo = C_FG_GREEN;
			}
			if (c >= 52)
			{
				if(f == 0 || f == 39)
				{
				vd->fondo = C_FG_RED;
				}
				if( 0 < f && f < 39)
				{
					vd->fondo = C_FG_LIGHT_GREY;
				}
				
			}
			if ( (52 < c && c < 70) && f >= 47)
			{
				vd->fondo = C_FG_LIGHT_GREY;
			}
			
			vd->ascii = (unsigned char) 0x0;
			vd++;	
			c++;
		}
		f++;
	}
}


void imprimir(char* m, memoria_video* vd){
	
	memoria_video* vdAux = vd;
	while (*m != '\0'){
		//vdAux->fondo = C_FG_GREEN;
		vdAux->ascii = *m;
		m++;
		vdAux++;
	}
}

void mostrar_int(int error){
	memoria_video* vd = (memoria_video*) (0xb8000);
	switch ( error)
	{
		case 0:
			imprimir("Divide Error Exception (#DE)", vd);
			break;
		case 1:
			imprimir("Debug Exception (#DB)", vd);
			break;
		case 2:
			imprimir("NMI Interrupt", vd);
			break;
		case 3:
			imprimir("Breakpoint Exception (#BP)", vd);
			break;
		case 4:
			imprimir("Overflow Exception (#OF)", vd);
			break;
		case 5:
			imprimir("BOUND Range Exceeded Exception (#BR)", vd);
			break;
		case 6:
			imprimir("Invalid Opcode Exception (#UD)", vd);
			break;
		case 7:
			imprimir("Device Not Available Exception (#NM)", vd);
			break;
		case 8:
			imprimir("Double Fault Exception (#DF)", vd);
			break;
		case 9:
			imprimir("Coprocessor Segment Overrun", vd);
			break;
		case 10:
			imprimir("Invalid TSS Exception (#TS)", vd);
			break;
		case 11:
			imprimir("Segment Not Present (#NP)", vd);
			break;
		case 12:
			imprimir("Stack Fault Exception (#SS)", vd);
			break;
		case 13:
			imprimir("General Protection Exception (#GP)", vd);
			break;
		case 14:
			imprimir("Page-Fault Exception (#PF)", vd);
			break;
		case 15:
			imprimir("", vd);
			break;
		case 16:
			imprimir("x87 FPU Floating-Point Error (#MF)", vd);
			break;
		case 17:
			imprimir("Alignment Check Exception (#AC)", vd);
			break;
		case 18:
			imprimir("Machine-Check Exception (#MC)", vd);
			break;
		case 19:
			imprimir("SIMD Floating-Point Exception (#XM)", vd);
			break;
	}
}


void mostrar_num(int teclado){
	memoria_video* vd = (memoria_video*) (0xb8000);
	vd += 79;
	//vd->fondo = switch ()
	switch (teclado)
	{
		case 2:	imprimir("1", vd);
				break;
		case 3: imprimir("2", vd);
				break;
		case 4: imprimir("3", vd);
				break;
		case 5:	imprimir("4", vd);
				break;
		case 6: imprimir("5", vd);
				break;
		case 7: imprimir("6", vd);
				break;
		case 8:	imprimir("7", vd);
				break;
		case 9: imprimir("8", vd);
				break;
		case 10: imprimir("9", vd);
				break;
	}
}
