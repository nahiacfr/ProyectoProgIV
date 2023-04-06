#include "log.h"
#include <stdlib.h>
#include <string.h>

Log* crear_log(char *ruta_archivo) {
    Log *log = malloc(sizeof(Log));
    log->archivo = fopen(ruta_archivo, "a");
    if (log->archivo == NULL) {
        printf("Error al abrir el archivo de log\n");
        free(log);
        return NULL;
    }
    return log;
}

void escribir_mensaje(Log *log, TipoMensaje tipo, char *mensaje) {
    time_t t;
    time(&t);
    struct tm *local = localtime(&t);

    char fecha[20];
    strftime(fecha, 20, "%Y-%m-%d %H:%M:%S", local);

    char tipo_str[10];
    switch (tipo) {
        case INFO:
            strcpy(tipo_str, "INFO");
            break;
        case WARNING:
            strcpy(tipo_str, "WARNING");
            break;
        case ERROR:
            strcpy(tipo_str, "ERROR");
            break;
        default:
            strcpy(tipo_str, "DESCONOCIDO");
            break;
    }

    char mensaje_formateado[MAX_MENSAJE];
    snprintf(mensaje_formateado, MAX_MENSAJE, "[%s] [%s]: %s\n", fecha, tipo_str, mensaje);

    fputs(mensaje_formateado, log->archivo);
    fflush(log->archivo);
}

void cerrar_log(Log *log) {
    fclose(log->archivo);
    free(log);
}
