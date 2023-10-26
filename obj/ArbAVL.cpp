#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T> class Avl {
    protected:
        class Nodo {
            private:
                Avl * izq;
                Avl * der;
                T dato;
            public:
                Nodo  (Avl<T> * izq, Avl<T> * der, const T & elemento) {
                    this->dato = elemento;
                    this->izq = izq;
                    this->der = der;
                }

                Avl<T> * HijoIzq () const {return izq;}
                Avl<T> * HijoDer () const {return der;}
                T & raiz () {return dato;}
        };
        void vaciar (Avl<T> * raiz);
        Avl<T> * rotar(Avl<T> * raiz);
    private: 
        Avl<T> * min_rama(); 
        Nodo * primero;
        int altura;
        Avl<T> * rotar_izq (Avl<T> * raiz);
        Avl<T> * rotar_der (Avl<T> * raiz);
        void actualizar_alturas();
        void insertar (const T & elemento);
        void eliminar(const T & dato);
    public:
        Avl ();
        Avl (Avl<T> * otro);
        ~Avl () {vaciar (this);}
        Avl<T> * operator=(const Avl<T> * otro);
        Avl<T> * sub_izq() const {return primero->HijoIzq();}
        Avl<T> * sub_der() const {return primero->HijoDer();}
        const T & dato () const {return primero->raiz();}
        void agregar(const T & elemento) {
            this->insertar(elemento);
            this->actualizar_alturas();
            this->balancear();
        }
        bool balanceado () const;
        void borrar(const T & dato) {
            this->eliminar(dato);
            this->actualizar_alturas();
            this->balancear();
        }
        int altura_nodo() const;
        bool vacio () const {return primero == NULL;}
        void balancear();
};

template <typename T> Avl<T>::Avl() {
    primero = NULL;
    altura = 0;
}
//suka

template <typename T> Avl<T>:: Avl(Avl<T> * otro) {
    altura = otro->altura;
    this->primero = NULL;
    this->operator=(otro);
}

template <typename T> void Avl<T>::vaciar (Avl * raiz) {
    if (!raiz->vacio()) {
        vaciar (raiz->sub_izq());
        vaciar (raiz->sub_der());
        delete raiz->primero;
        raiz->primero = NULL;
    }
}

template <typename T> Avl<T> * Avl<T>::operator=(const Avl<T> * otro) {
    if (otro->vacio()) {
        primero = NULL;
        altura = 0;
    }
    else {
        Avl<T> * izq = new Avl<T> (otro->sub_izq());
        Avl<T> * der = new Avl <T> (otro->sub_der());
        primero = new Nodo (izq, der, otro->dato());
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
        Avl<T> * izq = new Avl<T>();
        Avl<T> * der = new Avl<T>();
        primero = new Nodo (izq, der, elemento);
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
        if ((!sub_izq()->vacio()) && (!sub_der()->vacio())) {
            Avl<T> * temp = this->sub_der()->min_rama(); 
            primero->raiz() = temp->dato();
            sub_der()->eliminar(temp->dato());
        } else {
            if (sub_izq()->vacio() && sub_der()->vacio()) {
                delete this->primero;
                this->primero = NULL;
            } else {
                Avl<T> * temp = (sub_izq()->vacio()) ? sub_der() : sub_izq();
                primero->raiz() = temp->dato();
                cout << "Llego acá" << endl;
                if (sub_izq()->vacio()) {
                    sub_der()->eliminar(temp->dato());
                } else {
                    sub_izq()->eliminar(temp->dato());
                }
            }    
        }
    }
}

bool pertenece (Avl<int> * arb, const int & dato) {
    if (!arb->vacio()) {
        if (arb->dato() > dato) {
            return pertenece (arb->sub_izq(), dato);
        } else if(arb->dato() < dato) {
            return pertenece (arb->sub_der(),dato);
        } else {
            return true;
        }
    }
    return false;
} 

void mostrar (Avl<int> * arb, int cont) {
    if (!arb->vacio()){
        mostrar (arb->sub_der(), cont+1 );
        for (int i = 0; i < cont; i++) {
            cout << "  ";
        }
        cout << arb->dato() <<endl;
        mostrar(arb->sub_izq(), cont +1);
    }
}

void balance(const Avl<int> & arb) {
    if (arb.balanceado()) {
        cout <<"Está balanceado" <<endl;
    }
    else {
        cout << "No está balanceado" <<endl;
    }
} //QUIERO LA LIBERTADORESS

template class Avl<int>;

int main () {
    Avl<int> * arb = new Avl<int> ();
    int dato = 0;
    while (dato >= 0){
        cout << "Ingrese un dato al arreglo: ";
        cin >> dato;
        if (dato > 0){
            arb->agregar(dato);
            balance(*arb);
        }        
        mostrar(arb, 0);
        cout <<endl;
    } 
    cout << endl << "Ingrese el valor a eliminar: ";
    cin >> dato;
    arb->borrar(dato);
    cout << endl;
    mostrar(arb, 0);
}
