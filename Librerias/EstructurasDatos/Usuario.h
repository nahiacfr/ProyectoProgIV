#ifndef USUARIO_H
#define USUARIO_H

typedef struct 
{
    char *dni;
    char *nombre;
    char *apellidos;
    char *correo;
}Usuario;

void anyadirUsuario(Usuario **listaUs, int tamanyoLista, Usuario *us);

#endif