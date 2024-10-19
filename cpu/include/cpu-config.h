#ifndef CPU_CPU_CONFIG_H
#define CPU_CPU_CONFIG_H

// Librerias internas:
#include "./include/cpu-estructuras.h"

// Librerias de externas:
#include <utils/include/config.h>
#include <commons/config.h>

/**
* @brief Carga las configuraciones necesarias para la CPU.
*/
void cargar_configuraciones_de_cpu(void);

/**
* @brief Inicializa la configuración de la CPU.
* @return Devuelve un puntero a la estructura de configuración de la CPU.
*/
t_config_cpu* inicializar_config_cpu(void);

/**
* @brief Verifica si la configuración de la CPU es válida.
* @param config Puntero a la estructura de configuración.
* @return Devuelve 1 si la configuración es válida, 0 en caso contrario.
*/
int is_config_cpu_valid(t_config* config);

#endif // CPU_CPU_CONFIG_H