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

tss* buscar_contexto_tarea(short task_actual);
tss* buscar_contexto_tarea_ant(short task_actual);
void sched_guardar_contexto(unsigned int free_tss_gdt_index); //agregue esto
void sched_cargar_sig_tarea(); //agregue esto

extern void sched_inicializar();
extern unsigned int TAREA_ACTUAL;
extern unsigned int TAREA_ANTERIOR;

#endif	/* !__SCHED_H__ */

