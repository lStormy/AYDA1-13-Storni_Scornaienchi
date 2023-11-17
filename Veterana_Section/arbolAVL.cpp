#include "arbolAVL.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "contacto.h"
#include <string>

using namespace std;

template <typename T> 
Avl<T>::Nodo::Nodo (Avl<T> * izq, Avl<T> * der, const T & elemento) {
    this->dato = elemento;
    this->izq = izq;
    this->der = der;
} 

template <typename T> 
Avl<T> * Avl<T>::Nodo::HijoIzq() const {
    return izq;
}

template <typename T>
Avl<T> * Avl<T>::Nodo::HijoDer() const {
    return der;
}

template <typename T>
T & Avl<T>::Nodo::valor() {
    return dato;
}

template <typename T>
const T & Avl<T>::dato () const {
    return raiz->valor();
}

template <typename T>
Avl<T> * Avl<T>::sub_der() const {
    return raiz->HijoDer();
}

template <typename T>
Avl<T> * Avl<T>::sub_izq() const {
    return raiz->HijoIzq();
}

template <typename T>
bool Avl<T>::vacio() const {
    return raiz == NULL;
}

template <typename T>
void Avl<T>::agregar(const T & elemento) {
    this->insertar(elemento);
    this->actualizar_alturas();
    this->balancear();
}

template <typename T>
void Avl<T>::borrar(const T & dato) {
    this->eliminar(dato);
    this->actualizar_alturas();
    this->balancear();
}

template <typename T>
Avl<T>::Avl() {
    raiz = NULL;
    altura = 0;
}
//suka

template <typename T>
Avl<T>::Avl(Avl<T> * otro) {
    altura = otro->altura;
    this->raiz = NULL;
    this->operator=(otro);
}

template <typename T>
Avl<T>::~Avl() {
    vaciar (this);
}

template <typename T>
void Avl<T>::vaciar (Avl * otro) {
    if (!otro->vacio()) {
        vaciar (otro->sub_izq());
        vaciar (otro->sub_der());
        delete otro->raiz;
        otro->raiz = NULL;
    }
}

template <typename T>
Avl<T> * Avl<T>::operator=(const Avl<T> * otro) {
    if (otro->vacio()) {
        raiz = NULL;
        altura = 0;
    }
    else {
        Avl<T> * izq = new Avl<T> (otro->sub_izq());
        Avl<T> * der = new Avl <T> (otro->sub_der());
        raiz = new Nodo (izq, der, otro->dato());
        this->actualizar_alturas();
    }
    return this;
}

template <typename T>
int Avl<T>::altura_nodo () const {
    if (!vacio()) {
        return 1 + max (this->sub_izq()->altura_nodo(),this->sub_der()->altura_nodo());
    }
    return -1;
}

template <typename T>
void Avl<T>::actualizar_alturas() {
    if (!vacio()) {
        altura = altura_nodo();
        sub_der()->actualizar_alturas();
        sub_izq()->actualizar_alturas();
    }
    else {
        altura = -1;
    }
}

template <typename T>
bool Avl<T>::balanceado() const { //Chequea si un nodo est� balanceado.
    (((this->sub_izq()->altura - this->sub_der()->altura) > 1) || ((this->sub_izq()->altura - this->sub_der()->altura < -1))) ? false : true;
}

template <typename T>
Avl<T> * Avl<T>::rotar_izq (Avl<T> * otro) {
    Avl<T> * aux = new Avl<T>(otro->sub_der());
    Avl<T> * aux2  = new Avl<T>(aux->sub_izq());
    otro->sub_der()->operator=(aux2);
    aux->sub_izq()->operator=(otro);
    aux->actualizar_alturas();
    otro->actualizar_alturas();
    return aux;
}

template <typename T>
Avl<T> * Avl<T>::rotar_der (Avl<T> * otro) {
    Avl * aux = new Avl<T> (otro->sub_izq());
    Avl * aux2  = new Avl<T>(aux->sub_der());
    otro->sub_izq()->operator=(aux2);
    aux->sub_der()->operator=(otro);
    aux->actualizar_alturas();
    otro->actualizar_alturas();
    return aux;
}

template <typename T>
Avl<T> * Avl <T>::rotar(Avl<T> * otro) {
    if (!vacio()) {
        int balance = (otro->sub_izq()->altura - otro->sub_der()->altura);
        if (balance > 1) {
            otro = rotar_der(otro);
        } else if (balance < -1) {
            otro = rotar_izq (otro);
        }
    }
    return otro;
}

template <typename T>
void Avl<T>::balancear () {
    if (!vacio()) {
        if (!balanceado()) {
            this->operator=(rotar(this));
        } else {
            this->sub_izq()->balancear();
            this->sub_der()->balancear();
        }
    }
}

template <typename T>
void Avl<T>::insertar (const T & elemento) {
    cout << "HOLA" << endl;
    if (!vacio()) {
        cout << "huola" << endl;
        if (elemento > this->dato()) {
            this->sub_der()->insertar(elemento);
        } else {
            this->sub_izq()->insertar(elemento);
        }
    }
    else {
        Avl<T> * izq = new Avl();
        Avl<T> * der = new Avl();
        cout << "HOLA" << endl;
        raiz = new Nodo (izq, der, elemento);
        //actualizar_alturas(this);
    }
}

template <typename T>
Avl<T> * Avl<T>::min_rama() {
    if (!vacio()) {
        if (sub_izq()->vacio()) {
            return this;
        } else {
            return sub_izq();
        }
    } else {
        return NULL;
    }
}

template <typename T> void Avl<T>::eliminar(const T & dato) {
    if (vacio()) {
        return;
    } else if (dato < this->dato()) {
        sub_izq()->eliminar(dato);    
    } else if (dato > this->dato()) {
        sub_der()->eliminar(dato);
    } else {
        if (sub_izq()->vacio() && sub_der()->vacio()) {
            delete this->raiz;
            this->raiz = NULL;
        } else if ((!sub_izq()->vacio()) && (!sub_der()->vacio())) {
            
            Avl<T> * temp = this->sub_der()->min_rama(); 
            cout << raiz->valor() << endl;
            raiz->valor() = temp->dato();
            cout << temp->dato() << endl;
            sub_der()->eliminar(temp->dato());
            
        } else {
            cout << raiz->valor() << endl;
            Avl<T> * temp = (sub_izq()->vacio()) ? sub_der() : sub_izq();
            cout << temp->dato();
            raiz->valor() = temp->dato();
            if (sub_izq()->vacio()) {
                sub_der()->eliminar(temp->dato());
            } else {
                sub_izq()->eliminar(temp->dato());
            }
        }    
    }
}


template <typename T>
bool Avl<T>::buscar (const T & dato) const {
    if (vacio()) {
        return false;
    } else {
        if (this->dato() == dato) {
            cout << this->dato();
            return true;
        } else {
            return (sub_izq()->buscar(dato) || sub_der()->buscar(dato));
        }
    }
}

template <typename T>
void Avl<T>::inorden() const {
    if (!vacio()) {
        sub_izq()->inorden();
        cout << dato() << " ";
        sub_der()->inorden();
    }
}

template class Avl<int>;
template class Avl<Contacto>;
