#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

class Configuracion {
public:
    static const int MAX_USUARIO = 50;
    static const int MAX_CLAVE = 50;
    static const int MAX_RUTA = 100;

    char usuario[MAX_USUARIO];
    char clave[MAX_CLAVE];
    char ruta_archivo[MAX_RUTA];
    char nombre_archivo[MAX_RUTA];
    char ruta_base_datos[MAX_RUTA];
    char nombre_base_datos[MAX_RUTA];
};

void guardar_configuracion(const Configuracion& config);

#endif /* CONFIGURACION_H_ */