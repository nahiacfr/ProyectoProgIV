#ifndef LIBRO_H
#define LIBRO_H

class Libro
{
private:
    char *isbn;
    char *titulo;
    int anio;
    Autor *autor;
    Editorial *editorial;
public:
    Libro();
    Libro(const char *isbn, const char *titulo, int anio, Autor *autor, Editorial *editorial);
    ~Libro();
    void anyadirLibro(Libro **listaLib, int tamanyoLista, Libro *lib);
};

class Autor
{
private:
    int id;
    char *nombre;
    char *apellidos;
public:
    Autor();
    Autor(int id, const char* nombre, const char* apellido);
    ~Autor();
    void anyadirAutor(Autor **listaAu, int tamanyoLista, Autor *au);
};

class Editorial
{
private:
    int id;
    char *nombre;
public:
    Editorial();
    Editorial(int id, const char* nombre);
    ~Editorial();
    void anyadirEditorial(Editorial **listaEd, int tamanyoLista, Editorial *ed);
};


#endif