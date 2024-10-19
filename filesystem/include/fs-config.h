#ifndef FS_FS_CONFIG_H
#define FS_FS_CONFIG_H

// Librerias externas:
#include <commons/config.h>
#include <utils/include/config.h>
#include <utils/include/logger.h>

// Librerias internas:
#include "fs-estructuras.h"

/**
* @brief Carga las configuraciones necesarias para el sistema de archivos (FS).
*/
void cargar_configuraciones_de_fs(void);

/**
* @brief Inicializa la configuración del sistema de archivos (FS).
* @return Devuelve un puntero a la estructura de configuración del FS.
*/
t_config_fs* inicializar_config_fs(void);

/**
* @brief Verifica si la configuración del sistema de archivos (FS) es válida.
* @param config Puntero a la estructura de configuración.
* @return Devuelve 1 si la configuración es válida, 0 en caso contrario.
*/
int is_config_fs_valid(t_config* config);

#endif //FS_FS_CONFIG_H