#ifndef FECHA_H
#define FECHA_H

class FechaCPP
{
private:
    int dia;
    int mes;
    int anyo;
public:
    FechaCPP(int dia, int mes, int anyo);
    ~FechaCPP();
    int compararFechas(Fecha fecha1, Fecha fecha2);
};

#endif