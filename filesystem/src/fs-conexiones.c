#include "../include/fs-conexiones.h"

void crear_servidor_fs(void) {
    
    // Inicializo variables con parametros de la configuracion:
    char *puerto_escucha = config_fs->puerto_escucha;
    char *ip_generica = ""

    // Creo el socket servidor:
    socket_servidor = iniciar_servidor_generico("FS", ip_generica, puerto_escucha);
}