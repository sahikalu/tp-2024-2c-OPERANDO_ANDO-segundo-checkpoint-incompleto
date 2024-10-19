#ifndef UTILS_SOCKET_H_
#define UTILS_SOCKET_H_

// Incluimos las librerias necesarias externas:
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

// Incluimos las librerias propias:
#include <utils/include/logger.h>

/**
* @afn int crear_conexion(const char *server_name, char *ip, char *puerto)
* @brief Crea una conexión con el servidor.
* @param server_name Nombre del servidor
* @param ip IP del servidor
* @param puerto Puerto del servidor
* @return Devuelve el socket del servidor.
*/
int crear_conexion(const char *server_name, char *ip, char *puerto);

/**
 * @fn int iniciar_servidor( const char *name, char *ip, char *puerto)
 * @brief Inicia un servidor en el puerto especificado.
 * @param logger Logger para loguear mensajes.
 * @param ip IP en la que se va a iniciar el servidor.   
 * @param puerto Puerto en el que se va a iniciar el servidor. 
 * @return Devuelve el socket del servidor.
*/
int iniciar_servidor( const char *name, char *ip, char *puerto);

/**
 * @fn int esperar_cliente(const char *name, int socket_servidor)
 * @brief Espera a que un cliente se conecte al servidor.
 * @param name Nombre del servidor.
 * @param socket_servidor Socket del servidor.
 * @return Devuelve el socket del cliente.
*/
int esperar_cliente(const char* name, int socket_servidor);


#endif
