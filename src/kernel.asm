; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
extern GDT_DESC
extern IDT_DESC 
extern idt_inicializar
extern mmu_inicializar
extern mmu_inicializar_dir_kernel
extern pintar
extern pintarTablero
extern deshabilitar_pic
extern resetear_pic
extern habilitar_pic
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
    CLI

    ; Cambiar modo de video a 80 X 50
    MOV AX, 0003h
    INT 10h ; set mode 03h
    XOR BX, BX
    MOV BX, 1112h
    INT 10h ; load 8x8 font

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
    
    CALL pintar
    CALL idt_inicializar
	LIDT [IDT_DESC]
	
	CALL pintarTablero

	CALL mmu_inicializar_dir_kernel
	MOV EAX, 0x27000
	MOV CR3, EAX ;cargo en CR3 la direccion del page directory
	MOV EAX, CR0
    OR EAX, 0x80000000 ;habilitamos paginacion
	MOV CR0, EAX
    ; Imprimir mensaje de bienvenida
    
    ; Inicializar pantalla
    
    ; Inicializar el manejador de memoria
    
    ; Inicializar el directorio de paginas
    CALL mmu_inicializar
    
    CALL deshabilitar_pic
    CALL resetear_pic
    CALL habilitar_pic
    ; Cargar directorio de paginas
   
    ; Habilitar paginacion
    
    ; Inicializar tss
    
    ; Inicializar tss de la tarea Idle
    
    ; Inicializar tss de las tanques
    
    ; Inicializar el scheduler
    
    ; Inicializar la IDT
    
    ; Inicializar Game
    
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
