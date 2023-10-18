#include "Arbin.h"
#include <iostream>

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
template class Arbin <int>;