#include "../include/conexiones.h"

int iniciar_servidor_generico(char* nombre_servidor, char* ip, char* puerto) {
    
    // Creo el socket servidor:
    int socket_servidor = iniciar_servidor(nombre_servidor, ip, puerto);

    // Verifico si se pudo crear el servidor:
    if (!socket_servidor) {
        log_error(logger, "No se pudo crear el servidor de %s", nombre_servidor);
        exit(EXIT_FAILURE);
    }

    // Logueo la creación del servidor:
    log_info(logger, "Servidor de %s creado en %s:%s", nombre_servidor, ip, puerto);

    return socket_servidor;
}

int establecer_conexion(char* nombre_servicio, char* ip, char* puerto) {

    // Crear la conexión:
    int descriptor_conexion = crear_conexion(nombre_servicio, ip, puerto);

    // Verificar si se pudo crear la conexión:
    if (descriptor_conexion == -1) {
        log_error(logger, "No se pudo establecer la conexión con %s en %s:%s", nombre_servicio, ip, puerto);
        exit(EXIT_FAILURE);
    }

    // Realizar el handshake:
    generar_handshake(descriptor_conexion, nombre_servicio, ip, puerto);

    // Loguear la creación de la conexión:
    log_info(logger, "Conexión con %s establecida en %s:%s", nombre_servicio, ip, puerto);

    return descriptor_conexion;
}