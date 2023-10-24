#include <iostream>

class Contacto {
    private: 
        struct fecha {
            int dd, mm, aa;
            fecha(int d, int m, int a) {
                if (d < 31 && m < 12 && a < 2023) {
                dd = d;
                mm = m;
                aa = a;
            }
        };
        struct Nodo {
            char * nombre, * mail, * direccion, * organizacion;
            int numero;
            fecha cumple;
        };

};