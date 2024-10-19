#ifndef CPU_CILO_INSTRUCCIONES_H
#define CPU_CILO_INSTRUCCIONES_H

#include <utils/include/estructuras.h>

/**
* @brief Inicia el ciclo de instrucciones de la CPU.
*/
void iniciar_ciclo_instrucciones(void);

/**
* @brief Realiza la etapa de fetch de las instrucciones.
*/
void fetch_instrucciones(void);

/**
* @brief Ejecuta una instrucción específica.
* @param instruccion La instrucción a ejecutar.
*/
void ejecutar_instruccion(t_instruccion instruccion);

#endif // CPU_CILO_INSTRUCCIONES_H