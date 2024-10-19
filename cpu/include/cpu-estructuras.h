#ifndef CPU_CPU_ESTRUCTURAS_H
#define CPU_CPU_ESTRUCTURAS_H

#include <utils/include/estructuras.h>
typedef struct {
    char *ip_memoria;
    char *puerto_memoria;
    char *puerto_dispatch;
    char *puerto_interrupt;
    char *log_level;
} t_config_cpu;

// Variables globales:
// Variables de configuración:
extern t_config_cpu *config_cpu = NULL;

// Variables de servidor:
extern int socket_servidor_dispatch = 0;
extern int socket_servidor_interrupt = 0;

// Variables de socket:
extern int socket_memoria = 0;

// Variables de proceso:
extern int pid;
extern int tid;
extern t_contexto_de_proceso *contexto;
extern exec_cicle;

#endif // CPU_CPU_ESTRUCTURAS_H
