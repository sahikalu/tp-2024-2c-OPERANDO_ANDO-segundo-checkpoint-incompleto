#include "../include/kernel-estreucturas.h"

// Variables para la configuracion del Kernel:
t_config_kernel *config_kernel = NULL;

// Variables para el manejo de PCBs:
int pid_counter = 0;

// Variables para el manejo de conexiones con CPU y Memoria:
int socket_dispatcher = 0;
int socket_interrupt = 0;
int socket_memoria = 0;

// Variables para el manejo de estados de los procesos:
t_list *queue_new = NULL;
t_list *queue_ready = NULL;
t_list *queue_exit = NULL;
