#ifndef FECHA_H
#define FECHA_H

typedef struct 
{
    int dia;
    int mes;
    int anyo;
}Fecha;

Fecha* crearFecha(int dia, int mes, int anyo);
int compararFechas(Fecha fecha1, Fecha fecha2);

#endif