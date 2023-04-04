#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#define MAX_USUARIO 50
#define MAX_CLAVE 50
#define MAX_RUTA 100

typedef struct {
    char usuario[MAX_USUARIO];
    char clave[MAX_CLAVE];
    char ruta_archivo[MAX_RUTA];
    char nombre_archivo[MAX_RUTA];
    char ruta_base_datos[MAX_RUTA];
    char nombre_base_datos[MAX_RUTA];
} Configuracion;

void guardar_configuracion(Configuracion config);


#endif /* CONFIGURACION_H_ */
