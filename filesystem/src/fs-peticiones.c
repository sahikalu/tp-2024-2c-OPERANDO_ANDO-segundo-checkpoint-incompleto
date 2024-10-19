#include "../include/fs-peticiones.h"

void escuchar_peticiones_fs(void) {
    escuchar_peticiones_con_hilo(socket_servidor, peticiones_fs);
}

void peticiones_fs(void *args) {

    // Obtenemos el socket del cliente:
    int socket_cliente = (int) args;
    int execute = 1;

    // Manejamos la petición:
    while(execute) {

        // recibimos la operacion:
        op_code operacion = recibir_operacion(socket_cliente);

        // Manejamos la operación:
        switch(operacion) {
            case CREACION_PROCESO:
                manejar_creacion_proceso(socket_cliente);
                execute = 0;
                break;
        }
    }
}