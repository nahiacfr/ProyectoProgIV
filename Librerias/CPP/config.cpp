#include <iostream>
#include <fstream>
#include <cstring>
#include "config.h"

void guardar_configuracion(Configuracion config) {
    std::ofstream archivo("configuracion.txt");
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo de configuración" << std::endl;
        return;
    }

    archivo << "usuario=" << config.usuario << std::endl;
    archivo << "clave=" << config.clave << std::endl;
    archivo << "ruta_archivo=" << config.ruta_archivo << std::endl;
    archivo << "nombre_archivo=" << config.nombre_archivo << std::endl;
    archivo << "ruta_base_datos=" << config.ruta_base_datos << std::endl;
    archivo << "nombre_base_datos=" << config.nombre_base_datos << std::endl;

    archivo.close();
}