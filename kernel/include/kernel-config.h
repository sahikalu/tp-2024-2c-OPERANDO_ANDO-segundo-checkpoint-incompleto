#ifndef KERNEL_KERNEL_CONFIG_H
#define KERNEL_KERNEL_CONFIG_H

// Librerias de internas:
#include "../include/kernel-estructuras.h"

// Librerias de externas:
#include <utils/include/config.h>

/**
* @afn t_config_kernel *inicializar_config_kernel()
* @brief Inicializa la configuración del Kernel.
* @return Devuelve la configuración del Kernel.
*/
t_config_kernel *inicializar_config_kernel();

/**
* @afn void cargar_configuraciones_del_kernel()
* @brief Carga las configuraciones del Kernel.
*/
void cargar_configuraciones_del_kernel();

/**
 * @afn int is_config_kernel_valid(t_config *config)
 * @brief Verifica si la configuración del Kernel es válida.
 * @param config Puntero a la estructura de configuración.
 * @return Devuelve 1 si la configuración es válida, 0 en caso contrario.
 */
int is_config_kernel_valid(t_config *config) 

#endif // KERNEL_KERNEL_INIT_H