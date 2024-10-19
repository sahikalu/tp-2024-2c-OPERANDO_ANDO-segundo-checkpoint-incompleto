#include "./include/cpu-ciclo-instrucciones.h"

void iniciar_ciclo_instrucciones() {
    while(exec_cicle) {
        // Recibo la instruccion a ejecutar:
        t_instruccion *instruccion = fetch_instrucciones(pid, tid);    

        // Ejecutamos la instruccion, liberamos la memoria y verificamos si hay que finalizar el ciclo:
        ejecutar_instruccion(instruccion);
        free(instruccion);
        hay_que_finalizar_ciclo();
    }
}

void fetch_instrucciones() {
    // Inicializo variables:
    t_instruccion *instruccion = malloc(sizeof(t_instruccion));
    instruccion->operandos = list_create();

    // Envio la solicitud de instruccion:
    enviar_solicitud_instruccion(socket_memoria, pid, tid);

    // Recibo la instruccion:
    op_code operacion = recibir_operacion(socket_servidor_dispatch);
    instruccion->operandos = recibir_operandos(socket_servidor_dispatch);
}

void ejecutar_instruccion(t_instruccion) {
    // Inicializo variables:
    code_instruccion instruccion = instruccion->instruccion;

    // Ejecuto la instruccion:
    switch(instruccion) {
        case SET:

    }


}