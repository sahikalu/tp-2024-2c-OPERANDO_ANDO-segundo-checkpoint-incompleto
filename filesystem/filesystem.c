#include "../include/filesystem.h"

int main(int argc, char* argv[]) {

    // Inicialización:
    cargar_configuraciones_de_fs();
    logger = log_create("memoria.log", "MEMORIA", true, config_memoria->log_level);

    // Servidor de memoria:
    crear_servidor_fs();
    escuchar_peticiones_fs();

    return 0;
}
