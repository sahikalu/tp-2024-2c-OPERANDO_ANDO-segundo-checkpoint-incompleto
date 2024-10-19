#include "./include/cpu-config.h"

t_config_cpu *inicializar_config_cpu() {
    t_config_cpu *config_cpu = malloc(sizeof(t_config_cpu));
    config_cpu->ip_memoria = NULL;
    config_cpu->puerto_memoria = NULL;
    config_cpu->puerto_dispatch = NULL;
    config_cpu->puerto_interrupt = NULL;
    config_cpu->log_level = NULL;

    return config_cpu;
}

void cargar_configuraciones_de_cpu() {

    // Inicializo la configuracion de la CPU y abro el archivo de configuracion:
    config_cpu = inicializar_config_cpu();
    t_config *config = config_create_or_exit("cpu.config");

    // Verifico que el archivo de configuracion tenga todas las claves necesarias:
    if(is_config_cpu_valid(config)) {
        log_error(logger, "No se encontraron todas las claves necesarias en el archivo de configuracion");
        exit(EXIT_FAILURE);
    }

    // Cargo las configuraciones de la memoria:
    assign_string_value_config(&config_cpu->ip_memoria, config, "IP_MEMORIA");
    assign_string_value_config(&config_cpu->puerto_memoria, config, "PUERTO_MEMORIA");

    // Configuracion de las conexiones con CPU:
    assign_string_value_config(&config_cpu->puerto_dispatch, config, "PUERTO_DISPATCH");
    assign_string_value_config(&config_cpu->puerto_interrupt, config, "PUERTO_INTERRUPT");

    // Configuracion del nivel de log:
    assign_string_value_config(&config_cpu->log_level, config, "LOG_LEVEL");
}

int is_config_cpu_valid(t_config *config) {

    // Creamos un array con las claves necesarias:
    char *keys[] = {
        "IP_MEMORIA",
        "PUERTO_MEMORIA",
        "PUERTO_DISPATCH",
        "PUERTO_INTERRUPT",
        "LOG_LEVEL",
        NULL
    };

    return config_exists_keys(config, keys);
}