/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
//#include "tss.h"
short actual = 0;
unsigned int tss_busy = 15;
unsigned int tss_free = 16;
tss* tss_pointer_busy;
tss* tss_pointer_anterior;
nodo* array_tareas;
selector_offset sel_tarea;

/// INVARIANTE array_tareas APUNTA SIEMPRE AL CONTEXTO DE LA TAREA ACTUAL EN NUESTRO STRUCT ///

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

void sched_inicializar_gdt(){
	gdt[15].base_0_15 = ((unsigned int) tss_pointer_busy << 16) >> 16;
	gdt[15].base_23_16 = (unsigned int) tss_pointer_busy >> 16;
	//15->base_31_24 = ;
	unsigned int aux = (unsigned int) (0x68 - 0x1); // 0x68 == 104 bytes
	gdt[15].limit_0_15 = (aux << 16) >> 16;
	gdt[15].limit_16_19 = aux >> 16;

	gdt[16].base_0_15 = ((unsigned int) tss_pointer_anterior << 16) >> 16;
	gdt[16].base_23_16 = (unsigned int) tss_pointer_anterior >> 16;
	//16->base_31_24 = ;
	aux = (unsigned int) (0x68 - 0x1); // 0x68 == 104 bytes
	gdt[16].limit_0_15 = (aux << 16) >> 16;
	gdt[16].limit_16_19 = aux >> 16;
}


void sched_inicializar(){
	sched_inicializar_gdt();
}

void tss_copy(tss* tss_pointer_anterior, tss* contexto_tarea_previa){
   contexto_tarea_previa = tss_pointer_anterior;
}

tss* buscar_contexto_tarea(short anterior){
	nodo* res = array_tareas;
	while (res->num_tarea != anterior){
		res = res->sig;
	}
	return res->tarea;
}

void sched_guardar_contexto(tss* ts, tss* ts2){
	tss* contexto_tarea_previa = buscar_contexto_tarea(array_tareas->ant->num_tarea);	
	tss_copy(tss_pointer_anterior ,contexto_tarea_previa);
} 


void sched_cargar_sig_tarea(){
	tss_pointer_anterior = buscar_contexto_tarea(array_tareas->sig->num_tarea);	// 1er paso
	tss* tss_aux = tss_pointer_anterior; 
	tss_pointer_anterior = tss_pointer_busy; 
	tss_pointer_busy = tss_aux;
	actual = array_tareas->sig->num_tarea;
	// HACER JMP FAR EN ASM A LA NUEVA TAREA
//	asm("jmp far %(tss_free)*(0x8)");

	sel_tarea.offset = 0;
	sel_tarea.selector = tss_free * 0x8;	
//	__asm __volatile("jmp far %%sel_tarea" : :);
}

//b)
unsigned short sched_proximo_indice() {
	if (tss_busy == 15){
		tss_busy = 16;
		tss_free = 15;}
	else{
		tss_busy = 15;
		tss_free = 16;}
	//ya se a que tarea guardarle el contexto
	sched_guardar_contexto(tss_pointer_anterior, array_tareas->tarea);
	sched_cargar_sig_tarea(); //cambie NODO Por ARRAY_TAREAS
	if (array_tareas->sig != 0)
		actual = array_tareas->sig->num_tarea; //AGREGUE "(unsigned int)" hay que chequear esto porque tarea es una tss
	else
		actual = 8;

	return 0; 
}
