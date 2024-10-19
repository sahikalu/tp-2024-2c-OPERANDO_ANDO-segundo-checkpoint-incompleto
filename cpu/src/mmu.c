#include "../include/mmu.h"

//h

uint32_t calcular_direccion_fisica(uint32_t base, uint32_t desplazamiento, uint32_t limite) {
    // Validar que la dirección calculada no exceda el límite
    if (base + desplazamiento > limite) {
        log_error(logger_cpu, "Segmentation Fault: desplazamiento fuera del límite.");
        return SEGMENTATION_FAULT;  // Retorna un valor especial en caso de segmentation fault
    }
    return base + desplazamiento;
}

void manejar_solicitud_direccion_fisica(int conexion_memoria) {
    // Recibir solicitud de dirección lógica
    t_direccion_solicitud solicitud;
    int result = recv(conexion_memoria, &solicitud, sizeof(t_direccion_solicitud), MSG_WAITALL);
    if (result <= 0) {
        log_error(logger_cpu, "Error al recibir solicitud de dirección física");
        return;
    }

    // Calcular dirección física
    uint32_t direccion_fisica = calcular_direccion_fisica(solicitud.base, solicitud.desplazamiento, solicitud.limite);
    
    // Verificar si ocurrió un segmentation fault
    if (direccion_fisica == SEGMENTATION_FAULT) {
        // Enviar señal de segmentation fault a la memoria
        uint32_t status = SEGMENTATION_FAULT;
        send(conexion_memoria, &status, sizeof(uint32_t), 0);
        // Actualizar el contexto de ejecución en Memoria
        ContextoEjecucion contexto = contextoInvalido();
        actualizarContextoEjecucion(solicitud.PID, solicitud.TID, &contexto, conexion_memoria);
        // Devolver el TID al Kernel con motivo de Segmentation Fault
        send(conexion_kernel, &solicitud.TID, sizeof(int), 0);
        return;
    }

    // Enviar dirección física a la memoria
    send(conexion_memoria, &direccion_fisica, sizeof(uint32_t), 0);
}