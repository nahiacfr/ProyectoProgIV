#include "Fecha.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
/*
    Devulve la fecha como una cadena de caracteres
    Formato: dd/mm/aaaa
*/
char* getFecha(Fecha *fecha)
{   
    char* resultado;
    char dia[3];
    itoa(fecha->dia, dia, 10);
    char mes[3];
    itoa(fecha->mes, mes, 10);
    char anyo[5];
    itoa(fecha->anyo, anyo, 10);
    char *fechaAux = malloc(sizeof(int) * 3 + sizeof("/") * 2 + 1);
	strcpy(fechaAux, dia);
  	strcat(fechaAux, "/");
  	strcat(fechaAux, mes);
  	strcat(fechaAux, "/");
    strcat(fechaAux, anyo);
    resultado = fechaAux;
    free(fechaAux);
    return resultado;
}
Fecha* calcularFecha(Fecha *fechaIni, int dias)
{       
    if(dias >= 15)
    {
        dias = 15;
    }
    
    Fecha* fechaFin = malloc(sizeof(Fecha));

    int diasRest;
    switch (fechaIni->mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if(fechaIni->dia + dias > 31)
        {  
            diasRest = dias - (31 - fechaIni->dia);
            fechaFin->dia = diasRest;
            if (fechaIni->mes + 1 > 12)
            {
                fechaFin->mes = 1;
                fechaFin->anyo = fechaIni->anyo + 1;
            }else
            {
                fechaFin->mes = fechaIni->mes + 1;
                fechaFin->anyo = fechaIni->anyo;
            }
            
        }else
        {
            fechaFin->dia = fechaIni->dia + dias;
            fechaFin->mes = fechaIni->mes;
            fechaFin->anyo = fechaIni->anyo;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if(fechaIni->dia + dias > 30)
        {  
            diasRest = dias - (30 - fechaIni->dia);
            fechaFin->dia = diasRest;
            if (fechaIni->mes + 1 > 12)
            {
                fechaFin->mes = 1;
                fechaFin->anyo = fechaIni->anyo + 1;
            }else
            {
                fechaFin->mes = fechaIni->mes + 1;
                fechaFin->anyo = fechaIni->anyo;
            }
        }else
        {
            fechaFin->dia = fechaIni->dia + dias; 
            fechaFin->mes = fechaIni->mes;
            fechaFin->anyo = fechaIni->anyo;
        }
        break;
    case 2:
        if(fechaIni->dia + dias > 28)
        {  
            diasRest = dias - (28 - fechaIni->dia);
            fechaFin->dia = diasRest;
            if (fechaIni->mes + 1 > 12)
            {
                fechaFin->mes = 1;
                fechaFin->anyo = fechaIni->anyo + 1;
            }else
            {
                fechaFin->mes = fechaIni->mes + 1;
                fechaFin->anyo = fechaIni->anyo;
            }
        }else
        {
            fechaFin->dia = fechaIni->dia + dias;
            fechaFin->mes = fechaIni->mes;
            fechaFin->anyo = fechaIni->anyo;
        }
        break;
    default:
        break;
    }
   return fechaFin;
}