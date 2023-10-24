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
        void vaciar(Arbin * raiz);
    
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

using namespace std;


template <typename T> Arbin<T>::Arbin() {
    primero = NULL;
}

template <typename T> Arbin<T>::Arbin(const Arbin * & otro){
    primero = NULL;
    this->operator=(otro);
}

template <typename T> void Arbin<T>::vaciar(Arbin * raiz){
    if (!raiz->vacio()) {
        vaciar(raiz->sub_izq());
        vaciar(raiz->sub_der());
        delete raiz;
    }
}

template <typename T> Arbin<T>::~Arbin(){
    vaciar (this);
}

/**template <typename T> void Arbin<T>::Crear(const Arbin * & i, const Arbin * & d, const T & elemento) {
    Arbin * izquierda = new Arbin (i);
    Arbin * derecha = new Arbin (d);
    primero = new Nodo (izquierda, derecha, elemento);
}*/

template <typename T> void Arbin<T>::insertar(const T & elemento) {
    if (this->vacio()){
        Arbin * izq = new Arbin ();
        Arbin * der = new Arbin ();
        primero = new Nodo (izq, der, elemento);
    } 
    else {
        if (this->dato() < elemento) {
            this->sub_der()->insertar(elemento);
        }
        else if (this->dato() > elemento) {
            this->sub_izq()->insertar(elemento);
        }
    }
    
}

template <typename T> Arbin<T> & Arbin<T>::operator=(Arbin *& otro) {
    vaciar (this);
    if (otro->vacio()) {
        primero = NULL;
    }
    else {
        Arbin * izq (otro->sub_izq());
        Arbin * der (otro->sub_der());
        primero = new Nodo (izq, der, otro->dato());
    }
    return *this;
}
template class Arbin<int>;