#include <iostream>
#include "Lista.cpp"
#include <string>

class Contacto {
    private: 
        struct fecha {
            int dd, mm, aa;  
            friend std::ostream & operator << (std::ostream & os, const fecha & f) {
                os << f.dd << "/" << f.mm << "/" << f.aa << endl;
                return os;
            }  
        };
        string nombre, mail, direccion,  organizacion, puesto, notas;
        int numero;
        fecha cumple;
        Lista<string> links;         
    protected:
        bool validar_fecha () {
            if (cumple.dd <= 31 && cumple.aa <= 2023 && cumple.dd <= 12) {
                return  true;
            } else {
                return false;
            }
        }
    public:
        Contacto (string n, string m, string d, string o, string p, string notas, int cel, fecha c, Lista<string> l) {
            nombre = n;
            mail = m;
            direccion = d;
            organizacion = o;
            puesto = p;
            numero = cel;
            cumple = c;
            links = l;
        }
        bool operator>>(const Contacto & otro) {
            return this->nombre > otro.nombre;
        } 
        bool operator<<(const Contacto & otro) {
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