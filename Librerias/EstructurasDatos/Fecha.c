#include "Fecha.h"
#include <stdlib.h>

Fecha* crearFecha(int dia, int mes, int anyo){
    if(dia<32 && dia >= 0 && mes<13 && mes>0){
        Fecha* fecha = malloc(sizeof(Fecha));
       fecha->dia = dia;
        fecha->mes = mes;
        fecha->anyo = anyo;
        return fecha;
    } else {
        return NULL;
 }
}
 
 
int compararFechas(Fecha fecha1, Fecha fecha2){


}