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

nodo *actual;

typedef struct str_nodo{
	nodo *sig;
	nodo *ant;
	int tarea;
} __attribute__((__packed__, aligned (8))) nodo;



#endif	/* !__SCHED_H__ */
