#ifndef UTILS_CONEXIONES_H
#define UTILS_CONEXIONES_H

// Librerias internas:
#include "logger.h"
#include "socket.h"

/**
* @brief Inicia un servidor genérico y maneja errores si no se puede crear.
* @param nombre_servidor Nombre del servidor.
* @param ip Dirección IP del servidor.
* @param puerto Puerto del servidor.
* @return Devuelve el socket del servidor creado.
*/
int iniciar_servidor_generico(char* nombre_servidor, char* ip, char* puerto);

/**
* @brief Establece una conexión genérica y maneja errores si no se puede crear.
* @param nombre_servicio Nombre del servicio.
* @param ip Dirección IP del servicio.
* @param puerto Puerto del servicio.
* @return Devuelve el descriptor de la conexión creada.
*/
int establecer_conexion(char* nombre_servicio, char* ip, char* puerto);

#endif //UTILS_CONEXIONES_H