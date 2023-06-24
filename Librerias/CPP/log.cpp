#include "log.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

Log* Log::crear_log(const char *ruta_archivo) {
    Log *log = new Log;
    log->archivo.open(ruta_archivo, ios::app);
    if (!log->archivo.is_open()) {
        cout << "Error al abrir el archivo de log" << endl;
        delete log;
        return nullptr;
    }
    return log;
}

void Log::escribir_mensaje(Log *log, TipoMensaje tipo, const char *mensaje) {
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
        case ER:
            strcpy(tipo_str, "ERROR");
            break;
        default:
            strcpy(tipo_str, "DESCONOCIDO");
            break;
    }

    char mensaje_formateado[MAX_MENSAJE];
    snprintf(mensaje_formateado, MAX_MENSAJE, "[%s] [%s]: %s\n", fecha, tipo_str, mensaje);

    log->archivo << mensaje_formateado;
    log->archivo.flush();
}

void Log::cerrar_log(Log *log) {
    log->archivo.close();
    delete log;
}