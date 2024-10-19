#ifndef FILESYSTEM_FS_ESTRUCTURAS_H
#define FILESYSTEM_FS_ESTRUCTURAS_H

typedef struct {
    char *puerto_escucha;
    char *mount_dir;
    int block_size;
    int block_count;
    int retardo_acceso_bloque;
    char *log_level;
} t_config_fs;

// Variables globales:

// Variable de configuracion:
extern t_config_fs *config_fs;

#endif