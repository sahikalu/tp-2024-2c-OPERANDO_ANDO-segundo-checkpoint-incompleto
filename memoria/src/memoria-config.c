#include "../include/memoria-config.h"

t_config_kernel *inicializar_config_memoria() {
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

void cargar_configuraciones_de_memoria() {

    // Inicializo la configuracion de la memoria y abro el archivo de configuracion:
    config_memoria = inicializar_config_memoria();
    t_config *config = create_config_or_exit("memoria.config");

    if(!is_config_memory_valid(config)) {
        log_error(logger, "No se encontraron todas las claves necesarias en el archivo de configuracion");
        exit(EXIT_FAILURE);
    }

    // Valores para servidor de memoria:
    assign_string_value_config(&config_memoria->puerto_escucha, config, "PUERTO_ESCUCHA");

    // Valores del filesystem:
    assign_string_value_config(&config_memoria->ip_filesystem, config, "IP_FILESYSTEM");
    assign_string_value_config(&config_memoria->puerto_filesystem, config,"PUERTO_FILESYSTEM");

    // Valores basicos:
    assign_string_value_config(&config_memoria->path_instrucciones, config, "PATH_INSTRUCCIONES");
    config_memoria->retardo_respuesta = config_get_int(config, "RETARDO_RESPUESTA");
    config_memoria->tam_memoria = config_get_int(config, "TAM_MEMORIA");

    // Esquema y algoritmo de busqueda:
    assign_string_value_config(&config_memoria->esquema, config, "ESQUEMA");
    assign_string_value_config(&config_memoria->algoritmo_busqueda, config, "ALGORITMO_BUSQUEDA");
}

int is_config_memory_valid(t_config *config) {
    
    // Creamos un array con las claves necesarias:
    char *keys[] = {
        "PUERTO_ESCUCHA",
        "IP_FILESYSTEM",
        "PUERTO_FILESYSTEM",
        "TAM_MEMORIA",
        "PATH_INSTRUCCIONES",
        "RETARDO_RESPUESTA",
        "ESQUEMA",
        "ALGORITMO_BUSQUEDA",
        "PARTICIONES",
        "LOG_LEVEL",
        NULL
    };

    // Creamos un array con los valores validos para el esquema y el algoritmo de busqueda:
    char *esquemas_validos[] = { "FIJO", "DINAMICO", NULL};
    char *algoritmos_validos[] = { "FIRST", "BEST", "NEXT", NULL};

    return config_exists_keys(config, keys) && is_key_value_valid("ESQUEMA", config, esquemas_validos) 
            && is_key_value_valid("ALGORITMO_BUSQUEDA", config, algoritmos_validos);
}
