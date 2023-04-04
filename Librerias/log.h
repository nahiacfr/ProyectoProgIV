#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <time.h>

#define MAX_MENSAJE 1000

typedef enum {
    INFO,
    WARNING,
    ERROR
} TipoMensaje;

typedef struct {
    FILE *archivo;
} Log;

Log* crear_log(char *ruta_archivo);
void escribir_mensaje(Log *log, TipoMensaje tipo, char *mensaje);
void cerrar_log(Log *log);

#endif /* LOG_H_ */
