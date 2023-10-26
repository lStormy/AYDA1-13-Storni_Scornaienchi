#include <iostream>
#include "Lista.cpp"
#include <string>

class Contacto {
    private: 
        struct fecha {
            int dd, mm, aa;    
        };
        string nombre, mail, direccion,  organizacion, puesto, notas;
        int numero;
        fecha cumple;
        Lista<string> links; 

    protected:
        bool validar_fecha () {
            if (cumple.dd <= 31 && cumple.aa <= 2023 && cumple.dd <= 12) {
                return true;
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


};