#ifndef KERNEL_KERNEL_CONEXIONES_H
#define KERNEL_KERNEL_CONEXIONES_H

// Librerias de internas:
#include "../include/kernel-estructuras.h"
#include "../include/kernel-config.h"

// Librerias de externas:
#include <utils/include/logger.h>

/**
* @afn generar_conexiones_con_cpu()
* @brief Genera las conexiones con las CPU.
*/
void generar_conexiones_con_cpu();

/**
* @afn generar_conexion_con_memoria()
* @brief Genera la conexion con la memoria.
*/
void generar_conexion_con_memoria();

#endif // KERNEL_KERNEL_CONEXIONES_H