#include "./include/cpu-peticiones.h"

void escuchar_conexiones(void) {
    escuchar_peticiones_de_interrupt();
    escuchar_peticiones_de_dispatch();
}

void escuchar_peticiones_de_dispatch(void) {
    escuchar_peticiones_sin_hilo(socket_servidor_dispatch, manejar_peticion_dispatch);
}

void escuchar_peticiones_de_interrupt(void) {
    pthread_t hilo_interrupt;
    pthread_create(&hilo_interrupt, NULL, escuchar_peticiones_sin_hilo, (void *) socket_servidor_interrupt);
}

void manejar_peticion_dispatch(void *args) {
    // Inicializo variables:
    int socket_cliente = (int) args;

    // Recibo el handshake del cliente:
    recibir_handshake(socket_cliente);

    while(1) {  
        // Iniciziamos el ciclo de instrucciones:
        recibir_contexto_proceso(socket_cliente);
        iniciar_ciclo_de_instrucciones(); 
    }
}