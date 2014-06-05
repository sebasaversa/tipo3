/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar() {
	mmu_entry* pd = (mmu_entry*)(0x27000);
	mmu_entry* pdAux = pd;
	mmu_entry* pt = (mmu_entry*)(0x28000);
	mmu_entry* ptAux = pt;
	int mem = 0;
	
	mmu_entry aux = (mmu_entry) {

		(unsigned int)  	0x00000, 		//base_0_20;
		(unsigned char)  	0x00,   		//disp:3;
		(unsigned char)  	0x00,   		//g:1;
		(unsigned char)  	0x00,   		//ps:1;
		(unsigned char)  	0x00,   		//ign:1;
		(unsigned char)  	0x00,   		//a:1;
		(unsigned char)  	0x00,   		//pcd:1;
		(unsigned char)  	0x00,   		//pwt:1;
		(unsigned char)  	0x00,   		//us:1;
		(unsigned char)  	0x01,   		//rw:1;
		(unsigned char)  	0x00,   		//p:1;
    };
    
    int i;
    int j;
	for (i = 0; i < MMU_COUNT; i++)
	{
		*pd = aux;
		pd++;
	}
	pd = pdAux;
	
	for (i = 0; i < 4; i++)  //este for pondria la direccion de la page table en los 4 page directory que corresponden
	{
		pd->base_0_20 = (int) pt;
		pd->p = 0x01;
		pd++;
		pt += 0x1000;
	}
	pt = ptAux;
	
	for (i = 0; i < 3; i++)
	{
		for (j = 0; i < MMU_COUNT; j++)
			{
				*pt = aux;
				pt->p = 0x01;
				pt++;
				pt->base_0_20 = mem;
				mem += 1024;
			}
	}
	
	
}





