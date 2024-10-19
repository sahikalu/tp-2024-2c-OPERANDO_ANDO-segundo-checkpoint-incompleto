#ifndef CPU_CPU_CONEXIONES_H
#define CPU_CPU_CONEXIONES_H

// Librerias internas:
#include "cpu-estructuras.h"

// Librerias de externas:
#include <utils/include/socket.h>

/**
* @brief Crea el servidor de dispatch para la CPU.
*/
void crear_servidor_dispatch(void);

/**
* @brief Crea el servidor de interrupt para la CPU.
*/
void crear_servidor_interrupt(void);

/**
* @brief Genera una conexión con la memoria.
*/
void generar_conexion_con_memoria(void);

#endif // CPU_CPU_CONEXIONES_H