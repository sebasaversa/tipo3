/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_next_1;
tss tss_next_2;

tss tss_inicial;
tss tss_idle;

tss tss_tanques[CANT_TANQUES];
/*
void tss_inicializar_tarea_idle();
void tss_inicializar_tarea_tanque(unsigned int id);
void tss_inicializar_tareas_tanques();
void tss_copy(tss* tss_src, tss* tss_dst);
unsigned int tss_get_cr3(unsigned int id);

*/
void tss_inicializar() {
	tss_inicializar_tarea_idle();
	tss_inicializar_tareas_tanques();
}

void tss_inicializar_tarea_idle()
{
	gdt[GDT_IDX_TSS1].base_0_15 = ((unsigned int)&tss_idle << 16) >> 16;
	gdt[GDT_IDX_TSS1].base_23_16 = (unsigned int)&tss_idle >> 16;
	//GDT_IDX_TSS1->base_31_24 = ;
	unsigned int aux = (unsigned int) (0x0FFF);
	gdt[GDT_IDX_TSS1].limit_0_15 = (aux << 16) >> 16;
	gdt[GDT_IDX_TSS1].limit_16_19 = aux >> 16;
	tss_idle.cr3 = (unsigned int)0x27000;
	tss_idle.eip = (unsigned int)0x20000;
	tss_idle.eflags = (unsigned int)0x0000202;
	tss_idle.ebp = 0x27000;
	tss_idle.esp = 0x27000;
}

void tss_inicializar_tareas_tanques()
{	
	int i = 0;	
	for (i = 0; i < CANT_TANQUES; i++){
		dameMemoriaNivel0();
		tss_tanques[i].cr3 = (unsigned int) (0x27000 + i*0x2000);
		tss_tanques[i].eip = (unsigned int) 0x800000;
		tss_tanques[i].eflags = (unsigned int) 0x0000202;
		tss_tanques[i].ebp = tss_tanques[i].eip + 4096;	
		tss_tanques[i].esp = tss_tanques[i].ebp;
		tss_tanques[i].esp0 = (unsigned int) (area_libre + 0x1000);
	}
}

