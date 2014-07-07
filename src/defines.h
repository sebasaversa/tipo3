/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_TANQUES            8
#define PAGE_SIZE               0x00001000
#define TASK_SIZE               2 * 4096
#define CAMPO_SIZE              50


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_CODE_DESC_0			9
#define GDT_IDX_CODE_DESC_3			10
#define GDT_IDX_DATA_DESC_0			11
#define GDT_IDX_DATA_DESC_3			12
#define GDT_IDX_VIDEO_DESC			13
#define GDT_IDX_TSS_INICIAL			14
#define GDT_IDX_TSS_ACTUAL			15
#define GDT_IDX_TSS_ANTERIOR		16


/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

#endif  /* !__DEFINES_H__ */
