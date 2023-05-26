#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <time.h>

#define MAX_MENSAJE 1000

typedef enum {
    INFO,
    WARNING,
    ER
} TipoMensaje;

typedef struct {
    FILE *archivo;
} Log;

Log* crear_log(const char *ruta_archivo);
void escribir_mensaje(Log *log, TipoMensaje tipo, const char *mensaje);
void cerrar_log(Log *log);

#endif /* LOG_H_ */
