/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

unsigned int actual = 0;
unsigned int tssi = 15;
	/* code */
	
	/**
	1) guardar el contexto de la tarea actual
	2) escribir en uno de los registros de la gdt la proxima tss
	3) cargar la tss a travez de la gdt
	*/
	/** 1 */
	/**
		Cargar la tarea vieja
		mov ax, <indice>
		ltr ax
		Cargar la nueva tarea
		jmp <sel.tarea_idle>:0

	*/
	/**
	actual++;
	if(actual >= CANT_TANQUES)
		actual = 0;
	*/
	/** 3 */

unsigned short sched_proximo_indice() {
	if (tssi == 15)
		tssi = 16;
	else
		tssi = 15;
	return 0;
}
