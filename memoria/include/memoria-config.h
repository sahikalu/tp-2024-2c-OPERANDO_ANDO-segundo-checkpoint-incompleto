#ifndef MEMORIA_MEMORIA_CONFIG_H
#define MEMORIA_MEMORIA_CONFIG_H

// Librerias de internas:
#include "memoria-estructuras.h"

// Librerias de externas:
#include <utils/include/config.h>
#include <utils/include/logger.h>

/**
* @brief Inicializa la configuración de la memoria.
* @return Devuelve un puntero a la estructura de configuración de la memoria.
*/
t_config_kernel *inicializar_config_memoria();

/**
* @brief Carga las configuraciones necesarias para la memoria.
*/
void cargar_configuraciones_de_memoria();

/**
* @brief Verifica si la configuración de la memoria es válida.
* @param config Puntero a la estructura de configuración.
* @return Devuelve 1 si la configuración es válida, 0 en caso contrario.
*/
int is_config_memory_valid(t_config *config);