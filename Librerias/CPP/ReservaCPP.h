#ifndef RESERVA_H
#define RESERVA_H

#include "Usuario.h"
#include "Libro.h"
#include "FechaCPP.h"

class ReservaCPP
{
private:
    Libro libro;
    Usuario usuario;
    FechaCPP fechaIni;
    FechaCPP fechaFin;
public:
    ReservaCPP();
    ReservaCPP(Libro libro, Usuario usuario, FechaCPP fechaIni, FechaCPP fechaFin);
    ~ReservaCPP();
    Libro getLibro();
    Usuario getUsuario();
    Fecha getFechaIni();
    Fecha getFechaFin();
    void anyadirReserva(ReservaCPP **listaRes, int tamanyoLista, ReservaCPP *ed);
};

#endif