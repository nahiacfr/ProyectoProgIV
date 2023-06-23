#include <stdlib.h>

#include "ReservaCPP.h"

ReservaCPP::ReservaCPP()
{
    this->libro = NULL;
    this->usuario = NULL;
    this->fechaIni = NULL;
    this->fechaFin = NULL;
}
ReservaCPP::ReservaCPP(Libro libro, Usuario usuario, FechaCPP fechaIni, FechaCPP fechaFin)
{
    this->libro = libro;
    this->usuario = usuario;
    this->fechaIni = fechaIni;
    this->fechaFin = fechaFin;
}
ReservaCPP::~ReservaCPP()
{

}
Libro ReservaCPP::getLibro()
{
    return this->libro;
}
Usuario ReservaCPP::getUsuario()
{
    return this->usuario
}
FechaCPP ReservaCPP::getFechaIni()
{
    return this->fechaIni;
}
FechaCPP ReservaCPP::getFechaFin()
{
    return this->fechaFin;
}
void ReservaCPP::anyadirReserva(ReservaCPP **listaRes, int tamanyoLista, ReservaCPP *ed){
    ReservaCPP *nuevaLista[tamanyoLista+1];
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaRes[i];
    }
    nuevaLista[tamanyoLista] = ed;
    free(listaRes);
    listaRes = nuevaLista;
    free(nuevaLista);
}