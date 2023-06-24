#ifndef USUARIO_H
#define USUARIO_H

/*typedef struct 
{
    char *dni;
    char *nombre;
    char *apellidos;
    char *correo;
}Usuario;

void anyadirUsuario(Usuario **listaUs, int tamanyoLista, Usuario *us);
*/

class Usuario
{
private:
    char *dni;
    char *nombre;
    char *apellidos;
    char *correo;
public:
    Usuario();
    Usuario(const char* dni, const char* nombre, const char* apellido, const char* correo);
    ~Usuario();
    void anyadirUsuario(Usuario **listaUs, int tamanyoLista, Usuario *us);
};


#endif