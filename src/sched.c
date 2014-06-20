/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

unsigned int actual = 0;
unsigned int tss_busy = 15;
unsigned int tss_free = 16;
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
	gdt[15].base_0_15 = ((unsigned int)tss_pointer_busy << 16) >> 16;
	gdt[15].base_23_16 = (unsigned int) tss_pointer_busy >> 16;
	//15->base_31_24 = ;
	unsigned int aux = (unsigned int) (0x68 - 0x1); // 0x68 == 104 bytes
	gdt[15].limit_0_15 = (aux << 16) >> 16;
	gdt[15].limit_16_19 = aux >> 16;

	gdt[16].base_0_15 = ((unsigned int)tss_pointer_free << 16) >> 16;
	gdt[16].base_23_16 = (unsigned int)tss_pointer_free >> 16;
	//16->base_31_24 = ;
	aux = (unsigned int) (0x68 - 0x1); // 0x68 == 104 bytes
	gdt[16].limit_0_15 = (aux << 16) >> 16;
	gdt[16].limit_16_19 = aux >> 16;
}

void sched_inicializar_struct_tareas(){
/*typedef struct str_nodo{
	nodo *sig;		// para las 8 tareas
	nodo *ant;		// para las 8 tareas
	tss* tarea;
	int tarea;
} __attribute__((__packed__, aligned (8))) nodo;*/
	int i;
	nodo* array_tareas_temp = array_tareas;
	for (i = 0; i < 7 ; i++)
	{
		array_tareas_temp->tarea = tss_tanques[i];
		nodo* algo;
		array_tareas_temp->sig = algo;
		array_tareas_temp = array_tareas->sig;
	}
	array_tareas_temp->sig = array_tareas;


}
void sched_inicializar(){
	sched_inicializar_gdt();
	sched_inicializar_struct_tareas();
}

unsigned short sched_proximo_indice() {
	if (tss_busy == 15){
		tss_busy = 16;
		tss_free = 15;}
	else{
		tss_busy = 15;
		tss_free = 16;}
	
	//ya se a que tarea guardarle el contexto
	sched_cargar_sig_tarea(nodo->sig, gdt[tss_free]);
	sched_guardar_contexto(tss_pointer_busy, array_tareas->tarea);
	if (array_tareas->sig != 0)
		actual = array_tareas->sig->tarea;
	else
		actual = 8;

	return 0;
}
