#include "./include/cpu-estructuras.h"

// Variables globales:
// Variables de configuración:
t_config_cpu *config_cpu = NULL;

// Variables de servidor:
int socket_servidor_dispatch = 0;
int socket_servidor_interrupt = 0;

// Variables de socket:
int socket_memoria = 0;

// Variables de proceso:
int pid;
int tid;
t_contexto_de_proceso *contexto = NULL;
int exec_cicle = 1;