/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void inicializar_mmu(){

	
}

void mmu_inicializar_dir_kernel() {
	mmu_entry* pd = (mmu_entry*)(0x27000);
	mmu_entry* pdAux = pd;
	mmu_entry* pt = (mmu_entry*)(0x28000);
	mmu_entry* ptAux = pt;
	unsigned int mem = 0;
	
	mmu_entry aux = (mmu_entry) {

		(unsigned char)  	0x00,   		//p:1;
		(unsigned char)  	0x01,   		//rw:1;
		(unsigned char)  	0x00,   		//us:1;
		(unsigned char)  	0x00,   		//pwt:1;
		(unsigned char)  	0x00,   		//pcd:1;
		(unsigned char)  	0x00,   		//a:1;
		(unsigned char)  	0x00,   		//ign:1;
		(unsigned char)  	0x00,   		//ps:1;
		(unsigned char)  	0x00,   		//g:1;
		(unsigned char)  	0x00,   		//disp:3;
		(unsigned int)  	0x00000, 		//base_0_20:20;
    };
    
    int i;
    int j;
	for (i = 0; i < MMU_COUNT; i++)
	{
		*pd = aux;
		pd +=0x20;
	}
	pd = pdAux;
	
	for (i = 0; i < 4; i++)  //este for pondria la direccion de la page table en los 4 page directory que corresponden
	{
		pd->base_0_20 = (unsigned int) pt >> 12;
		pd->p = 0x01;
		pd +=0x20;
		pt += 0x1000;
	}
	pt = ptAux;
	
	for (i = 0; i < 3; i++)
	{
		for (j = 0; i < MMU_COUNT; j++)
			{
				//*pt = aux;
				pt->p =  0x01;
				pt->base_0_20 = mem;
				pt +=0x20;
				mem += (unsigned int) 0x1000;
			}	
		ptAux += 0x1000;
		pt = ptAux;
	}
	for (j = 0; i < 453; i++)
	{
		pt->p =  0x01;
		pt->base_0_20 = mem;
		pt +=0x20;
		mem += (unsigned int) 0x1000;	
	}
 
}

void mmu_inicializar_dir_tarea(){
	
	mmu_entry* pd = (mmu_entry*)(0x27000);
	mmu_entry* pdAux = pd;
	mmu_entry* pt = (mmu_entry*)(0x28000);
	mmu_entry* ptAux = pt;
	unsigned int mem = 0;
	
	mmu_entry aux = (mmu_entry) {

		(unsigned char)  	0x00,   		//p:1;
		(unsigned char)  	0x01,   		//rw:1;
		(unsigned char)  	0x00,   		//us:1;
		(unsigned char)  	0x00,   		//pwt:1;
		(unsigned char)  	0x00,   		//pcd:1;
		(unsigned char)  	0x00,   		//a:1;
		(unsigned char)  	0x00,   		//ign:1;
		(unsigned char)  	0x00,   		//ps:1;
		(unsigned char)  	0x00,   		//g:1;
		(unsigned char)  	0x00,   		//disp:3;
		(unsigned int)  	0x00000, 		//base_0_20:20;
    };
    
    int i;
    int j;
	for (i = 0; i < MMU_COUNT; i++)
	{
		*pd = aux;
		pd +=0x20;
	}
	pd = pdAux;
	
	for (i = 0; i < 4; i++)  //este for pondria la direccion de la page table en los 4 page directory que corresponden
	{
		pd->base_0_20 = (unsigned int) pt >> 12;
		pd->p = 0x01;
		pd +=0x20;
		pt += 0x1000;
	}
	pt = ptAux;
	
	for (i = 0; i < 3; i++)
	{
		for (j = 0; i < MMU_COUNT; j++)
			{
				//*pt = aux;
				pt->p =  0x01;
				pt->base_0_20 = mem >> 12;
				pt +=0x20;
				mem += (unsigned int) 0x1000;
			}	
		ptAux += 0x1000;
		pt = ptAux;
	}
	for (j = 0; i < 453; i++)
	{
		pt->p =  0x01;
		pt->base_0_20 = mem;
		pt +=0x20;
		mem += (unsigned int) 0x1000;	
	}
 	
	
	
}

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attrs){
	
	mmu_entry* pd = (mmu_entry*) cr3;
	unsigned int table = 0;
	unsigned int ptIndex = 0;
	unsigned int pdIndex = virtual >> 22; //saco el offset del page
	pd += pdIndex; //me muevo dentro del page
	table = pd->base_0_20 << 12; 
	pd = (mmu_entry*)table; //apunto al table que corresponde
	
	ptIndex = virtual << 10;
	ptIndex = ptIndex >> 22; //busco el index de la table
	pd += ptIndex; //me muevo dentro de la table q estoy
	table = pd->base_0_20 << 12; 
	pd = (mmu_entry*)table; //voy a la direccion que busco
	//*pd = fisica; ver esto

	
	
	
}

