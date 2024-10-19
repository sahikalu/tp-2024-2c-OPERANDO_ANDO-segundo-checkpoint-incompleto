#include "../include/kernel.h"

int main(int argc, char* argv[]) {

    // Inicializo las configuraciones del Kernel:
    cargar_configuraciones_del_kernel();
    logger = log_create("kernel.log", "Kernel", 1, config_kernel->log_level);

    // Iniciar conexiones con CPU:
    generar_conexiones_con_cpu();

    // Iniciamos el modulo de planificacion:
    iniciar_kernel(argc, argv);

    return 0;
}

