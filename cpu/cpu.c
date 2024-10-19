#include "../include/cpu.h"

int main(int argc, char* argv[]) {
    
    // Inicializo las configuraciones de CPU:
    cargar_configuraciones_de_cpu();
    logger = log_create("cpu.log", "CPU", true, config_cpu->log_level);

    // Nos conectamos con la memoria:
    generar_conexion_con_memoria();
    
    // Creamos los servidores de CPU:
    crear_servidores_cpu();

    // Escuchamos las conexiones:
    escuchar_conexiones();

    return 0;
}
