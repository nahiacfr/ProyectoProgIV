#include <stdlib.h>
#include "Libro.h"

//libro
Libro::Libro(/* args */)
{
}
Libro::~Libro()
{
}

//autor
Autor::Autor(/* args */)
{
}
Autor::~Autor()
{
}

//editorial
Editorial::Editorial(/* args */)
{
}
Editorial::~Editorial()
{
}

//////////////////////////
void Libro::anyadirLibro(Libro **listaLib, int tamanyoLista, Libro *lib)
{
    Libro **nuevaLista = new Libro*[tamanyoLista + 1];
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaLib[i];
    }
    nuevaLista[tamanyoLista] = lib;
    delete[] listaLib;
    listaLib = nuevaLista;
    delete[] nuevaLista;
}

void Autor::anyadirAutor(Autor **listaAu, int tamanyoLista, Autor *au)
{
    Autor **nuevaLista = new Autor*[tamanyoLista +1];
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaAu[i];
    }
    nuevaLista[tamanyoLista] = au;
    delete[] listaAu;
    listaAu = nuevaLista;
    delete[] nuevaLista;
}

void Editorial::anyadirEditorial(Editorial **listaEd, int tamanyoLista, Editorial *ed)
{
    Editorial **nuevaLista = new Editorial*[tamanyoLista+1];
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaEd[i];
    }
    nuevaLista[tamanyoLista] = ed;
    delete[] listaEd;
    listaEd = nuevaLista;
    delete[] nuevaLista;
}