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
{   printf("Check F1");
    char* resultado;
    printf("%i", fecha->dia);
    printf("Check F2");
    char dia[3];
    
    printf("Check F2.1");
    itoa(fecha->dia, dia, 10);
    printf("Check F2.2");
    char mes[3];
    printf("Check F2.3");
    itoa(fecha->mes, mes, 10);
    printf("Check F2.4");
    char anyo[5];
    printf("Check F2.5");
    itoa(fecha->anyo, anyo, 10);
    printf("Check F2.6");
    char *fechaAux = malloc(sizeof(int) * 3 + sizeof("/") * 2 + 1);
    printf("Check F3");
	strcpy(fechaAux, dia);
    printf("Check F4");
  	strcat(fechaAux, "/");
    printf("Check F5");
  	strcat(fechaAux, mes);
    printf("Check F6");
  	strcat(fechaAux, "/");
    printf("Check F7");
    strcat(fechaAux, anyo);
    printf("Check F8");
  	strcat(fechaAux, "/");
    printf("Check F9");
    resultado = fechaAux;
    printf("Check F10");
    free(fechaAux);
    printf("Check F11");
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
    switch (fechaFin->mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if(fechaFin->dia + dias > 31)
        {  
            diasRest = dias - (31 - fechaFin->dia);
            fechaFin->dia = diasRest;
            fechaFin->mes++;
        }else
        {
            fechaFin->dia += dias; 
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if(fechaFin->dia + dias > 30)
        {  
            diasRest = dias - (30 - fechaFin->dia);
            fechaFin->dia = diasRest;
            fechaFin->mes++;
        }else
        {
            fechaFin->dia += dias; 
        }
        break;
    case 2:
        if(fechaFin->dia + dias > 28)
        {  
            diasRest = dias - (28 - fechaFin->dia);
            fechaFin->dia = diasRest;
            fechaFin->mes++;
        }else
        {
            fechaFin->dia += dias; 
        }
        break;
    default:
        break;
    }
   return fechaFin;
}