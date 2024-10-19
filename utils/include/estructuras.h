#ifndef UTILS_ESTRUCTURAS_H
#define UTILS_ESTRUCTURAS_H

typedef enum {
    // Operaciones básicas:
    SET,
    READ_MEM,
    WRITE_MEM,
    SUM,
    SUB,
    JNZ.
    LOG,

    // Operaciones de procesos, que se consideran syscalls:
    DUMP_MEM,
    IO,
    PROCCES_CREATE,
    THREAR_CREATE,
    THREAD_JOIN,
    THREAD_CANCEL,
    MUTEX_CREATE,
    MUTEX_LOCK,
    MUTEX_UNLOCK,
    THREAD_EXIT,
    PROCESS_EXIT,
} code_instruccion;
// ! este creo q no va
typedef struct {
    uint32_t PC; // Program Counter
    uint32_t AX; // Proposito general
    uint32_t BX; // Proposito general
    uint32_t CX; // Proposito general
    uint32_t DX; // Proposito general
    uint32_t EX; // Proposito general
    uint32_t FX; // Proposito general
    uint32_t GX; // Proposito general
    uint32_t HX; // Proposito general
} t_contexto_de_proceso;

typedef struct {
    code_instruccion instruccion;
    t_list *operandos; 
} t_instruccion;

//! contexto de ejecucion
typedef struct {
    uint32_t PC;       // Program Counter
    uint32_t AX;       // Registro de propósito general
    uint32_t BX;       // Registro de propósito general
    uint32_t CX;       // Registro de propósito general
    uint32_t DX;       // Registro de propósito general
    uint32_t EX;       // Registro de propósito general
    uint32_t FX;       // Registro de propósito general
    uint32_t GX;       // Registro de propósito general
    uint32_t HX;       // Registro de propósito general
    uint32_t base;     // Dirección base del proceso
    uint32_t limite;   // Tamaño de la partición del proceso
} ContextoEjecucion;

#endif // UTILS_ESTRUCTURAS_H