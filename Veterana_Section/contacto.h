#ifndef CONTACTO_H_INCLUDED
#define CONTACTO_H_INCLUDED

#include <iostream>
#include "lista.h"
#include <string>
using namespace std;

class Contacto {
    private:
        string nombre, apellido, mail, direccion,  organizacion, puesto, notas, numero, cumple;
        Lista<string> links;

    public:
        Contacto(string & n, string & a, string & m, string & d, string & o, string & p, string & _notas, string & cel, string & c, Lista<string> &otro);
        
        Contacto();

        Contacto & operator= (const Contacto & otro);

        bool operator >(const Contacto & otro) const;

        bool operator <(const Contacto & otro) const;

        bool operator== (const Contacto & otro) const;

        friend ostream & operator << (ostream& os, const Contacto & c) {
            /*
            Función para imprimir datos del contacto.
            No encontramos la forma de ponerlo en el .cpp
            */
            os << endl << "<Datos contacto>"
               << "\nNombre y apellido: " << c.nombre + " " + c.apellido
               << "\nMail: " << c.mail
               << "\nDirecci�n: " << c.direccion
               << "\nOrganizaci�n: " << c.organizacion
               << "\nPuesto: " << c.puesto
               << "\nNumero: " << c.numero
               << "\nFecha de cumplea�os: " << c.cumple
               << "\nLinks: " << c.links
               << "\n<Fin de datos>"<<endl;
            return os;
        }

        const string recuperar_apellido() const;

        const string recuperar_nombre() const;
};

#endif // CONTACTO_H_INCLUDED
