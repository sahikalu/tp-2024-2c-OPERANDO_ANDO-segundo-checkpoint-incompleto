#include "../include/contexto.h" 

ProcesoMemoria* buscar_proceso(int pid) {
    for (int i = 0; i < list_size(lista_pcbs); i++) {
        ProcesoMemoria* proceso = list_get(lista_pcbs, i);
        if (proceso->PID == pid) {
            return proceso;
        }
    }
    return NULL;
}

TCBMemoria* buscar_hilo_en_proceso(ProcesoMemoria* proceso, int tid) {
    for (int i = 0; i < list_size(proceso->hilos); i++) {
        TCBMemoria* tcb = list_get(proceso->hilos, i);
        if (tcb->TID == tid) {
            return tcb;
        }
    }
    return NULL;
}

void manejar_solicitud_contexto(int conexion_cpu) {
    // Recibir la solicitud
    t_tabla_solicitud solicitud;
    int result = recv(conexion_cpu, &solicitud, sizeof(t_tabla_solicitud), MSG_WAITALL);
    if (result <= 0) {
        log_error(logger_memoria, "Error al recibir solicitud de contexto de ejecución");
        return;
    }

    // Log de la solicitud recibida
    log_info(logger_memoria, "## TID: %d - Solicitud de Contexto Ejecución recibida para PID: %d", solicitud.TID, solicitud.PID);

    // Obtener el contexto de ejecución (esto depende de tu lógica de negocio)
    ContextoEjecucion contexto = obtener_contexto_ejecucion(solicitud.PID, solicitud.TID);

    // Enviar el contexto de ejecución de vuelta a la CPU
    if (send(conexion_cpu, &contexto, sizeof(ContextoEjecucion), 0) == -1) {
        log_error(logger_memoria, "Error al enviar contexto de ejecución a la CPU");
    } else {
        log_info(logger_memoria, "## TID: %d - Contexto de Ejecución enviado correctamente para PID: %d", solicitud.TID, solicitud.PID);
    }
}

ContextoEjecucion solicitarContextoMemoria(int pid, int tid) {
    // Buscar el proceso en la tabla de procesos
    ProcesoMemoria* proceso = buscar_proceso(pid);
    
    if (proceso == NULL) {
        log_error(logger_memoria, "## Contexto Solicitado - (PID:TID) - (%d:%d) - No se encontró el proceso en Memoria", pid, tid);
        return contextoInvalido();
    }

    // Buscar el TCB del hilo dentro del proceso
    TCBMemoria* tcb = buscar_hilo_en_proceso(proceso, tid);
    
    if (tcb == NULL) {
        // Si no existe el TCB, se crea uno nuevo
        tcb = malloc(sizeof(TCBMemoria));
        if (tcb == NULL) {
            log_error(logger_memoria, "Error al asignar memoria para el TCB del hilo TID: %d", tid);
            return contextoInvalido();
        }

        tcb->TID = tid;

        // Inicializar los registros del contexto en 0
        tcb->contexto.PC = 0;
        tcb->contexto.AX = 0;
        tcb->contexto.BX = 0;
        tcb->contexto.CX = 0;
        tcb->contexto.DX = 0;
        tcb->contexto.EX = 0;
        tcb->contexto.FX = 0;
        tcb->contexto.GX = 0;
        tcb->contexto.HX = 0;
        tcb->contexto.base = proceso->base;     // Heredar base del proceso
        tcb->contexto.limite = proceso->limite; // Heredar límite del proceso

        // Agregar el TCB a la lista de hilos del proceso
        list_add(proceso->hilos, tcb);

        log_info(logger_memoria, "## Contexto Solicitado - (PID:TID) - (%d:%d) - Contexto creado en Memoria", pid, tid);
    } else {
        log_info(logger_memoria, "## Contexto Solicitado - (PID:TID) - (%d:%d) - Contexto encontrado en Memoria", pid, tid);
    }

    return tcb->contexto;
}

void actualizarContextoMemoria(int pid, int tid, ContextoEjecucion* contexto) {
    // Buscar el proceso en la tabla de procesos
    ProcesoMemoria* proceso = buscar_proceso(pid);
    
    if (proceso == NULL) {
        log_error(logger_memoria, "## Contexto Actualizado - (PID:TID) - (%d:%d) - No se encontró el proceso en Memoria para actualizar", pid, tid);
        return;
    }

    // Buscar el TCB del hilo dentro del proceso
    TCBMemoria* tcb = buscar_hilo_en_proceso(proceso, tid);
    
    if (tcb == NULL) {
        log_error(logger_memoria, "## Contexto Actualizado - (PID:TID) - (%d:%d) - No se encontró el TCB en Memoria para actualizar", pid, tid);
        return;
    }

    // Actualizar el contexto del TCB con los valores que envía la CPU
    tcb->contexto = *contexto;

    // Log de éxito
    log_info(logger_memoria, "## Contexto Actualizado - (PID:TID) - (%d:%d) - Contexto actualizado correctamente", pid, tid);
}

ContextoEjecucion contextoInvalido() {
    ContextoEjecucion contexto;
    // Inicializa el contexto con valores que indiquen que es inválido
    contexto.PC = -1;
    contexto.AX = -1;
    contexto.BX = -1;
    contexto.CX = -1;
    contexto.DX = -1;
    contexto.EX = -1;
    contexto.FX = -1;
    contexto.GX = -1;
    contexto.HX = -1;
    contexto.base = -1;
    contexto.limite = -1;
    return contexto;
}