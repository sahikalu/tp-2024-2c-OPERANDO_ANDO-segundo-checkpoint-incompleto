#ifdef UTILS_CONFIG_H
#define UTILS_CONFIG_H

// Librerias externas:
#include <commons/config.h>
#include <commons/string.h>
#include <string.h>

// Librerias internas:
#include <utils/include/logger.h>

/**
* @brief Obtiene una cadena de texto asociada a una clave en la configuración.
* @param config Puntero a la estructura de configuración.
* @param key Clave de la cual se obtendrá el valor.
* @return Devuelve un puntero a la cadena de texto asociada a la clave.
*/
char *config_get_string(t_config *config, char *key);

/**
* @brief Obtiene un entero asociado a una clave en la configuración.
* @param config Puntero a la estructura de configuración.
* @param key Clave de la cual se obtendrá el valor.
* @return Devuelve el entero asociado a la clave.
*/
int config_get_int(t_config *config, char *key);

/**
* @brief Verifica si existen todas las claves especificadas en la configuración.
* @param config Puntero a la estructura de configuración.
* @param keys Arreglo de claves a verificar.
* @return Devuelve 1 si todas las claves existen, 0 en caso contrario.
*/
int config_exists_keys(t_config *config, char **keys);

/**
* @brief Verifica si el valor asociado a una clave es válido según una lista de valores válidos.
* @param key Clave de la cual se verificará el valor.
* @param config Puntero a la estructura de configuración.
* @param valid_values Arreglo de valores válidos.
* @return Devuelve 1 si el valor es válido, 0 en caso contrario.
*/
int is_key_value_valid(char *key, t_config *config, char **valid_values);

/**
* @brief Asigna un valor de cadena de texto a una variable de destino desde la configuración.
* @param destino Puntero a la variable de destino donde se asignará el valor.
* @param config Puntero a la estructura de configuración.
* @param key Clave de la cual se obtendrá el valor.
*/
void assign_string_value_config(char **destino, t_config *config, char *key);

/**
* @brief Crea una configuración a partir de un archivo y maneja errores si no se puede abrir.
* @param config_file Nombre del archivo de configuración.
* @param logger Logger para registrar errores.
* @return Devuelve un puntero a la configuración creada.
*/
t_config* create_config_or_exit(char* config_file);