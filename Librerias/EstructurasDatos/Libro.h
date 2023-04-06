#ifndef LIBRO_H
#define LIBRO_H

typedef struct
{
    char *nombre;
    char *apellidos;
    int id;
}Autor;

typedef struct
{
    char *nombre;
    int id;
}Editorial;

typedef struct
{
    char *titulo;
    char isbn[13];
    int anio;
    Autor autor;
    Editorial editorial;
}Libro;

#endif