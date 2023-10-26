#include <iostream>
#include <cassert>
#include "Contacto.cpp"
using namespace std;

template <typename T> class Lista {
    protected: 
        struct Nodo {
            T dato;
            Nodo * ste;
        };
    private: 
        Nodo * primero; 
        Nodo * nuevo (const T & dato) {
            Nodo * aux = new Nodo();
            aux->dato = dato;
            aux->ste = NULL;
            return aux;
        }
        void vaciar (Nodo * lista) {
            while (lista != NULL) {
                vaciar (lista->ste);
                delete lista;
                lista = NULL;
            }   
        } 
        void imprimir_lista (Nodo * listita) {
            cout << endl;
            Nodo * cursor = listita;
            while (cursor != NULL) {
                cout << cursor->dato << endl;
                cursor = cursor->ste;
            }
            cout <<endl;
        }
    public: 
        Lista () {
            primero = NULL;
        }
        Lista (const Lista<T> & otro) {
            primero = NULL;
            this->operator= (otro);
        }
        ~Lista() {
            vaciar(this->primero);
        }
        void insertar (const T & dato) {
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
        bool vacio () const {
            return this->primero == NULL;
        }
        int len() const {
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
        const T & operator()(const int & pos) const {
            assert (pos >= 1 && pos <= len());
            Nodo * cursor = this->primero;
            for (int i = 1; i < pos; i++) {
                cursor = cursor->ste;
            } 
            return cursor->dato;
        }
        void eliminar (const int & pos) {
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
        Lista<T> & operator= (const Lista<T> & otro) {
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
        void mostrar () {
            cout << endl;
            for (int i = 1; i <= len(); i++) {
                cout << this->operator()(i) << " ";
            }
            cout << endl;
        }
};

template class Lista<int>;
template class lista<contacto>;

void cargar_lista (Lista<int> & list) {
    cout << "<Deja de cargar con un entero menor a 0>" <<endl;
    cout << "Inserte un elemento a la lista: ";
    int elemento = -1;
    cin >> elemento;
    while (elemento > -1) {
        list.insertar(elemento);
        elemento = -1;
        cout << "Inserte un elemento a la lista: ";
        cin >> elemento;
    }
}

int main () {
    Lista<int> nueva = Lista<int>();
    cout << nueva.len() <<endl;
    cargar_lista(nueva);
    cout << nueva.len() <<endl;
    cout << "Primer elemento: " << nueva(1);
    nueva.mostrar();
    return 0;
}