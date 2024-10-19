#ifndef UTILS_PROTOCOLO_H
#define UTILS_PROTOCOLO_H

// Librerias internas:
#include "estructuras.h"

/**
* @brief Genera un handshake con el servidor especificado.
* @param socket Socket a través del cual se realizará el handshake.
* @param server_name Nombre del servidor con el que se realizará el handshake.
* @param ip Dirección IP del servidor.
* @param puerto Puerto del servidor.
*/
void generar_handshake(int socket, char *server_name, char *ip, char *puerto);

/**
* @brief Recibe un handshake desde el socket especificado.
* @param socket Socket desde el cual se recibirá el handshake.
*/
void recibir_handshake(int socket);

/**
* @brief Parsea una cadena desde el buffer especificado.
* @param buffer Puntero al buffer desde el cual se parseará la cadena.
* @param desplazamiento Puntero a un entero que indica el desplazamiento actual en el buffer.
* @return Devuelve un puntero a la cadena parseada.
*/
char *parsear_string(void *buffer, int *desplazamiento);

#endif // UTILS_PROTOCOLO_H