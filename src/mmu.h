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


typedef struct str_mmu_descriptor {
    unsigned short  mmu_length;
    unsigned int    mmu_addr;
} __attribute__((__packed__)) mmu_descriptor;

typedef struct str_mmu_entry {
    unsigned int 	base_0_20:20;
    unsigned char   disp:3;
    unsigned char   g:1;
    unsigned char   ps:1;
    unsigned char   ign:1;
    unsigned char   a:1;
    unsigned char   pcd:1;
    unsigned char   pwt:1;
    unsigned char   us:1;
    unsigned char   rw:1;
    unsigned char   p:1;
} __attribute__((__packed__, aligned (8))) mmu_entry;

void mmu_inicializar();


#endif	/* !__MMU_H__ */




