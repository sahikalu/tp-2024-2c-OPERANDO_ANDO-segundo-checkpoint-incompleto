#ifndef KERNEL_SYSCALL_H
#define KERNEL_SYSCALL_H

#include <stdint.h>
#include "kernel-estructuras.h"
#include <commons/colections/list.h>

// ! PROCESOS ------------------------------------------------------------------------------------------------------------------------------------------------------------

void process_create(char* nombre_archivo, uint32_t tamano_proceso, uint32_t prioridad);
void process_exit(uint32_t pid);

// ! HILOS ------------------------------------------------------------------------------------------------------------------------------------------------------------
void thread_create(char* nombre_archivo, uint32_t prioridad);
void thread_join(uint32_t tid);
void thread_cancel(uint32_t tid);
void thread_exit();

// ! MUTEX ------------------------------------------------------------------------------------------------------------------------------------------------------------
void mutex_create(uint32_t mutex_id);
void mutex_lock(uint32_t mutex_id);
void mutex_unlock(uint32_t mutex_id);

// ! AUX ------------------------------------------------------------------------------------------------------------------------------------------------------------
t_pcb* buscar_pcb(uint32_t pid);
t_tcb* buscar_tcb(uint32_t tid);
t_mutex* buscar_mutex(uint32_t mutex_id);
void remover_pcb_de_cola(t_pcb* pcb);
void notificar_memoria_fin_proceso(uint32_t pid);
void notificar_memoria_fin_hilo(uint32_t tid);
t_tcb* obtener_tcb_actual();

#endif 