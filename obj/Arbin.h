#ifndef ARBIN_H
#define ARBIN_H
#include <iostream>
using namespace std;

template <typename T> class Arbin {
    protected:
        class Nodo {
            private:
                Arbin * izq;
                Arbin * der;
                T dato;
            public:
                Nodo (Arbin<T> *& izq, Arbin<T> *& der, const T & elemento) {
                    this->dato = elemento;
                    this->izq = izq;
                    this->der = der;
                }
                Arbin * HijoIzq () const {return izq;}
                Arbin * HijoDer () const {return der;}
                const T & raiz () const {return dato;}
                
        };
        void vaciar(Arbin* raiz);
    
    private:
        Nodo * primero;

    public: 
        Arbin ();
        Arbin (const Arbin * & otro);
        ~Arbin ();
        void insertar(const T & elemento);
        bool vacio () const {return primero == NULL;}
        Arbin & operator=(Arbin *& otro);
        const T & dato () {return primero->raiz();}
        Arbin * sub_izq () {return primero->HijoIzq();}
        Arbin * sub_der () {return primero->HijoDer();}
};  

#endif