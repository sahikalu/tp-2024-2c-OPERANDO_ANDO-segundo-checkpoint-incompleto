#ifndef UTILS_PAQUETE_H
#define UTILS_PAQUETE_H

// Librerias internas:
#include "estructuras.h"

typedef struct {
	int size;
	void* stream;
} t_buffer;

typedef struct {
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

/**
* @brief Crea un paquete con la operación especificada.
* @param operacion Código de operación para el paquete.
* @return Devuelve un puntero al paquete creado.
*/
t_paquete* crear_paquete(op_code operacion);

/**
* @brief Crea un buffer para el paquete especificado.
* @param paquete Puntero al paquete para el cual se creará el buffer.
*/
void crear_buffer(t_paquete* paquete);

/**
* @brief Agrega un valor al paquete.
* @param paquete Puntero al paquete al cual se agregará el valor.
* @param valor Puntero al valor que se agregará al paquete.
* @param tamanio Tamaño del valor que se agregará al paquete.
*/
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);

/**
* @brief Envía un paquete al cliente especificado.
* @param paquete Puntero al paquete que se enviará.
* @param socket_cliente Socket del cliente al cual se enviará el paquete.
*/
void enviar_paquete(t_paquete* paquete, int socket_cliente);

/**
* @brief Elimina un paquete y libera la memoria asociada.
* @param paquete Puntero al paquete que se eliminará.
*/
void eliminar_paquete(t_paquete* paquete);

/**
* @brief Recibe un buffer desde el socket especificado.
* @param size Puntero a un entero donde se almacenará el tamaño del buffer recibido.
* @param socket_cliente Socket desde el cual se recibirá el buffer.
* @return Devuelve un puntero al buffer recibido.
*/
void* recibir_buffer(int* size, int socket_cliente);