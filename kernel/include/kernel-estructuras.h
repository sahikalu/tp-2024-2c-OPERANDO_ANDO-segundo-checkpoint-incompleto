#ifndef KERNEL_KERNEL_ESTRUCTURAS_H
#define KERNEL_KERNEL_ESTRUCTURAS_H

// Librerias externas:
#include <commons/colections/list.h>

typedef struct {
    char *puerto_memoria;
    char *ip_memoria;
    char *ip_cpu;
    int puerto_memoria;
    int puerto_cpu_dispatch;
    int puerto_cpu_interrupt;
    char *algoritmo_planificacion;
    int quantum;
    char *log_level;
} t_config_kernel;

typedef struct {
    int pid;
    int next_tid;
    t_list *tids;
    t_list *mutexs;
} t_pcb;

typedef struct {
    int tid;
    int prioridad;
} t_tcb;

typedef struct {
    int id;
    int estado;
    t_list *cola_bloqueados;
    int hilo_asignado;
} t_mutez;


// Variables globales:
extern t_config_kernel *config_kernel;

// Variables para el manejo de PCBs y TCBs:
extern int pid_counter;

// Variables para el manejo de conexiones con CPU y Memoria:
extern int socket_dispatcher;
extern int socket_interrupt;
extern int socket_memoria;

// Variables para el manejo de estados de los procesos:
extern t_list *queue_new;
extern t_list *queue_ready;
extern t_list *queue_exit;

#endif