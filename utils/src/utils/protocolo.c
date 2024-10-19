#include "../include/protocolo.h"

void generar_handshake(int socket, char *server_name, char *ip, char *puerto) {
    int32_t handshake = 1;
    int32_t result;

	op_code cod_op = HANDSHAKE; 
	send(socket, &cod_op, sizeof(op_code), 0);
    
    send(socket, &handshake, sizeof(int32_t), 0);
	recv(socket, &result, sizeof(int32_t), MSG_WAITALL);

    if(result == 0) 
        log_info(logger, "Handshake exitoso con %s", server_name);
    else {
        log_error(logger, "Error en el handshake con %s", server_name);
        exit(EXIT_FAILURE);
    }
}

void recibir_handshake(int socket) {
	int32_t handshake;
	int32_t resultOk = 0;
	int32_t resultError = -1;

	recv(socket, &handshake, sizeof(int32_t), MSG_WAITALL);
	
	if (handshake == 1) 
		send(socket, &resultOk, sizeof(int32_t), 0);
	else 
		send(socket, &resultError, sizeof(int32_t), 0);
}

char *parsear_string(void *buffer, int *desplazamiento) {
    int tam;

    // Copiamos el tamaño del string:
    memcpy(&tam, buffer + *desplazamiento, sizeof(int));
    *desplazamiento += sizeof(int);

    // Copiamos el string:
    char *string = malloc(tam + 1);
    memcpy(string, buffer + *desplazamiento, tam);
    *desplazamiento += tam + 1;

    string[tam] = '\0';

    return string;
}