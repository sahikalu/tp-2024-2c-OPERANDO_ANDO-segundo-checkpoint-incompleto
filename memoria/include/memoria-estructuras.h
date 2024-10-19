#ifndef MEMORIA_MEMORIA_ESTRUCTURAS_H
#define MEMORIA_MEMORIA_ESTRUCTURAS_H

// Librerias externas:
#include <commons/collections/list.h>
#include <commons/collections/dictionary.h>

typedef struct {
    int puerto_escucha;
    char *ip_filesystem;
    char *puerto_filesystem;
    int tam_memoria;
    char *path_instrucciones;
    int retardo_respuesta;
    char *esquema;
    char *algoritmo_busqueda;
    t_list *particiones;
    char *log_level;
} t_config_memoria;

// Variable para la configuracion de la memoria:
extern t_config_memoria *config_memoria = NULL;

// Variable para el espacio de usuario:
extern void *espacio_usuario;

// Variable para el socket del servidor:
extern int socket_servidor;

// Variable para administrar las instrucciones por PIB Y TIB:
extern t_dictionary *instrucciones;