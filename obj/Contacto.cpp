#ifndef CONTACTO_H
#define CONTACTO_H

#include <iostream>
#include "Lista.cpp"
#include <string>
using namespace std;


class Contacto {
    private: 
        string nombre, apellido, mail, direccion,  organizacion, puesto, notas;
        string numero;
        string cumple;
        Lista<string> links;         
    public:
        Contacto (string n, string a, string m,  string d, string o, string p, string notas, string cel, string c, const Lista<string> & l) {
            nombre = n;
            apellido = a;
            mail = m;
            direccion = d;
            organizacion = o;
            puesto = p;
            numero = cel;
            cumple = c;
            links = Lista<string>(l);
        } 
        Contacto() {
            links = Lista<string>();
        }
        Contacto & operator = (const Contacto & otro) {
            
            this->nombre = otro.nombre;
            this->apellido = otro.apellido;
            this->cumple = otro.cumple;
            this->direccion = otro.direccion;
            this->mail = otro.mail;
            this->notas = otro.notas;
            this->numero = otro.numero;
            this->organizacion = otro.organizacion;
            this->puesto = otro.puesto;
            
            
            this->links = Lista<string>(otro.links);
        
            return * this;
        }
        void modificar_nombre (const string & nombre, const string & apellido) {
            this->nombre = nombre;
            this->apellido = apellido;
        }
        bool operator >(const Contacto & otro) const {
            if (this->apellido != otro.apellido) {
                return this->apellido > otro.apellido;
            }
            else if (this->nombre != otro.nombre) {
                return this->nombre > otro.nombre;
            }
            return this->numero > otro.numero;
        }

        bool operator <(const Contacto & otro) const {
            if (this->apellido != otro.apellido) {
                return this->apellido < otro.apellido;
            }
            else if (this->nombre != otro.nombre) {
                return this->nombre < otro.nombre;
            }
            return this->numero < otro.numero;
        }
        bool operator== (const Contacto & otro) const {
            return ((this->nombre == otro.nombre) && (this->apellido == otro.apellido) && (this->numero == otro.numero));
        }
        //Visualización
        friend std::ostream & operator << (std::ostream& os, const Contacto & c) {
            os << endl << "<Datos contacto>" 
               << "\nNombre y apellido: " << c.apellido_nombre()
               << "\nMail: " << c.mail 
               << "\nDirección: " << c.direccion
               << "\nOrganización: " << c.organizacion
               << "\nPuesto: " << c.puesto
               << "\nNumero: " << c.numero
               << "\nFecha de cumpleaños: " << c.cumple
               << "\nLinks: " << c.links 
               << "\n<Fin de datos>"<<endl;
            return os;
        }
        const string apellido_nombre () const {
            return (nombre + " " + apellido);
        }


};


/*int main () {
    Lista<string> links = Lista<string>();
    Contacto nuevo = Contacto("Carlos", "YO", "Alem al no sé cuanto", "No trabajo", "Que no", "Nada", "41349", "1/1/1", links);
    cout << nuevo;
    Contacto otro = Contacto("Carlos", "YO", "Alem al no sé cuanto", "No trabajo", "Que no", "Nada", "41349", "1/1/1", links);
    cout << endl << otro;
    if (nuevo < otro) {
        cout << "Es menor" << endl;
    } 
    else if (nuevo > otro) {
        cout << "Es mayor" << endl;
    }
    else {
        cout << "ES LO MISMOO!!!" << endl;
    }
    cout << endl;
    return 0;
}*/
#endif