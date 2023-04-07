#include <stdlib.h>

#include "Reserva.h"

void anyadirReserva(Reserva **listaRes, int tamanyoLista, Reserva *ed){
    Reserva **nuevaLista = (Reserva**)malloc(sizeof(Reserva*)* tamanyoLista + 1);
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaRes[i];
    }
    nuevaLista[tamanyoLista] = ed;
    free(listaRes);
    listaRes = nuevaLista;
    free(nuevaLista);
}