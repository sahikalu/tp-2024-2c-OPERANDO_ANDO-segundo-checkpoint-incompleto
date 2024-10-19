#include "../include/socket.h"

int iniciar_servidor(const char* name, char* ip, char* puerto) {
    int socket_servidor;
    struct addrinfo hints, *servinfo;

    // Inicializando hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Recibe los addrinfo
    getaddrinfo(ip, puerto, &hints, &servinfo);

    bool conecto = false;

    // Itera por cada addrinfo devuelto
    for (struct addrinfo *p = servinfo; p != NULL; p = p->ai_next) {
        socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (socket_servidor == -1) 
            continue;

		if(setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0){
            // log_error(logger, "Error en setsockopt SO_REUSEPORT");
			return EXIT_SUCCESS;
		}
		
        if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
            close(socket_servidor);
            continue;
        }

        conecto = true;
        break;
    }

    if(!conecto) {
        free(servinfo);
        return 0;
    }

    listen(socket_servidor, SOMAXCONN);
    freeaddrinfo(servinfo);

    return socket_servidor;
}


int crear_conexion(const char* server_name, char* ip, char* puerto) {

    struct addrinfo hints, *servinfo;

    // Init de hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;


    // Recibe addrinfo
    getaddrinfo(ip, puerto, &hints, &servinfo);

    // Crea un socket con la informacion recibida (del primero, suficiente)
    int socket_cliente = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

   // printf("Socket cliente: %d\n", socket_cliente);

    // Fallo en crear el socket
    if(socket_cliente == -1) {
        // log_error(logger, "Error creando el socket para %s:%s", ip, puerto);
        return -1;
    }

    // Error conectando
    if(connect(socket_cliente, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        // log_error(logger, "Error al conectar (a %s)\n", server_name);
        freeaddrinfo(servinfo);
        return -1;
    } else
        // log_info(logger, "Cliente conectado en %s:%s (a %s)\n", ip, puerto, server_name);

    freeaddrinfo(servinfo);

    return socket_cliente;
}

int esperar_cliente(const char* name, int socket_servidor) {
    struct sockaddr_in dir_cliente;
    socklen_t tam_direccion = sizeof(struct sockaddr_in);

    int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

    return socket_cliente;
}