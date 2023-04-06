#ifndef RESERVA_H
#define RESERVA_H

#include "Usuario.h"
#include "Libro.h"
#include "Fecha.h"

typedef struct 
{
    Fecha fechaIni;
    Fecha fechaFin;
    Usuario usuario;
    Libro libro;
}Reserva;



#endif