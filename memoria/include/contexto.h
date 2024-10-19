#ifndef MEMORIA_CONTEXTO_H
#define MEMORIA_CONTEXTO_H

#include "../utils/include/conexiones.h"
#include "../include/memoria-estructuras.h"
#include "../include/memoria-init.h"
#include "../utils/include/estructuras.h"

extern t_list* lista_pcbs;

void manejar_solicitud_contexto(int); 
ContextoEjecucion contextoInvalido();
ProcesoMemoria* buscar_proceso(int);
TCBMemoria* buscar_hilo_en_proceso(ProcesoMemoria*, int);
ContextoEjecucion solicitarContextoMemoria(int, int);
void actualizarContextoMemoria(int, int, ContextoEjecucion*)

#endif