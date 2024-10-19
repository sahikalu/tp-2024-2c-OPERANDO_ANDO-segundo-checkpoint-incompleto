#include "../include/kernel-syscalls.h"
#include "../include/kernel-estructuras.c"
#include "../include/kernel.c"
#include "../utils/src/logger.c"
#include "../memoria/src/memoria.c"
#include <commons/colections/list.h>
#include <stdlib.h>
#include <string.h>

// ! PROCESOS ------------------------------------------------------------------------------------------------------------------------------------------------------------

// esta syscall recibirá 3 parámetros de la CPU, el primero será el nombre del archivo de pseudocódigo que deberá ejecutar el proceso, el segundo parámetro es el tamaño del proceso en Memoria y el tercer parámetro es la prioridad del hilo main (TID 0). El Kernel creará un nuevo PCB y un TCB asociado con TID 0 y lo dejará en estado NEW.
void process_create(char* nombre_archivo, uint32_t tamano_proceso, uint32_t prioridad) {
    // * Creo el nuevo PCB
    t_pcb* nuevo_pcb = malloc(sizeof(t_pcb));
    nuevo_pcb->pid = pid_counter++;
    nuevo_pcb->tamano = tamano_proceso;
    nuevo_pcb->estado = NEW;
    nuevo_pcb->hilos = list_create();

    // * Creo el TCB asociado con TID 0
    t_tcb* tcb_main = malloc(sizeof(t_tcb));
    tcb_main->tid = 0;
    tcb_main->prioridad = prioridad;
    tcb_main->contexto = crearContextoEjecucion(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, tamano_proceso);

    // * Agrego el TCB al PCB
    list_add(nuevo_pcb->hilos, tcb_main);

    // * Agrego el PCB a la cola de NEW
    list_add(queue_new, nuevo_pcb);

    // * Loggeo
    log_info(logger, "Proceso creado: PID %d, TID %d, Tamaño %d, Prioridad %d", nuevo_pcb->pid, tcb_main->tid, tamano_proceso, prioridad);
}

// esta syscall finalizará el PCB correspondiente al TCB que ejecutó la instrucción, enviando todos sus TCBs asociados a la cola de EXIT. Esta instrucción sólo será llamada por el TID 0 del proceso y le deberá indicar a la memoria la finalización de dicho proceso.
void process_exit(uint32_t pid) {
    // * Busco el PCB en las colas de estados
    t_pcb* pcb = buscar_pcb(pid);

    if (pcb == NULL) {
        // * Loggeo el error
        log_error(logger, "No se encontró el proceso cuyo PID es: %d", pid);
        return;
    }

    // * Muevo todos los TCBs asociados a la cola de EXIT
    for (int i = 0; i < list_size(pcb->hilos); i++) {
        t_tcb* tcb = list_get(pcb->hilos, i);
        list_add(queue_exit, tcb);
    }

    // * Remuevo el PCB de su cola actual y libero memoria
    remover_pcb_de_cola(pcb);
    free(pcb);

    // * Notifico a la memoria la finalización del proceso
    notificar_memoria_fin_proceso(pid);

    // * Loggeo el exito
    log_info(logger, "Finalizó el proceso cuyo PID es: %d", pid);
}

// ! HILOS ------------------------------------------------------------------------------------------------------------------------------------------------------------

// esta syscall recibirá como parámetro de la CPU el nombre del archivo de pseudocódigo que deberá ejecutar el hilo a crear y su prioridad. Al momento de crear el nuevo hilo, deberá generar el nuevo TCB con un TID autoincremental y poner al mismo en el estado READY.
void thread_create(char* nombre_archivo, uint32_t prioridad) {
    // * Creo nuevo TCB
    t_tcb* nuevo_tcb = malloc(sizeof(t_tcb));
    nuevo_tcb->tid = tid_counter++;
    nuevo_tcb->prioridad = prioridad;
    nuevo_tcb->contexto = crearContextoEjecucion(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    // * Agrego TCB a la cola de READY
    list_add(queue_ready, nuevo_tcb);

    // * Loggeo el exito
    log_info(logger, "Se creo el hilo cuyo TID es: %d, con prioridad %d", nuevo_tcb->tid, nuevo_tcb->prioridad);
}

// esta syscall recibe como parámetro un TID, mueve el hilo que la invocó al estado BLOCK hasta que el TID pasado por parámetro finalice. En caso de que el TID pasado por parámetro no exista o ya haya finalizado, esta syscall no hace nada y el hilo que la invocó continuará su ejecución.
void thread_join(uint32_t tid) {
    // * Busco el TCB en las colas de estados
    t_tcb* tcb = buscar_tcb(tid);
    if (esta_vacio_o_terminado(tcb)) {
        // * Loggeo el error
        log_info(logger,  "No se encontró o ya finalizó el hilo cuyo TID es: %d", tid);
        return;
    }

    // * Muevo el hilo que invocó a BLOCK
    t_tcb* tcb_invocador = obtener_tcb_actual(tid);
    tcb_invocador->estado = BLOCK;
    list_add(queue_block, tcb_invocador);

    // * Loggeo el exito
    log_info(logger, "Se creo el hilo y espera al fin del hilo cuyo TID es: %d", tid);
}

// esta syscall recibe como parámetro un TID con el objetivo de finalizarlo pasando al mismo al estado EXIT. Se deberá indicar a la Memoria la finalización de dicho hilo. En caso de que el TID pasado por parámetro no exista o ya haya finalizado, esta syscall no hace nada. Finalmente, el hilo que la invocó continuará su ejecución.
void thread_cancel(uint32_t tid) {
    // * Busco el TCB en las colas de estados
    t_tcb* tcb = buscar_tcb(tid);
    if (esta_vacio_o_terminado(tcb)) {
        // * Loggeo el error
        log_info(logger, "Hilo no encontrado o ya finalizado: TID %d", tid);
        return;
    }

    // * Muevo el TCB a la cola de EXIT
    tcb->estado = EXIT;
    list_add(queue_exit, tcb);

    // * Notifico a la memoria la finalización del hilo
    notificar_memoria_fin_hilo(tid);

    // * Loggeo el exito
    log_info(logger, "Finalizó el hilo cuyo TID es: %d", tid);
}

//  esta syscall finaliza al hilo que lo invocó, pasando el mismo al estado EXIT. Se deberá indicar a la Memoria la finalización de dicho hilo.
void thread_exit(uint32_t tid) {
    // * Obtengo el TCB actual
    t_tcb* tcb_actual = obtener_tcb_actual(tid);

    // * Muevo el TCB a la cola de EXIT
    tcb_actual->estado = EXIT;
    list_add(queue_exit, tcb_actual);

    // * Notifico a la memoria la finalización del hilo
    notificar_memoria_fin_hilo(tcb_actual->tid);

    // * Loggeo el exito
    log_info(logger, "Finalizó el hilo cuyo TID es: %d", tcb_actual->tid);
}

// ! MUTEX ------------------------------------------------------------------------------------------------------------------------------------------------------------

//  crea un nuevo mutex para el proceso sin asignar a ningún hilo.
void mutex_create(uint32_t mutex_id) {
    // * Creo nuevo mutex
    t_mutex* nuevo_mutex = malloc(sizeof(t_mutex));
    nuevo_mutex->id = mutex_id;
    nuevo_mutex->estado = LIBRE;
    nuevo_mutex->cola_bloqueados = list_create();

    // * Agrego el mutex a la lista de mutexes
    list_add(lista_mutexes, nuevo_mutex);

    // * Loggeo el exito
    log_info(logger, "Se creo el mutex cuyo ID es: %d", mutex_id);
}

//  se deberá verificar primero que exista el mutex solicitado y en caso de que exista y el mismo no se encuentre tomado se deberá asignar dicho mutex al hilo correspondiente. En caso de que el mutex se encuentre tomado, el hilo que realizó MUTEX_LOCK se bloqueará en la cola de bloqueados correspondiente a dicho mutex.
void mutex_lock(uint32_t mutex_id) {
    // * Busco el mutex en la lista de mutex
    t_mutex* mutex = buscar_mutex(mutex_id);
    if (mutex == NULL) {
        // * Loggeo el error
        log_error(logger, "No se enconto el mutex cuyo ID es: %d", mutex_id);
        return;
    }

    // * Verifico si el mutex está libre
    if (mutex->estado == LIBRE) {
        // * Asigno el mutex al hilo actual
        t_tcb* tcb_actual = obtener_tcb_actual(mutex->hilo_asignado);
        mutex->estado = OCUPADO;
        mutex->hilo_asignado = tcb_actual;

        // * Loggeo el exito
        log_info(logger, "Se asignó el mutex cuyo ID es:  %d al hilo cuyo TID es: %d", mutex_id, tcb_actual->tid);
    } else {
        // * Bloqueo el hilo actual en la cola del mutex
        t_tcb* tcb_actual = obtener_tcb_actual(mutex->hilo_asignado);
        tcb_actual->estado = BLOCK;
        list_add(mutex->cola_bloqueados, tcb_actual);
        list_add(queue_block, tcb_actual);

        // * Loggeo el exito
        log_info(logger, "Se bloqueó el mutex cuyo ID es:  %d perteneciente al hilo cuyo TID es: %d", mutex_id, tcb_actual->tid);
    }
}

// se deberá verificar primero que exista el mutex solicitado y esté tomado por el hilo que realizó la syscall. En caso de que corresponda, se deberá desbloquear al primer hilo de la cola de bloqueados de ese mutex y le asignará el mutex al hilo recién desbloqueado. Una vez hecho esto, se devuelve la ejecución al hilo que realizó la syscall MUTEX_UNLOCK. En caso de que el hilo que realiza la syscall no tenga asignado el mutex, no realizará ningún desbloqueo.
void mutex_unlock(uint32_t mutex_id) {
    // * Busco el mutex en la lista de mutexes
    t_mutex* mutex = buscar_mutex(mutex_id);
    if (mutex == NULL) {
        // * Loggeo el error
        log_error(logger, "No se enconto el mutex cuyo ID es: %d", mutex_id);
        return;
    }

    // * Verifico si el mutex está asignado al hilo actual
    t_tcb* tcb_actual = obtener_tcb_actual(mutex->hilo_asignado);
    if (mutex->hilo_asignado != tcb_actual) {
        // * Loggeo el error
        log_error(logger, "No se asigno el mutex cuyo ID es: %d perteneciente al hilo cuyo TID es: %d", mutex_id, tcb_actual->tid);
        return;
    }

    // * Desbloqueo al primer hilo de la cola de bloqueados del mutex
    if (!list_is_empty(mutex->cola_bloqueados)) {
        t_tcb* tcb_desbloqueado = list_remove(mutex->cola_bloqueados, 0);
        tcb_desbloqueado->estado = READY;
        list_add(queue_ready, tcb_desbloqueado);
        mutex->hilo_asignado = tcb_desbloqueado;

        // * Loggeo el exito
        log_info(logger, "Se re-asigno el mutex cuyo ID es: %d al hilo cuyo TID es: %d", mutex_id, tcb_desbloqueado->tid);
    } else {
        mutex->estado = LIBRE;
        mutex->hilo_asignado = NULL;

        // * Loggeo el exito
        log_info(logger, "Se liberó el mutex cuyo ID es: %d", mutex_id);
    }
}

// ! AUX ------------------------------------------------------------------------------------------------------------------------------------------------------------

t_pcb* buscar_pcb(uint32_t pid) {
    t_pcb* pcb = NULL;
    
    // * Busco en la cola de NEW, READY y EXIT
    pcb = buscar_pcb_en_lista(pid, queue_new);
    pcb = buscar_pcb_en_lista(pid, queue_ready);
    pcb = buscar_pcb_en_lista(pid, queue_exit);
    
    return pcb;
}

t_pcb* buscar_pcb_en_lista(uint32_t pid, t_list *lista) {
    // * Recorro la lista buscando el pcb
    for (int i = 0; i < list_size(lista); i++) {
        t_pcb* pcb = list_get(lista, i);

        if (pcb->pid == pid) {
            return pcb;
        }
    }
}

t_tcb* buscar_tcb(uint32_t tid) {
    t_tcb* tcb = NULL;
    
    // * Busco en la cola de NEW, READY y EXIT
    tcb = buscar_tcb_en_lista(pid, queue_new);
    tcb = buscar_tcb_en_lista(pid, queue_ready);
    tcb = buscar_tcb_en_lista(pid, queue_exit);
    
    return tcb;
}

t_pcb* buscar_tcb_en_lista(uint32_t tid, t_list *lista) {
    // * Recorro la lista buscando el tcb
    for (int i = 0; i < list_size(lista); i++) {
        t_tcb* tcb = list_get(lista, i);
        if (tcb->tid == tid) {
            return tcb;
        }
    }
}

bool esta_vacio_o_terminado(t_tcb* tcb) {
    // * Verifico si el TCB esta vacío o si ya finalizo
    return tcb == NULL || tcb->estado == EXIT;
}

t_mutex* buscar_mutex(uint32_t mutex_id) {
    // * Busco en la lista de mutexs
    for (int i = 0; i < list_size(lista_mutexes); i++) {
        t_mutex* mutex = list_get(lista_mutexes, i);
        if (mutex->id == mutex_id) {
            return mutex;
        }
    }
    return NULL;
}

void remover_pcb_de_cola(t_pcb* pcb) {
    // * Remuevo de la cola de NEW, READY y EXIT
    remover_pcb_de_cola(pcb, queue_new);
    remover_pcb_de_cola(pcb, queue_ready);
    remover_pcb_de_cola(pcb, queue_ready);
}

void remover_pcb_de_cola(t_pcb* pcb, t_list* lista) {
    // * Remuevo el PCB de la lista
    list_remove_by_condition(lista, (bool (*)(void *)) (pcb->pid == ((t_pcb*) pcb)->pid));
}

void notificar_memoria_fin_proceso(uint32_t pid) {
    // TODO
}

void notificar_memoria_fin_hilo(uint32_t tid) {
    // TODO
}

t_tcb* obtener_tcb_actual(tid) {
    return buscar_tcb(tid);
}