#include "../include/fs-config.h"

t_config_fs *inicializar_config_fs() {
    t_config_fs *config = malloc(sizeof(t_config_fs));
    config->puerto_escucha = NULL;
    config->mount_dir = NULL;
    config->block_size = 0;
    config->block_count = 0;
    config->retardo_acceso_bloque = 0;
    config->log_level = NULL;

    return config;
}

void cargar_configuraciones_de_fs() {
    
    // Inicializo la configuracion del FS y abro el archivo de configuracion:
    config_fs = inicializar_config_fs();
    t_config *config = config_create_or_exit("fs.config");

    // Verifico que el archivo de configuracion tenga todas las claves necesarias:
    if(is_config_fs_valid(config)) {
        log_error(logger, "No se encontraron todas las claves necesarias en el archivo de configuracion");
        exit(EXIT_FAILURE);
    }

    // Cargo las configuraciones del FS:
    assign_string_value_config(&config_fs->puerto_escucha, config, "PUERTO_ESCUCHA");
    assign_string_value_config(&config_fs->mount_dir, config, "MOUNT_DIR");

    config_fs->block_size = config_get_int(config, "BLOCK_SIZE");
    config_fs->block_count = config_get_int(config, "BLOCK_COUNT");
    config_fs->retardo_acceso_bloque = config_get_int(config, "RETARDO_ACCESO_BLOQUE");

    assign_string_value_config(&config_fs->log_level, config, "LOG_LEVEL");
}

int is_config_fs_valid(t_config *config) {
    
    // Creamos un array con las claves necesarias:
    char *keys[] = {
        "PUERTO_ESCUCHA",
        "MOUNT_DIR",
        "BLOCK_SIZE",
        "BLOCK_COUNT",
        "RETARDO_ACCESO_BLOQUE",
        "LOG_LEVEL",
        NULL
    };

    return config_exists_keys(config, keys);
}