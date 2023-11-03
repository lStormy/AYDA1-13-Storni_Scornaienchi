#ifndef CONTACTO_H
#define CONTACTO_H

#include <iostream>
#include "Lista.cpp"
#include <string>
using namespace std;


class Contacto {
    private: 
        string nombre, mail, direccion,  organizacion, puesto, notas;
        string numero;
        string cumple;
        Lista<string> links;         
    public:
        Contacto (string n, string m, string d, string o, string p, string notas, string cel, string c, const Lista<string> & l) {
            nombre = n;
            mail = m;
            direccion = d;
            organizacion = o;
            puesto = p;
            numero = cel;
            cumple = c;
            links = l;
        } 
        Contacto() {
            links = Lista<string>();
        }
        Contacto & operator = (const Contacto & otro) {
            this->nombre = otro.nombre;
            this->cumple = otro.cumple;
            this->direccion = otro.direccion;
            this->mail = otro.mail;
            this->notas = otro.notas;
            this->numero = otro.numero;
            this->organizacion = otro.organizacion;
            this->puesto = otro.puesto;
            this->links = otro.links;
            return * this;
        }
        void modificar_nombre (const string & nombre) {
            this->nombre = nombre;
        }
        bool operator >(const Contacto & otro) const {
            return this->nombre > otro.nombre;
        } 
        bool operator <(const Contacto & otro) const {
            return this->nombre < otro.nombre;
        }
        bool operator== (const Contacto & otro) const {
            return this->nombre == otro.nombre;
        }
        friend std::ostream & operator << (std::ostream& os, const Contacto & c) {
            os << endl << "<Datos contacto>" 
               << "\nNombre: " << c.nombre 
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


};


/**int main () {
    Contacto nuevo = Contacto("Carlos", "YO", "Alem al no sé cuanto", "No trabajo", "Que no", "Nada", 41349, "1/1/1");
    cout << nuevo;
    Contacto otro = Contacto("Barlos", "YO", "Alem al no sé cuanto", "No trabajo", "Que no", "Nada", 41349, "1/1/1");
    cout << endl << otro;
    if (nuevo < otro) {
        cout << "Es menor" << endl;
    } else {
        cout << "Es mayor" << endl;
    }
    cout << endl;
    return 0;
}*/
#endif