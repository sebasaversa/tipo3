/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "defines.h"

unsigned int tss_busy = 15;
unsigned int tss_free = 16;
unsigned int TAREA_ACTUAL;
unsigned int TAREA_ANTERIOR;
//tss* tss_pointer_busy;
//tss* tss_pointer_anterior;
nodo* array_tareas;

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

	gdt[15].base_0_15 = (unsigned int)&tss_next_1;
	gdt[15].base_23_16 = ((unsigned int)&tss_next_1) >>16; 
	gdt[15].base_31_24 = ((unsigned int)&tss_next_1) >>24; 
	
	gdt[16].base_0_15 = (unsigned int)&tss_next_2;
	gdt[16].base_23_16 = ((unsigned int)&tss_next_2) >>16; 
	gdt[16].base_31_24 = ((unsigned int)&tss_next_2) >>24;
/*	gdt[15].base_0_15 = ((unsigned int) tss_pointer_busy << 16) >> 16;
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
*/}


void sched_inicializar(){
	sched_inicializar_gdt();
}

void tss_copy(tss* dst, tss* src){
   dst = src;
}

tss* buscar_contexto_tarea(short task_actual){
	nodo* res = array_tareas;
	while (res->num_tarea != task_actual){
		res = res->sig;
	}
	return res->sig->tarea;

}
tss* buscar_contexto_tarea_ant(short task_ant){
	nodo* res = array_tareas;
	while (res->num_tarea != task_ant){
		res = res->sig;
	}
	return res->tarea;

}

void sched_guardar_contexto(unsigned int free_tss_gdt_index){

//(1) cual tengo que guardar, la free o la busy... no! la free! siempre
//(2) donde tengo que guardar, en que cacho de memoria tengo que salvar lo que esta en la free
//(3) copiar la papa
	// si es la primera vez, tenemos la idle en tss1 y tss2
	if (TAREA_ACTUAL != TAREA_ANTERIOR){ // si entra es porque ya hice al menos un sched_cargar_sig_tarea
		//tss* contexto_tarea_previa = array_tareas->ant->tarea;	
		/*tss* contexto_tarea_previa_en_gdt = (tss*) ((gdt[free_tss_gdt_index].base_31_24 << 24) +
													(gdt[free_tss_gdt_index].base_23_16 << 16) +
													gdt[free_tss_gdt_index].base_0_15);*/
		if (free_tss_gdt_index == 15)
			tss_copy(array_tareas->ant->tarea, &tss_next_1); //tss_next_1 es apuntado por gdt[15]->base
		else
			tss_copy(array_tareas->ant->tarea, &tss_next_2); //tss_next_1 es apuntado por gdt[16]->base
	  //tss_copy(dst, src);
	}
} 


void sched_cargar_sig_tarea(){

//(1) tengo que tocar el free
//(2) cual es la siguiente tarea a ejecutar, puede ser la idle?, no! esta se llama desde otro lado!
//(3) copiar las cosas en la free, las cosas es la tarea a la que quiero saltar
//(4) guardarme en algun lado que puse a correr esa tarea!
	TAREA_ANTERIOR = TAREA_ACTUAL;
	if (array_tareas != 0){ // chequeo si no hay mas tareas para ejecutar
		tss* tss_aux;
		if (TAREA_ACTUAL == 0){ // si estoy ejecutando la idle
			TAREA_ACTUAL = array_tareas->num_tarea; // como invariante, array_tareas apunta siempre a la tarea actual (en la lista doblemente enlazada)
			tss_aux = array_tareas->tarea;	// 1er paso
		}else{					// si no
			TAREA_ACTUAL = array_tareas->sig->num_tarea;
			tss_aux = array_tareas->sig->tarea;	// 1er paso
		}

		if (tss_free == 16) 	//La tarea que se estaba corriendo es la 15 en la gdt
			tss_copy(&tss_next_2, tss_aux);
		else					//La tarea que se estaba corriendo es la 16 en la gdt
			tss_copy(&tss_next_1, tss_aux);
		
		array_tareas = array_tareas->sig; // como ejecuto la siguiente tarea, muevo el puntero para cumplir el invariante
	
	}else{ // si no hay tareas, cargo la idle
		TAREA_ACTUAL = 0; // TAREA_ACTUAL = 0 == idle
		TAREA_ANTERIOR = 1; // para que entre el if de guardar
		if (tss_free == 16) 	//La tarea que se estaba corriendo es la 15 en la gdt
			tss_copy(&tss_next_2, &tss_idle);
		else					//La tarea que se estaba corriendo es la 16 en la gdt
			tss_copy(&tss_next_1, &tss_idle);
	}
}

//b)
unsigned short sched_proximo_indice() {
	//breakpoint();
	sched_guardar_contexto(tss_free);
	sched_cargar_sig_tarea(tss_free);

	if (tss_busy == 15){
		tss_busy = 16;
		tss_free = 15;}
	else{
		tss_busy = 15;
		tss_free = 16;}

	return (tss_busy << 3); // Devuelvo el indice (shifteado) de la gdt de la prox tarea a ser ejecutada
}
