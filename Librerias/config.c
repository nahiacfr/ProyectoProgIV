#include <stdio.h>
#include <string.h>
#include "config.h"

void guardar_configuracion(Configuracion config) {
    FILE *archivo = fopen("configuracion.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de configuración\n");
        return;
    }

    fprintf(archivo, "usuario=%s\n", config.usuario);
    fprintf(archivo, "clave=%s\n", config.clave);
    fprintf(archivo, "ruta_archivo=%s\n", config.ruta_archivo);
    fprintf(archivo, "nombre_archivo=%s\n", config.nombre_archivo);
    fprintf(archivo, "ruta_base_datos=%s\n", config.ruta_base_datos);
    fprintf(archivo, "nombre_base_datos=%s\n", config.nombre_base_datos);

    fclose(archivo);
}