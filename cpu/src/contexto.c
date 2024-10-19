#include "../include/contexto.h" 

ContextoEjecucion solicitarContextoEjecucion(int pid, int tid, int conexion_memoria) {
    // Log obligatorio: Solicitud de contexto de ejecución
    log_info(logger_cpu, "## TID: %d - Solicito Contexto Ejecución para PID: %d", tid, pid);

    // Estructura temporal para realizar la solicitud
    t_tabla_solicitud* solicitud = malloc(sizeof(t_tabla_solicitud));
    if (solicitud == NULL) {
        log_error(logger_cpu, "Error al asignar memoria para la solicitud del contexto\n");
        return contextoInvalido();  // Devolver un contexto inválido
    }

    solicitud->PID = pid;
    solicitud->TID = tid;

    // Serializar la solicitud
    t_paquete* paquete = crear_paquete(SOLICITUD_CONTEXTO);
    agregar_a_paquete(paquete, solicitud, sizeof(t_tabla_solicitud));

    // Enviar la solicitud al módulo de Memoria
    if (enviar_paquete(paquete, conexion_memoria) == -1) {
        log_error(logger_cpu, "PID: %d - TID: %d - Error al enviar solicitud de contexto a Memoria", pid, tid);
        free(solicitud);
        eliminar_paquete(paquete);
        return contextoInvalido();
    }

    // Recibir el contexto de la Memoria
    ContextoEjecucion contexto;
    int result = recv(conexion_memoria, &contexto, sizeof(ContextoEjecucion), MSG_WAITALL);

    // Validar recepción correcta
    if (result <= 0) {
        log_error(logger_cpu, "PID: %d - TID: %d - Error al recibir contexto de ejecución", pid, tid);
        free(solicitud);
        eliminar_paquete(paquete);
        return contextoInvalido();
    }

    // Verificar si el contexto es válido (dependiendo de tu lógica)
    if (!contextoValido(&contexto)) {
        log_error(logger_cpu, "PID: %d - TID: %d - Contexto de ejecución inválido", pid, tid);
        free(solicitud);
        eliminar_paquete(paquete);
        return contextoInvalido();
    }

    // Log indicando éxito
    log_info(logger_cpu, "## TID: %d - Contexto de Ejecución recibido correctamente", tid);

    free(solicitud);
    eliminar_paquete(paquete);

    return contexto;  // Devolver el contexto de ejecución completo
}


// ! actualizarContextoEjecucion(1, 1, &contexto, conexion_memoria);
void actualizarContextoEjecucion(int pid, int tid, ContextoEjecucion* contexto, int conexion_memoria) {
    // Log obligatorio: Actualización de contexto de ejecución
    log_info(logger_cpu, "## TID: %d - Actualizo Contexto Ejecución en Memoria para PID: %d", tid, pid);

    // Estructura para realizar la solicitud de actualización
    t_tabla_solicitud* solicitud = malloc(sizeof(t_tabla_solicitud));
    if (solicitud == NULL) {
        log_error(logger_cpu, "Error al asignar memoria para la actualización del contexto\n");
        return;
    }

    solicitud->PID = pid;
    solicitud->TID = tid;

    // Serializar la solicitud y el contexto
    t_paquete* paquete = crear_paquete(ACTUALIZACION_CONTEXTO);
    agregar_a_paquete(paquete, solicitud, sizeof(t_tabla_solicitud));
    agregar_a_paquete(paquete, contexto, sizeof(ContextoEjecucion));

    // Enviar el paquete al módulo de Memoria
    if (enviar_paquete(paquete, conexion_memoria) == -1) {
        log_error(logger_cpu, "PID: %d - TID: %d - Error al enviar actualización de contexto a Memoria", pid, tid);
        free(solicitud);
        eliminar_paquete(paquete);
        return;
    }

    // Recibir la confirmación de la actualización
    int confirmacion;
    int result = recv(conexion_memoria, &confirmacion, sizeof(int), MSG_WAITALL);

    if (result <= 0 || confirmacion != OK) {
        log_error(logger_cpu, "PID: %d - TID: %d - Error al actualizar el contexto en Memoria", pid, tid);
    } else {
        log_info(logger_cpu, "## TID: %d - Contexto de Ejecución actualizado correctamente en Memoria para PID: %d", tid, pid);
    }

    free(solicitud);
    eliminar_paquete(paquete);
}

void modificarcontexto (ContextoEjecucion* contexto, uint32_t PC, uint32_t AX, uint32_t BX, uint32_t CX, uint32_t DX, uint32_t EX, uint32_t FX, uint32_t GX, uint32_t HX, uint32_t base, uint32_t limite) {
    contexto->PC = PC;
    contexto->AX = AX;
    contexto->BX = BX;
    contexto->CX = CX;
    contexto->DX = DX;
    contexto->EX = EX;
    contexto->FX = FX;
    contexto->GX = GX;
    contexto->HX = HX;
    contexto->base = base;
    contexto->limite = limite;
}
// TODO para cuando se cree un nuevo proceso
ContextoEjecucion crearContextoEjecucion(uint32_t PC, uint32_t AX, uint32_t BX, uint32_t CX, uint32_t DX, uint32_t EX, uint32_t FX, uint32_t GX, uint32_t HX, uint32_t base, uint32_t limite) {
    ContextoEjecucion contexto;
    contexto.PC = PC;
    contexto.AX = AX;
    contexto.BX = BX;
    contexto.CX = CX;
    contexto.DX = DX;
    contexto.EX = EX;
    contexto.FX = FX;
    contexto.GX = GX;
    contexto.HX = HX;
    contexto.base = base;
    contexto.limite = limite;
    return contexto;
}