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
		}
		case 1:
		{
			imprimir("Debug Exception (#DB)");
		}
		case 2:
		{
			imprimir("NMI Interrupt");
		}
		case 3:
		{
			imprimir("Breakpoint Exception (#BP)");
		}
		case 4:
		{
			imprimir("Overflow Exception (#OF)");
		}
		case 5:
		{
			imprimir("BOUND Range Exceeded Exception (#BR)");
		}
		case 6:
		{
			imprimir("Invalid Opcode Exception (#UD)");
		}
		case 7:
		{
			imprimir("Device Not Available Exception (#NM)");
		}
		case 8:
		{
			imprimir("Double Fault Exception (#DF)");
		}
		case 9:
		{
			imprimir("Coprocessor Segment Overrun");
		}
		case 10:
		{
			imprimir("Invalid TSS Exception (#TS)");
		}
		case 11:
		{
			imprimir("Segment Not Present (#NP)");
		}
		case 12:
		{
			imprimir("Stack Fault Exception (#SS)");
		}
		case 13:
		{
			imprimir("General Protection Exception (#GP)");
		}
		case 14:
		{
			imprimir("Page-Fault Exception (#PF)");
		}
		case 15:
		{
			imprimir("");
		}
		case 16:
		{
			imprimir("x87 FPU Floating-Point Error (#MF)");
		}
		case 17:
		{
			imprimir("Alignment Check Exception (#AC)");
		}
		case 18:
		{
			imprimir("Machine-Check Exception (#MC)");
		}
		case 19:
		{
			imprimir("SIMD Floating-Point Exception (#XM)");
		}
	}
}

