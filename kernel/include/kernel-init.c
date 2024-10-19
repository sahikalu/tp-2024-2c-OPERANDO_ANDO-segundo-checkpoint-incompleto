#ifndef KERNEL_KERNEL_INIT_H
#define KERNEL_KERNEL_INIT_H

// Librerias de internas:
#include "../include/kernel-estructuras.h"

// Librerias de externas:
#include <pthread.h>
#include <utils/include/logger.h>


/**
* @brief Inicia el kernel con los argumentos especificados.
* @param argc Número de argumentos.
* @param argv Arreglo de argumentos.
*/
void iniciar_kernel(int argc, char* argv[]);

/**
* @brief Inicializa los estados de los procesos.
*/
void inicializar_estados_procesos();

/**
* @brief Inicializa los semáforos necesarios para el kernel.
*/
void inicializar_semaforos();

/**
* @brief Inicializa el planificador con los argumentos especificados.
* @param argc Número de argumentos.
* @param argv Arreglo de argumentos.
*/
void inicializar_planificador(int argc, char* argv[]);

/**
* @brief Inicializa el hilo dispatcher.
*/
void inicializar_hilo_dispatcher();

#endif //KERNEL_KERNEL_INIT_H