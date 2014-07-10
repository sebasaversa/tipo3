/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

unsigned int* area_libre = (unsigned int*)0x100000;
unsigned int cr3_array[8];

void dameMemoriaKPaginas(int i){
	area_libre += (unsigned int) (i*0x1000);
}

void mmu_inicializar_dir_kernel() {
	mmu_entry* pd = (mmu_entry*)(0x27000);
	//mmu_entry* pdAux = pd;
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
	for (i = 0; i < MMU_COUNT ; i++) //inicializo toda la page directory en 0 (las 1024 entradas)
	{
		pd[i] = aux;
	}
	//pd = (mmu_entry*)(0x27000);
	
	//////////////////////////////////////////////////
	////////////////// IDENTITY MAPPING //////////////
	//////////////////////////////////////////////////

	for (i = 0; i < 4; i++)  //este for pondria la direccion de la page table en los 4 page directory que corresponden
	{
		pd[i].base_0_20 = ((unsigned int) pt) >> 12;
		pd[i].p = 0x01;
		pt += 0x1000;
	}
	pt = ptAux;
	
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < MMU_COUNT; j++)
		{
			//*pt = aux;
			pt[1024*i + j].base_0_20 = mem >> 12;
			pt[1024*i + j].p =  0x01;
			mem += 0x1000;
		}	
//		pt += 0x1000;
	}
	
	for (i = 0; i < 452; i++)
	{
		pt[1024*3 + i].base_0_20 = mem >> 12;
		pt[1024*3 + i].p =  0x01;
		mem += 0x1000;	
	}
 	
 }
	//////////////////////////////////////////////////
	///////////// TERMINA IDENTITY MAPPING ///////////
	//////////////////////////////////////////////////

void mmu_inicializar_dir_tarea(){

	
	mmu_entry* pd = (mmu_entry*)(area_libre);
	dameMemoriaKPaginas(1);
	mmu_entry* pt = (mmu_entry*)(area_libre);
	dameMemoriaKPaginas(5);
	mmu_entry* ptAux = pt;
	unsigned int mem = (unsigned int) 0x0;
	
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
	for (i = 0; i < MMU_COUNT ; i++) //inicializo toda la page directory en 0 (las 1024 entradas)
	{
		pd[i] = aux;
	}

	for (i = 0; i < 5; i++)  //este for pondria la direccion de la page table en los 4 page directory que corresponden
	{
		pd[i].base_0_20 = ((unsigned int) pt) >> 12;
		pd[i].p = 0x01;
		pt += 1024;
	}
	pt = ptAux;
	
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < MMU_COUNT; j++)
		{
			pt[1024*i + j].base_0_20 = mem >> 12;
			pt[1024*i + j].p =  0x01;
			mem += 0x1000;
		}	
	}
}

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attrs){

	mmu_entry* pd = (mmu_entry*) (cr3 >> 12);
	unsigned int table = 0;
	unsigned int ptIndex = 0;
	unsigned int pdIndex = virtual >> 22; //saco el offset del page
	unsigned int index = virtual;
	pd += pdIndex * 4 + 3; //me muevo dentro del page
	table = pd->base_0_20; 
	pd = (mmu_entry*)table; //apunto al page table que corresponde
	ptIndex = virtual << 10;
	ptIndex = ptIndex >> 22; //busco el index de la table
	pd += ptIndex * 4 + 3; //me muevo dentro de la table q estoy
	table = pd->base_0_20; 
	pd = (mmu_entry*)table; //voy al bloque de direccion fisica de 4k que busco
	index = index << 20;
	index = index >> 20;
	pd += index; //me muevo dentro del bloque de 4k de memoria a donde quiero copiar el dato
	unsigned int* pd2 =(unsigned int*) pd;
	*pd2 = fisica;
	// pd es tipo mmu_entry por eso no le puedo pasar fisica que es unsigned int, pensaba crear otro puntero a pd del tipo necesario

	tlbflush();
}

void mmu_inicializar(){
	short i;
	unsigned int codTarea = (unsigned int) 0x10000; //esta es la direccion de la primer pagina de la primer tarea
	unsigned int dirVirtual = (unsigned int) 0x8000000; //esta es la direccion virtual desde donde arranco a copiar las tareas
	for(i = 0; i < 8; i++){
		unsigned int* cr3 = area_libre; //guardo la direccion del PD de esta tarea
		cr3_array[i] = ((unsigned int)cr3) << 12;
		//dameMemoriaKPaginas(5); // ver cuanto pido
		mmu_inicializar_dir_tarea(); // creo el page directory
		mmu_mapear_pagina(dirVirtual, (unsigned int) cr3, codTarea, 0); //escribo la primer pagina de la tarea en la memoria fisica
		codTarea += (unsigned int) 0x1000; //voy a la siguiente pagina de la tarea
		dirVirtual += (unsigned int) 0x1000; //voy a la siguiente direccion fisica libre para copiar la nueva pagina
		mmu_mapear_pagina(dirVirtual, *area_libre, codTarea, 0); //mapeo la segunda pagina de la tarea en la memoria fisica
		codTarea += (unsigned int) 0x1000; //voy a la siguiente tarea
		dirVirtual += (unsigned int) 0x1000; // voy al siguiente espacio libre para copiar la nueva tarea
		dameMemoriaKPaginas(5); //pido memoria para la siguiente tarea
	}

}    

void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){
	mmu_entry* pd = (mmu_entry*) (cr3 >> 12);
	unsigned int table = 0;
	unsigned int ptIndex = 0;
	unsigned int pdIndex = virtual >> 22; //saco el offset del page
	unsigned int index = virtual;
	pd += pdIndex; //me muevo dentro del page
	table = pd->base_0_20 << 12; 
	pd = (mmu_entry*)table; //apunto al table que corresponde
	
	ptIndex = virtual << 10;
	ptIndex = ptIndex >> 22; //busco el index de la table
	pd += ptIndex; //me muevo dentro de la table q estoy
	table = pd->base_0_20 << 12; 
	pd = (mmu_entry*)table; //voy al bloque de direccion que busco
	index = index << 20;
	index = index >> 20;
	pd += index;
	unsigned int* pd2 =(unsigned int*) pd;
	*pd2 = 0;
	tlbflush();
}

