#include <iostream>
#include <cassert>
#include <string>
#include "lista.h"
using namespace std;

//Constructoras
template <typename T>
Lista<T>::Lista () {
    primero = NULL;
}

template <typename T>
Lista<T>::Lista (const Lista<T> & otro) {
    primero = NULL;
    this->operator= (otro);
}

//Destructoras
template <typename T>
Lista<T>::~Lista() {
    vaciar(this->primero);
}

template <typename T>
void Lista<T>::vaciar (Nodo * lista) {
    while (lista != NULL) {
        vaciar (lista->ste);
        delete lista;
        lista = NULL;
    }
}

//Modificadoras
template <typename T>
void Lista<T>::insertar (const T & dato) {
    if (this->vacio()) {
        cout << dato << endl;
        Nodo * aux = nuevo (dato);

        primero = aux;
    } else {
        if (dato < primero->dato) {
            Nodo * aux = nuevo (dato);
            cout << dato << endl;
            aux->ste = primero;
            primero = aux;
        } else {
            Nodo * cursor = primero;
            while ((cursor->ste != NULL) && (cursor->ste->dato < dato)) {
                cursor = cursor->ste;
            }
            Nodo * aux = nuevo(dato);
            if (cursor->ste != NULL) {
                aux->ste = cursor->ste;
            }
            cursor->ste = aux;
        }
    }
    imprimir_lista(this->primero);
}

template <typename T>
void Lista<T>::eliminar (const int & pos) {
    assert (pos >= 1 && pos <= len());
    if (pos == 1) {
        Nodo * eliminar = primero;
        primero = primero->ste;
        delete eliminar;
    } else {
        Nodo * cursor = this->primero;
        int i = 1;
        while (i < pos-1) {
            cursor = cursor->ste;
            i++;
        }
        Nodo * eliminar = cursor->ste;
        cursor->ste = cursor->ste->ste;
        delete eliminar;
    }
}

//Observadoras
template <typename T>
void Lista<T>::imprimir_lista (Nodo * listita) {
    cout << endl;
    Nodo * cursor = listita;
    while (cursor != NULL) {
        cout << cursor->dato << endl;
        cursor = cursor->ste;
    }
    cout <<endl;
}

template <typename T>
bool Lista<T>::vacio () const {
    return this->primero == NULL;
}

template <typename T>
int Lista<T>::len() const {
    if (this->vacio()) {
        return -1;
    } else {
        int i = 1;
        Nodo * cursor = this->primero->ste;
        while (cursor != NULL) {
            i++;
            cursor = cursor->ste;
        }
        return i;
    }
}

template <typename T>
Lista<T>& Lista<T>::operator= (const Lista<T>& otro) {
    if (!this->vacio()) {
        vaciar(this->primero);
    }
    if (otro.vacio()) {
        primero = NULL;
        primero->ste = NULL;
    } else {
        for (int i = 1; i <= otro.len(); i++) {
            this->insertar(otro.operator()(i));
        }
    }
    return *this;
}

template <typename T>
const T & Lista<T>::operator()(const int & pos) const {
    assert (pos >= 1 && pos <= len());
    Nodo * cursor = this->primero;
    for (int i = 1; i < pos; i++) {
        cursor = cursor->ste;
    }
    return cursor->dato;
}

template <typename T>
void Lista<T>::mostrar () const{
    cout << endl;
    for (int i = 1; i <= len(); i++) {
        cout << this->operator()(i) << " ";
    }
    cout << endl;
}


template class Lista<int>;
//template class Lista<string>;

//Sukablyand
