#ifndef RESERVA_H
#define RESERVA_H

#include "Usuario.h"
#include "Libro.h"
#include "Fecha.h"

typedef struct 
{
    Libro libro;
    Usuario usuario;
    Fecha fechaIni;
    Fecha fechaFin;
}Reserva;

void anyadirReserva(Reserva **listaRes, int tamanyoLista, Reserva *ed);

#endif