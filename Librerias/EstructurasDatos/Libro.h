#ifndef LIBRO_H
#define LIBRO_H

typedef struct
{
    int id;
    char *nombre;
    char *apellidos;
}Autor;

typedef struct
{
    int id;
    char *nombre;
}Editorial;

typedef struct
{
    char *titulo;
    char *isbn;
    int anio;
    Autor autor;
    Editorial editorial;
}Libro;

void anyadirLibro(Libro **listaLib, int tamanyoLista, Libro *lib);
void anyadirAutor(Autor **listaAu, int tamanyoLista, Autor *au);
void anyadirEditorial(Editorial **listaEd, int tamanyoLista, Editorial *ed);

#endif