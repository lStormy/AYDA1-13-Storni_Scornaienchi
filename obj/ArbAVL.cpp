#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Contacto.cpp"
#include <string>

using namespace std;

template <typename T> class Avl {
    protected:
        class Nodo {
            private:
                Avl<T> * izq;
                Avl<T> * der;
                T dato;
            public:
                Nodo  (Avl<T> * izq, Avl<T> * der, const T & elemento) {
                    this->dato = elemento;
                    this->izq = izq;
                    this->der = der;
                }

                Avl<T> * HijoIzq () const {return izq;}
                Avl<T> * HijoDer () const {return der;}
                T & valor () {return dato;}
        };
        void vaciar (Avl<T> * raiz);
        Avl<T> * rotar(Avl<T> * raiz);
    private: 
        Nodo * raiz;
        int altura;
        Avl<T> * rotar_izq (Avl<T> * raiz);
        Avl<T> * rotar_der (Avl<T> * raiz);
        void actualizar_alturas();
        void insertar (const T & elemento);
        void eliminar(const T & dato);
        bool balanceado () const;
        Avl<T> * min_rama(); 
    public:
        //Generadoras
        Avl (); //En vacio
        Avl (Avl<T> * otro); // Por copia
        
        //Destructora
        ~Avl () {vaciar (this);}
        
        //Lectoras
        Avl<T> * sub_izq() const {return raiz->HijoIzq();}
        Avl<T> * sub_der() const {return raiz->HijoDer();}
        const T & dato () const {return raiz->valor();}
        Avl<T> * operator=(const Avl<T> * otro);
        bool buscar (const T & dato) const; //Busca e imprime si lo encuentra
        
        int altura_nodo() const;
        void inorden();
        bool vacio () const {return raiz == NULL;}
        
        //Modificadoras
        void balancear(); 
        void agregar(const T & elemento) {
            this->insertar(elemento);
            this->actualizar_alturas();
            this->balancear();
        }
        void borrar(const T & dato) {
            this->eliminar(dato);
            this->actualizar_alturas();
            this->balancear();
        }
};

template <typename T> Avl<T>::Avl() {
    raiz = NULL;
    altura = 0;
}
//suka

template <typename T> Avl<T>:: Avl(Avl<T> * otro) {
    altura = otro->altura;
    this->raiz = NULL;
    this->operator=(otro);
}

template <typename T> void Avl<T>::vaciar (Avl * raiz) {
    if (!raiz->vacio()) {
        vaciar (raiz->sub_izq());
        vaciar (raiz->sub_der());
        delete raiz->raiz;
        raiz->raiz = NULL;
    }
}

template <typename T> Avl<T> * Avl<T>::operator=(const Avl<T> * otro) {
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


template <typename T> int Avl<T>::altura_nodo () const {
    if (!vacio()) {
        return 1 + max (this->sub_izq()->altura_nodo(),this->sub_der()->altura_nodo());
    }
    return -1;
}

template <typename T> void Avl<T>::actualizar_alturas() {
    if (!vacio()) {
        altura = altura_nodo();
        sub_der()->actualizar_alturas();
        sub_izq()->actualizar_alturas();
    }
    else {
        altura = -1;
    }
}

template <typename T> bool Avl<T>::balanceado() const { //Chequea si un nodo está balanceado.
    if (((this->sub_izq()->altura - this->sub_der()->altura) > 1) || ((this->sub_izq()->altura - this->sub_der()->altura < -1))) {
        return false;
    }
    else {
        return true;
    }
}

template <typename T> Avl<T> * Avl<T>::rotar_izq (Avl<T> * raiz) {
    Avl<T> * aux = new Avl<T>(raiz->sub_der());
    Avl<T> * aux2  = new Avl<T>(aux->sub_izq());
    raiz->sub_der()->operator=(aux2);
    aux->sub_izq()->operator=(raiz);
    aux->actualizar_alturas();
    raiz->actualizar_alturas();
    return aux;
}

template <typename T> Avl<T> * Avl<T>::rotar_der (Avl<T> * raiz) {
    Avl * aux = new Avl<T> (raiz->sub_izq());
    Avl * aux2  = new Avl<T>(aux->sub_der());
    raiz->sub_izq()->operator=(aux2);
    aux->sub_der()->operator=(raiz);
    aux->actualizar_alturas();
    raiz->actualizar_alturas();
    return aux;
}

template <typename T> Avl<T> * Avl <T>::rotar(Avl<T> * raiz) {
    if (!vacio()) {
        int balance = (raiz->sub_izq()->altura - raiz->sub_der()->altura);
        if (balance > 1) {
            raiz = rotar_der(raiz);
        } else if (balance < -1) {
            raiz = rotar_izq (raiz);
        }   
    }
    return raiz;
}

template <typename T> void Avl<T>::balancear () {
    if (!vacio()) {
        if (!balanceado()) {
            this->operator=(rotar(this));
        } else {
            this->sub_izq()->balancear();
            this->sub_der()->balancear();
        }
    }
}

template <typename T> void Avl<T>::insertar (const T & elemento) {
    if (!vacio()) {
        if (elemento > this->dato()) {
            this->sub_der()->insertar(elemento);
        } else {
            this->sub_izq()->insertar(elemento);
        }
    }
    else {
        Avl<T> * izq = new Avl();
        Avl<T> * der = new Avl();
        raiz = new Nodo (izq, der, elemento);
        
        //actualizar_alturas(this);
    }
}

template <typename T> Avl<T> * Avl<T>::min_rama() {
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

template <typename T> bool Avl<T>::buscar (const T & dato) const {
    if (vacio()) {
        cout << "<El contacto no existe>";
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

template <typename T> void Avl<T>::inorden() {
    if (!vacio()) {
        cout << dato();
        cout << endl;
        sub_izq()->inorden();
        sub_der()->inorden();
    }
}

template class Avl<int>;
template class Avl<Contacto>;

/*void mostrar (Avl<int> * arb, int cont) {
    if (!arb->vacio()){
        mostrar (arb->sub_der(), cont+1 );
        for (int i = 0; i < cont; i++) {
            cout << "  ";
        }
        cout << arb->dato() <<endl;
        mostrar(arb->sub_izq(), cont +1);
    }
}

int main () {
    Avl<int> * arb = new Avl<int>();
    for (int i = 1; i<=15; i++) {
        arb->agregar(i);
        cout << endl;
        mostrar(arb, 0);
        cout << endl; 
    }
    for (int i = 15; i >= 1; i = i/2) {
        arb->borrar(i);
        cout << endl;
        mostrar(arb, 0);
        cout << endl;
    }

    return 0;
}
*/