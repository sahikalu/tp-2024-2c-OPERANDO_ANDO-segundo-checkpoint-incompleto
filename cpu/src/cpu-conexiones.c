#include "./include/cpu-conexiones.h"

void crear_servidores_cpu(void) {
    crear_servidor_dispatch();
    crear_servidor_interrupt();
}

void crear_servidor_dispatch(void) {

    // Inicializo variables con parametros de la configuracion:
    char *puerto_escucha = config_cpu->puerto_dispatch;
    char *ip_generica = "";

    // Creo el socket servidor:
    socket_servidor_dispatch = iniciar_servidor_generico("DISPATCH", ip_generica, puerto_escucha);
}

void crear_servidor_interrupt(void) {

    // Inicializo variables con parametros de la configuracion:
    char *puerto_escucha = config_cpu->puerto_interrupt;
    char *ip_generica = "";

    // Creo el socket servidor:
    socket_servidor_interrupt = iniciar_servidor_generico("INTERRUPT", ip_generica, puerto_escucha);
}

void generar_conexion_con_memoria(void) {

    // Inicializo variables con parametros de la configuracion:
    char* puerto_memoria = config_cpu->puerto_memoria;
    char* ip_memoria = config_cpu->ip_memoria;

    // Creo la conexion con la memoria:
    socket_memoria = establecer_conexion("MEMORIA", ip_memoria, puerto_memoria);
}