#include "../include/ram.h"

void manejar_solicitud_direccion_fisica(int conexion_cpu) {
    // Recibir solicitud de dirección lógica
    t_direccion_solicitud solicitud;
    int result = recv(conexion_cpu, &solicitud, sizeof(t_direccion_solicitud), MSG_WAITALL);
    if (result <= 0) {
        log_error(logger_memoria, "Error al recibir solicitud de dirección física");
        return;
    }

    // Buscar el proceso en la tabla de memoria
    ProcesoMemoria* proceso = buscar_proceso(solicitud.PID);
    if (proceso == NULL) {
        log_error(logger_memoria, "Proceso no encontrado para PID: %d", solicitud.PID);
        return;
    }

    // Recibir la dirección física calculada por la CPU
    uint32_t direccion_fisica;
    result = recv(conexion_cpu, &direccion_fisica, sizeof(uint32_t), MSG_WAITALL);
    if (result <= 0) {
        log_error(logger_memoria, "Error al recibir dirección física calculada por la CPU");
        return;
    }

    // Verificar si ocurrió un segmentation fault
    if (direccion_fisica == SEGMENTATION_FAULT || direccion_fisica >= proceso->limite) {
        log_error(logger_memoria, "Segmentation Fault: dirección física fuera del límite.");

        // Actualizar el contexto de ejecución en Memoria
        ContextoEjecucion contexto = contextoInvalido();
        actualizarContextoEjecucion(solicitud.PID, solicitud.TID, &contexto, conexion_memoria);

        // Devolver el TID al Kernel con motivo de Segmentation Fault
        uint32_t status = SEGMENTATION_FAULT;
        send(conexion_cpu, &status, sizeof(uint32_t), 0);
        send(conexion_kernel, &solicitud.TID, sizeof(int), 0);
        return;
    }

    // Enviar dirección física a la CPU
    send(conexion_cpu, &direccion_fisica, sizeof(uint32_t), 0);
}