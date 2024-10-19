#include "../include/kernel-config.h"

t_config_kernel *inicializar_config_kernel() {
    t_config_kernel *config_kernel = malloc(sizeof(t_config_kernel));
    config_kernel->puerto_memoria = NULL;
    config_kernel->ip_memoria = NULL;
    config_kernel->ip_cpu = NULL;
    config_kernel->puerto_memoria = 0;
    config_kernel->puerto_cpu_dispatch = 0;
    config_kernel->puerto_cpu_interrupt = 0;
    config_kernel->algoritmo_planificacion = NULL;
    config_kernel->quantum = 0;
    config_kernel->log_level = NULL;

    return config_kernel;
}

void cargar_configuraciones_del_kernel() {

    // Inicializo la configuracion del Kernel y abro el archivo de configuracion:
    config_kernel = inicializar_config_kernel();
    t_config *config = config_create_or_exit("kernel.config");

    // Verifico que el archivo de configuracion tenga todas las claves necesarias:
    if(is_config_kernel_valid(config)) {
        log_error(logger, "No se encontraron todas las claves necesarias en el archivo de configuracion");
        exit(EXIT_FAILURE);
    }

    // Cargo las configuraciones de la memoria:
    assign_string_value_config(&config_kernel->ip_memoria, config, "IP_MEMORIA");
    assign_string_value_config(&config_kernel->puerto_memoria, config, "PUERTO_MEMORIA");

    // Configuracion de las conexiones con CPU:
    assign_string_value_config(&config_kernel->ip_cpu, config, "IP_CPU");
    assign_string_value_config(&config_kernel->puerto_cpu_dispatch, config, "PUERTO_CPU_DISPATCH");
    assign_string_value_config(&config_kernel->puerto_cpu_interrupt, config, "PUERTO_CPU_INTERRUPT");

    // Configuracion del algoritmo de planificacion:
    assign_string_value_config(&config_kernel->algoritmo_planificacion, config, "ALGORITMO_PLANIFICACION");

    // Configuracion del nivel de log:
    assign_string_value_config(&config_kernel->log_level, config, "LOG_LEVEL");

    // Cargo el resto de las configuraciones:
    config_kernel->quantum = config_get_int(config, "QUANTUM");
}


int is_config_kernel_valid(t_config *config) {
    
    // Creamos un array con las claves necesarias:
    char *keys[] = {
        "PUERTO_MEMORIA",
        "IP_MEMORIA",
        "IP_CPU",
        "PUERTO_CPU_DISPATCH",
        "PUERTO_CPU_INTERRUPT",
        "ALGORITMO_PLANIFICACION",
        "QUANTUM",
        "LOG_LEVEL",
        NULL
    };

    // Creamos un array con los valores validos para el algoritmo de planificacion:
    char *algoritmos_validos[] = { "FIFO", "RR", "VRR", NULL};

    return config_exists_keys(config, keys) && is_key_value_valid("ALGORITMO_PLANIFICACION", config, algoritmos_validos);
}
