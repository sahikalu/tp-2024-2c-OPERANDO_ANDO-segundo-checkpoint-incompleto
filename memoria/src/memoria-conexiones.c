#include "../include/memoria-conexiones.h"

void crear_servidor_memoria(void) {

    // Inicializo variables con parametros de la configuracion:
    char *puerto_escucha = config_memoria->puerto_escucha;
    char *ip_generica = "127.0.0.1";

    // Creo el socket servidor:
    socket_servidor = iniciar_servidor_generico("MEMORIA", ip_generica, puerto_escucha);
}

void generar_conexion_con_fs(void) {

    // Inicializo variables con parametros de la configuracion:
    char* puerto_fs = config_kernel->PUERTO_FILESYSTEM;
    char* ip_fs = config_kernel->IP_FILESYSTEM;

    // Creo la conexion con el filesystem:
    socket_filesystem = establecer_conexion = establecer_conexion("FILESYSTEM", ip_fs, puerto_fs);
}