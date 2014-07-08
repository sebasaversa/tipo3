; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
extern gdt
extern GDT_DESC
extern IDT_DESC 
extern idt_inicializar
extern mmu_inicializar
extern mmu_inicializar_dir_kernel
extern tss_inicializar
extern pintar
extern pintarTablero
extern deshabilitar_pic
extern resetear_pic
extern habilitar_pic
extern gdt_inic_tss
extern sched_inicializar

global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0
  

    ; Habilitar A20
    CALL habilitar_A20
    ; Cargar la GDT
    LGDT [GDT_DESC]
    ; Setear el bit PE del registro CR0 (esto pasa a modo protegido)
    MOV EAX,CR0
    OR EAX,1
    MOV CR0,EAX
    ; Saltar a modo protegido
    JMP (9*0x08):modoProtegido

    BITS 32

    modoProtegido:
        ;CODIGO
    ;xchg bx, bx
;    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0    
    
    ; Establecer selectores de segmentos
    XOR EAX, EAX
    MOV AX, 1011000b ;1011b == 11d (index de la GDT) | 0 (0 -> GDT / 1 -> LDT) | 00 (NIVEL DE PRIVILEGIO)
    MOV DS, AX
    MOV ES, AX
    MOV GS, AX
    MOV SS, AX
    MOV AX, 1101000b
    MOV FS, AX
    ; Establecer la base de la pila
    MOV ESP, 0x27000
    MOV EBP, ESP

    ; Imprimir mensaje de bienvenida

    ; Inicializar pantalla
    CALL pintarTablero
    CALL idt_inicializar
    LIDT [IDT_DESC]
    
    ; Inicializar el manejador de memoria
    CALL mmu_inicializar_dir_kernel

    ; Inicializar el directorio de paginas
    CALL mmu_inicializar

    ; Cargar directorio de paginas
    
    ; Habilitar paginacion
    
    MOV EAX, 0x27000
    MOV CR3, EAX ;cargo en CR3 la direccion del page directory
    MOV EAX, CR0
    OR EAX, 0x80000000 ;habilitamos paginacion
    MOV CR0, EAX
    
    CALL deshabilitar_pic
    CALL resetear_pic
    CALL habilitar_pic
    STI
  
    ; Inicializar tss
    CALL gdt_inic_tss
    CALL tss_inicializar
    
    ; Inicializar tss de la tarea Idle
    
    ; Inicializar tss de las tanques
    
    ; Inicializar el scheduler
    CALL sched_inicializar
    MOV AX, 14*(0x8)
    LTR AX

    ; Inicializar la IDT
    
    ; Inicializar Game
;    jmp far    
;    xchg bx, bx
	xchg bx, bx
    jmp 15*(0x8):0x0
    xchg bx, bx
    jmp 16*(0x8):0x0
    ; Cargar IDT
    
    ; Configurar controlador de interrupciones
    
    ; pintar posiciones inciales de tanques
    
    ; Cargar tarea inicial

    ; Habilitar interrupciones
 
    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
