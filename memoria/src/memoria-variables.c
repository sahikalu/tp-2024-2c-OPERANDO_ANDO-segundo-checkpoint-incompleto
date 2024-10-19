#include "../include/memoria-estructuras.h"

// Variables globales:

// Variable para la configuracion de la memoria:
t_config_memoria *config_memoria = NULL;

// Variable para el espacio de usuario:
void *espacio_usuario = NULL;

// Variable para el socket del servidor:
int socket_servidor;

// Variable para administrar las instrucciones por PIB Y TIB:
t_dictionary *instrucciones;