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

typedef struct str_selector_offset{
    int offset;       
    short selector;
} __attribute__((__packed__)) selector_offset;


unsigned short sched_proximo_indice();

void sched_cargar_sig_tarea(); //agregue esto
void sched_guardar_contexto(tss* ts, tss* ts2); //agregue esto

extern selector_offset sel_tarea;
extern void sched_inicializar();
#endif	/* !__SCHED_H__ */

