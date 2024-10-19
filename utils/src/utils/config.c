#include "../include/config.h"

char *config_get_string(t_config *config, char *key) {
    char *value = config_get_string_value(config, key);

    if (!value) {
        log_error(logger, "No se encontro la clave %s en el archivo de configuracion", key);
        exit(EXIT_FAILURE);
    }

    return value;
}

int config_get_int(t_config *config, char *key) {
    int value = config_get_int_value(config, key);

    if (!value) {
        log_error(logger, "No se encontro la clave %s en el archivo de configuracion", key);
        exit(EXIT_FAILURE);
    }

    return value;
}

int config_exists_keys(t_config *config, char **keys) {
    for (int i = 0; keys[i] != NULL; i++) {
        if (!config_has_property(config, keys[i])) {
            return 0;
        }
    }

    return 1;
}

int is_key_value_valid(char *key, t_config *config, char **valid_values) {
    char *value = config_get_string(config, key);

    for (int i = 0; valid_values[i] != NULL; i++) {
        if (strcmp(value, valid_values[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

void assign_string_value_config(char **destino, t_config *config, char *key) {
    *destino = config_get_string(config, key);
}

t_config* create_config_or_exit(const char* config_file) {
    t_config *config = config_create(config_file);

    // Compruebo que se haya podido abrir el archivo de configuración:
    if (!config) {
        log_error(logger, "No se pudo abrir el archivo de configuración: %s", config_file);
        exit(EXIT_FAILURE);
    }

    return config;
}