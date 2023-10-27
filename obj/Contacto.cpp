#include <iostream>
#include "Lista.cpp"
#include <string>

class Contacto {
    private: 
        string nombre, mail, direccion,  organizacion, puesto, notas;
        int numero;
        string cumple;
        Lista<string> links;         
    public:
        Contacto (string n, string m, string d, string o, string p, string notas, int cel, string c) {
            nombre = n;
            mail = m;
            direccion = d;
            organizacion = o;
            puesto = p;
            numero = cel;
            cumple = c;
        }
        bool operator >(const Contacto & otro) {
            return this->nombre > otro.nombre;
        } 
        bool operator <(const Contacto & otro) {
            return this->nombre < otro.nombre;
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
               //<< "\nLinks: " << c.links 
               << "\n<Fin de datos>"<<endl;
            return os;
        }


};


int main () {
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
}