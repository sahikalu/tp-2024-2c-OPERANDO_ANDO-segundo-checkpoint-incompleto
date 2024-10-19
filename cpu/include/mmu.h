#ifndef CPU_MMU_H
#define CPU_MMU_H

#include "../include/cpu-conexiones.h"
#define SEGMENTATION_FAULT ((uint32_t)-1)

uint32_t calcular_direccion_fisica(uint32_t, uint32_t, uint32_t);
void manejar_solicitud_direccion_fisica(int);

#endif