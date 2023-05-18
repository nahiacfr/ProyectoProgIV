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
 
 /* Este método 
 devuelve -1 si la fecha 1 es anterior a la fecha 2
 devuelve 1 si la fecha 1 es posterior a la fecha 2
 devuelve 0 si las fechas son iguales*/
int compararFechas(Fecha fecha1, Fecha fecha2){
if (fecha1.anyo < fecha2.anyo) {
        return -1; 
    } else if (fecha1.anyo > fecha2.anyo) {
        return 1; 
    } else {
        // Los años son iguales, se compara el mes
        if (fecha1.mes < fecha2.mes) {
            return -1; // fecha1 es anterior a fecha2
        } else if (fecha1.mes > fecha2.mes) {
            return 1; // fecha1 es posterior a fecha2
        } else {
            // Los meses son iguales, se compara el día
            if (fecha1.dia < fecha2.dia) {
                return -1; // fecha1 es anterior a fecha2
            } else if (fecha1.dia > fecha2.dia) {
                return 1; // fecha1 es posterior a fecha2
            } else {
                return 0; // Las fechas son iguales
            }
        }
    }

}