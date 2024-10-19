#include "..include/kernel-init.h"

void iniciar_kernel(int argc, char* argv[]) {

    // Inicializo las variables globales:
    inicializar_estados_procesos();
    inicializar_semaforos();

    // Inicializamos el planificador y el dispatcher:
    inicializar_planificador();
    inicializar_hilo_dispatcher();
}

void inicializar_estados_procesos() {
    queue_new = list_create();
    queue_ready = list_create();
    queue_exit = list_create();
}

void inicializar_semaforos() {
    
}

void inicializar_planificador(int argc, char* argv[]) {
    pthread_t planificador_corto_plazo;
    pthread_t planificador_largo_plazo;

    // Inicializo el hilos de los planificadores:
    pthread_create(&planificador_corto_plazo, NULL, (void*)planificador_corto_plazo, NULL);
    pthread_create(&planificador_largo_plazo, NULL, (void*)planificador_largo_plazo, NULL);

    // Esperamos a que terminen los hilos de planificación:
    pthread_detach(planificador_corto_plazo);
    pthread_detach(planificador_largo_plazo);
}

void inicializar_hilo_dispatcher() {
    pthread_t dispatcher;

    // Inicializo el hilo del dispatcher:
    pthread_create(&dispatcher, NULL, (void*)dispatcher, NULL);

    // Esperamos a que termine el hilo del dispatcher:
    pthread_detach(dispatcher);
}
