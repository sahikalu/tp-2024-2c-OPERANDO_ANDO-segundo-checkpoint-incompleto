#include "../include/kernel-conexiones.h"

void generar_conexiones_con_cpu(void) {

    // Inicializo variables con parametros de la configuracion:
    char* puerto_dispatch = config_kernel->PUERTO_CPU_DISPATCH;
    char* puerto_interrupt = config_kernel->PUERTO_CPU_INT;
    char* ip_cpu = config_kernel->IP_CPU;

    // Creo la conexion con la CPU de dispatch:
    socket_cpu_dispatch = establecer_conexion("CPU_DISPATCH", ip_cpu, puerto_dispatch);
    
    // Creo la conexion con la CPU de interrupt:
    socket_cpu_interrupt = establecer_conexion("CPU_INTERRUPT", ip_cpu, puerto_interrupt);
}

void generar_conexion_con_memoria(void) {

    // Inicializo variables con parametros de la configuracion:
    char* puerto_memoria = config_kernel->PUERTO_MEMORIA;
    char* ip_memoria = config_kernel->IP_MEMORIA;

    // Creo la conexion con la memoria:
    socket_memoria = establecer_conexion("MEMORIA", ip_memoria, puerto_memoria);
}