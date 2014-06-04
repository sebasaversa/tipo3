/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar() {
	mmu_entry* pd = (mmu_entry*)(0x27000)
	mmu_entry* pt = (mmu_entry*)(0x28000)
	/*mmu_entry aux = (mmu_entry) {

		(unsigned int)  	0x0000, 		//base_0_15;
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
    };*/
	for (i = 0; i < MMU_COUNT; i++)
	{
		pd[i] = (mmu_entry)0;
	}
	
	mmu[0]->p = 1;
	mmu[1]->p = 1;
	mmu[1]->base_0_15 = 0x1000;
	muu[2]->p = 1;
	mmu[2]->base_0_15 = 0x2000;
	muu[3]->p = 1;
	mmu[3]->base_0_15 = 0x3000;
	
	pd[0] =	(mmu_entry) {
		(unsigned int)  	0x28000, 		//base_0_20;
		(unsigned char)  	0x00,   		//disp:3;
		(unsigned char)  	0x00,   		//g:1;
		(unsigned char)  	0x00,   		//ps:1;
		(unsigned char)  	0x00,   		//ign:1;
		(unsigned char)  	0x00,   		//a:1;
		(unsigned char)  	0x00,   		//pcd:1;
		(unsigned char)  	0x00,   		//pwt:1;
		(unsigned char)  	0x00,   		//us:1;
		(unsigned char)  	0x01,   		//rw:1;
		(unsigned char)  	0x01,   		//p:1;}
	}


mmu_entry mmu[MMU_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (mmu_entry) {

		(unsigned char) 	0x0, 			//base_15_20:4;
		(unsigned short)  	0x0000, 		//base_0_15;
		(unsigned char)  	0x00,   		//disp:3;
		(unsigned char)  	0x00,   		//g:1;
		(unsigned char)  	0x00,   		//ps:1;
		(unsigned char)  	0x00,   		//ign:1;
		(unsigned char)  	0x00,   		//a:1;
		(unsigned char)  	0x00,   		//pcd:1;
		(unsigned char)  	0x00,   		//pwt:1;
		(unsigned char)  	0x00,   		//us:1;
		(unsigned char)  	0x00,   		//rw:1;
		(unsigned char)  	0x00,   		//p:1;
    },                      
}





