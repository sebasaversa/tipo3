/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "mmu.h"

tss tss_next_1;
tss tss_next_2;

tss tss_inicial;
tss tss_idle;

tss tss_tanques[CANT_TANQUES];

void tss_inicializar_tarea_idle()
{
	gdt[GDT_IDX_TSS_ACTUAL] = define_gdt_tss((unsigned int)&tss_next_1);
	tss_next_1 = tss_idle;
	tss_next_1.cr3 		= (unsigned int)0x27000;
	tss_next_1.eip 		= (unsigned int)0x20000; // esta es la virtual de cada tarea que luego se mapea a una fisica distinta no?
	tss_next_1.eflags 	= (unsigned int)0x0000202;
	tss_next_1.ebp 		= 0x27000;
	tss_next_1.esp 		= 0x27000;
    tss_next_1.cs 		=  9*(0x8);
	tss_next_1.es 		= 11*(0x8);
    tss_next_1.ss 		= 11*(0x8);
    tss_next_1.ds 		= 11*(0x8);
    tss_next_1.fs 		= 11*(0x8);
    tss_next_1.gs 		= 11*(0x8);

	tss_next_2 = tss_idle;
	tss_next_2.cr3 		= (unsigned int)0x27000;
	tss_next_2.eip 		= (unsigned int)0x20000; // esta es la virtual de cada tarea que luego se mapea a una fisica distinta no?
	tss_next_2.eflags 	= (unsigned int)0x0000202;
	tss_next_2.ebp 		= 0x27000;
	tss_next_2.esp 		= 0x27000;
    tss_next_2.cs 		=  9*(0x8);
	tss_next_2.es 		= 11*(0x8);
    tss_next_2.ss 		= 11*(0x8);
    tss_next_2.ds 		= 11*(0x8);
    tss_next_2.fs 		= 11*(0x8);
    tss_next_2.gs 		= 11*(0x8);

}

void tss_inicializar_tareas_tanques()
{	
	int i = 0;	

	//... INICIALIZO LAS ENTRADAS DE LA GDT PARA LA TSS2
/*	gdt[GDT_IDX_TSS_ANTERIOR].base_0_15 = ((unsigned int)&tss_next_2 << 16) >> 16;
	gdt[GDT_IDX_TSS_ANTERIOR].base_23_16 = (unsigned int)&tss_next_2 >> 16;
	//GDT_IDX_TSS_ANTERIOR->base_31_24 = ;
	gdt[GDT_IDX_TSS_ANTERIOR].limit_0_15 = 0x67;
	gdt[GDT_IDX_TSS_ANTERIOR].limit_16_19 = 0;
*/	
	for (i = 0; i < CANT_TANQUES; i++){
		//breakpoint();
		tss_tanques[i].cr3 = (unsigned int) (0x100000 + i*0x1000);
		tss_tanques[i].eip = (unsigned int) 0x8000000;
		tss_tanques[i].eflags = (unsigned int) 0x0000202;
		tss_tanques[i].ebp = tss_tanques[i].eip + 0x2000;	
		tss_tanques[i].esp = tss_tanques[i].ebp;
		tss_tanques[i].esp0 = (unsigned int) (area_libre + 0x2000);
//		dameMemoriaNivel0();
//		dameMemoriaNivel0();
		//inicializar los selectores de segmento que nos dijo marco
		array_tareas->sig 		= 0;
		array_tareas->ant 		= 0;
		array_tareas->tarea 	= &tss_tanques[i];
		array_tareas->num_tarea	= i;
		
		if (i < 7){
			nodo* nodo_sig = 0;
			nodo_sig->sig = 0;
			nodo_sig->ant = array_tareas;
			nodo_sig->tarea = 0;
			nodo_sig->num_tarea = 0;
			array_tareas->sig = nodo_sig;
			array_tareas = array_tareas->sig;
		}
	}

	nodo* array_tareas_tmp = array_tareas;
	array_tareas->sig = array_tareas_tmp;
	array_tareas_tmp->ant = array_tareas;
	array_tareas = array_tareas->sig;
}

void tss_inicializar() {
	tss_inicializar_tarea_idle();
	tss_inicializar_tareas_tanques();
}
