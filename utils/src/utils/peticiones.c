#include "../include/peticiones.h"

void escuchar_peticiones_sin_hilo(int socket_servidor, void *manejar_peticion(void *args)) {
    
    // Aceptamos una conexión:
    int socket_cliente = aceptar_conexion(socket_servidor);

    // Si hubo un error:
    if(socket_cliente == -1) {
        log_error(logger, "Error al aceptar una conexión.");
        exit(EXIT_FAILURE);
    } else
        manejar_peticion((void*) socket_cliente);
}

void escuchar_peticiones_con_hilo(int socket_servidor, void *manejar_peticion(void *args)) {

    // Variable para el socket del cliente:
    int socket_cliente;

    while(1) {

        // Aceptamos una conexión:
        socket_cliente = aceptar_conexion(socket_servidor);

        // Si hubo un error:
        if(socket_cliente == -1) {
            log_error(logger, "Error al aceptar una conexión.");
            exit(EXIT_FAILURE);
        } else {
            
            // Creamos un hilo para manejar la petición:
            pthread_t hilo;
            pthread_create(&hilo, NULL, (void*) manejar_peticion, (void*) socket_cliente);
            pthread_detach(hilo);
        }
    }
}


