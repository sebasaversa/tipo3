/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"


#define MMU_COUNT 1024


unsigned int* area_libre = (unsigned int*)0x100000;

typedef struct str_mmu_descriptor {
    unsigned short  mmu_length;
    unsigned int    mmu_addr;
} __attribute__((__packed__)) mmu_descriptor;

typedef struct str_mmu_entry {
		unsigned char p:1;
		unsigned char rw:1;
		unsigned char us:1;
		unsigned char pwt:1;
		unsigned char pcd:1;
		unsigned char a:1;
		unsigned char ign:1;
		unsigned char ps:1;
		unsigned char g:1;
		unsigned char disp:3;
		unsigned int  base_0_20:20;
} __attribute__((__packed__, aligned (4))) mmu_entry;

void mmu_inicializar_dir_kernel();
void mmu_inicializar_dir_tarea();
void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attrs);
void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3);
void inicializar_mmu();
void dameMemoria();

#endif	/* !__MMU_H__ */




