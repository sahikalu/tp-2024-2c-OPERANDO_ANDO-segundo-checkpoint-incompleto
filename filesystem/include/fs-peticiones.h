#ifndef FS_FS_PETICIONES_H
#define FS_FS_PETICIONES_H

// Librerias externas:
#include <utils/include/socket.h>

// Librerias internas:
#include "fs-estructuras.h"

/**
* @brief Escucha las peticiones del sistema de archivos (FS).
*/
void escuchar_peticiones_fs(void);

/**
* @brief Maneja las peticiones del sistema de archivos (FS).
* @param args Argumentos necesarios para manejar las peticiones.
*/
void peticiones_fs(void *args);


#endif // FS_FS_PETICIONES_H