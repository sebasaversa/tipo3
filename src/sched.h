/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "screen.h"
#include "tss.h"

unsigned short sched_proximo_indice();


typedef struct str_nodo{
	struct str_nodo *sig;		// para las 8 tareas
	struct str_nodo *ant;		// para las 8 tareas
	tss* tarea;
} __attribute__((__packed__, aligned (8))) nodo;

void sched_cargar_sig_tarea(nodo* n, gdt_entry gdt); //agregue esto
void sched_guardar_contexto(tss* ts, tss* ts2); //agregue esto

extern nodo* array_tareas;

#endif	/* !__SCHED_H__ */

