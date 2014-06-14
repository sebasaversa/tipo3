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

	
	int f = 0;
	int c;
	while(f < 20 ){
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


void imprimir(char* m){
	
	memoria_video* vd = (memoria_video*) (0xb8000);
	while (*m != '\0'){
		vd->fondo = C_FG_GREEN;
		vd->ascii = *m;
		m++;
		vd++;
	
	}
	
}

void mostrar_int(int error){
	
	switch ( error)
	{
		case 0:
		{
			imprimir("Divide Error Exception (#DE)");
			break;
		}
		case 1:
		{
			imprimir("Debug Exception (#DB)");
			break;
		}
		case 2:
		{
			imprimir("NMI Interrupt");
			break;
		}
		case 3:
		{
			imprimir("Breakpoint Exception (#BP)");
			break;
		}
		case 4:
		{
			imprimir("Overflow Exception (#OF)");
			break;
		}
		case 5:
		{
			imprimir("BOUND Range Exceeded Exception (#BR)");
			break;
		}
		case 6:
		{
			imprimir("Invalid Opcode Exception (#UD)");
			break;
		}
		case 7:
		{
			imprimir("Device Not Available Exception (#NM)");
			break;
		}
		case 8:
		{
			imprimir("Double Fault Exception (#DF)");
			break;
		}
		case 9:
		{
			imprimir("Coprocessor Segment Overrun");
			break;
		}
		case 10:
		{
			imprimir("Invalid TSS Exception (#TS)");
			break;
		}
		case 11:
		{
			imprimir("Segment Not Present (#NP)");
			break;
		}
		case 12:
		{
			imprimir("Stack Fault Exception (#SS)");
			break;
		}
		case 13:
		{
			imprimir("General Protection Exception (#GP)");
			break;
		}
		case 14:
		{
			imprimir("Page-Fault Exception (#PF)");
			break;
		}
		case 15:
		{
			imprimir("");
			break;
		}
		case 16:
		{
			imprimir("x87 FPU Floating-Point Error (#MF)");
			break;
		}
		case 17:
		{
			imprimir("Alignment Check Exception (#AC)");
			break;
		}
		case 18:
		{
			imprimir("Machine-Check Exception (#MC)");
			break;
		}
		case 19:
		{
			imprimir("SIMD Floating-Point Exception (#XM)");
			break;
		}
	}
}

