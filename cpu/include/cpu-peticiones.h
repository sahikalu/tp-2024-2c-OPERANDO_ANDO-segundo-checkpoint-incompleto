#ifndef CPU_CPU_PETICIONES_H
#define CPU_CPU_PETICIONES_H

// Librerias internas:
#include "cpu-estructuras.h"

// Librerias de externas:
#include <utils/include/peticiones.h>
#include <utils/include/protocolo.h>

/**
* @brief Escucha las conexiones entrantes.
*/
void escuchar_conexiones(void);

/**
* @brief Escucha las peticiones del servidor de dispatch.
*/
void escuchar_peticiones_de_dispatch(void);

/**
* @brief Escucha las peticiones del servidor de interrupt.
*/
void escuchar_peticiones_de_interrupt(void);

/**
* @brief Maneja una petición del servidor de dispatch.
* @param args Argumentos necesarios para manejar la petición.
*/
void manejar_peticion_dispatch(void *args);

#endif // CPU_CPU_PETICIONES_H