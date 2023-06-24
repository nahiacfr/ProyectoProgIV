#ifndef LOGCPP_H_
#define LOGCPP_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

#define MAX_MENSAJE 1000

enum class TipoMensaje {
    INFO,
    WARNING,
    ER
};

class Log {
public:
    void escribir_mensaje(Log *log, TipoMensaje tipo, const char* mensaje);
    Log* crear_log(const char *ruta_archivo);
    void cerrar_log(Log *log);

private:
    std::ofstream archivo;
};

#endif