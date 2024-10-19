#ifndef CPU_CONTEXTO_H
#define CPU_CONTEXTO_H

#include "../utils/include/conexiones.h"
#include "../include/cpu-estructuras.h"
#include "../include/cpu-init.h"
#include "../utils/include/estructuras.h"

ContextoEjecucion solicitarContextoEjecucion(int, int, int);
void actualizarContextoEjecucion(int , int , ContextoEjecucion*, int);
void modificarcontexto (ContextoEjecucion*,uint32_t,uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t );
ContextoEjecucion crearContextoEjecucion(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

#endif