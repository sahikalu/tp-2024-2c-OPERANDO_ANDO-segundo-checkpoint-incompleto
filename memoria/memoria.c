#include "../include/memoria.h"

int main(int argc, char* argv[]) {

    // Inicialización:
    cargar_configuraciones_de_memoria();
    logger = log_create("memoria.log", "MEMORIA", true, config_memoria->log_level);

    // Servidor de memoria:
    crear_servidor_memoria();
    escuchar_peticiones_memoria();

    return 0;
}
