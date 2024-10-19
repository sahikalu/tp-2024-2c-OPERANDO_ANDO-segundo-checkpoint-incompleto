#ifndef MEMORIA_MEMORIA_CONEXIONES_H
#define MEMORIA_MEMORIA_CONEXIONES_H

// Librerias internas:
#include "memoria-estructuras.h"

// Librerias externas:
#include <utils/include/logger.h>
#include <utils/include/socket.h>

/**
* @brief Genera una conexión con el sistema de archivos (FS).
*/
void generar_conexion_con_fs(void);

/**
* @brief Crea el servidor de memoria.
*/
void crear_servidor_memoria(void);
