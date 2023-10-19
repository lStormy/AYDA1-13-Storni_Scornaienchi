#include <iostream>
using namespace std;

template <typename T> class Arbavl: {
    protected:
        class Nodo {
            private:
                Arbavl * izq;
                Arbavl * der;
                T dato;
            public:
                Nodo (Arbavl<T> *& izq, Arbavl<T> *& der, const T & elemento) {
                    this->dato = elemento;
                    this->izq = izq;
                    this->der = der;
                }
                Arbavl<T> * HijoIzq () {return izq;}
                Arbavl<T> * HijoDer () {return der;}
                const T & raiz () const {return dato;}
        };
        void vaciar (Arbavl<T> * & raiz);
        bool balanceado ();
        void rotar();
    private: 
        Nodo * primero;
        int altura;
        void rotar_izq();
        void rotar_der();
        void actualizar_alturas(const Arbavl * & raiz);
        void insertar (const T & elemento);
    public:
        Arbavl ();
        Arbavl (const Arbavl<T> * & otro);
        ~Arbavl () {vaciar (this);}
        Arbavl<T> & operator=(const Arbavl<T> * & otro);
        Arbavl<T> * sub_izq() {return primero->HijoIzq();}
        Arbavl<T> * sub_der() {return primero->HijoDer();}
        const T & dato () const {return primero->raiz();}
        void agregar(const T & elemento) {
            this->insertar(elemento);
            actualizar_alturas(this);
            this->actualizar();
        }
        //void eliminar ();
        int altura_nodo();
        bool vacio () {return primero == NULL;}
        void actualizar();
};

template <typename T> Arbavl<T>::Arbavl() {
    primero = NULL;
    altura = 0;
}

template <typename T> Arbavl<T>::Arbavl (const Arbavl<T> * & otro) {
    altura = otro->altura;
    this->operator=(otro);
}

template <typename T> void Arbavl<T>::vaciar(Arbavl * & raiz) {
    if (!vacio()) {
        vaciar (raiz->sub_izq());
        vaciar (raiz->sub_der());
        delete raiz;
    }
}

template <typename T> Arbavl<T> & Arbavl<T>::operator=(const Arbavl * & otro) {
    if (otro->vacio()) {
        primero = NULL;
        altura = 0;
    }
    else {
        primero = new Node (otro->sub_izq(), otro->sub_der(), otro->dato());
        altura = otro->altura;
    }
    return *this;
}

template <typename T> int Arbavl<T>::altura_nodo () {
    if (!vacio()) {S
        if ((!this->sub_izq()->vacio()) || (!this->sub_der()->vacio())) {
            return 1 + max (this->sub_izq()->altura_nodo(),this->sub_der()->altura_nodo());
        }
        else {
            return 0;
        }
    }
    return 0;
}

template <typename T> void Arbavl<T>::actualizar_alturas(const Arbavl * & raiz) {
    if (!vacio()) {
        altura = this->altura_nodo();
        actualizar_alturas(this->sub_izq());
        actualizar_alturas(this->sub_der());
    }
    else {
        altura = 0;
    }
}

int dif (const int & a, const int & b) {
    if (a < b) {
        return b - a;
    } else {
        return a - b;
    }
}

template <typename T> bool Arbavl<T>::balanceado() { //Chequea si un nodo está balanceado.
    if dif(this->sub_izq()->altura, this->sub_der()->altura) > 1 {
        return false;
    }
    else {
        return true;
    }
}

template <typename T> void Arbavl<T>::rotar_izq() {
    Arbavl * aux (this->sub_der());
    Arbavl * aux2 (aux->sub_izq());
    aux->sub_izq() = aux;
    this->sub_der() = aux2;
    actualizar_alturas(aux);
    actualizar_alturas(this);
}

template <typename T> void Arbavl<T>::rotar_der() {
    Arbavl * aux (this->sub_izq());
    Arbavl * aux2 (aux->sub_der());
    aux->sub_der()->operator= (aux);
    this->sub_izq()->operator= (aux2);
    actualizar_alturas(aux);
    actualizar_alturas(this);
}

template <typename T> void Arbavl<T>::rotar() {
    if (!vacio()) {
        if (sub_izq()->altura > sub_der()->altura) {
            this->rotar_izq();
        }
        else {
            rotar_der();
        }
    }
}

template <typename T> void Arbavl<T>::actualizar () {
    if (!vacio()) {
        if (!balanceado()) {
            rotar();
        } else {

            this->sub_izq()->actualizar();
            this->sub_der()->actualizar();
        }
    }
}

template <typename T> void Arbavl<T>::insertar (const T & elemento) {
    if (!vacio()) {
        if (elemento > this->dato()) {
            this->sub_der()->insertar(elemento);
        } else {
            this->sub_izq()->insertar(elemento);
        }
    }
    else {
        Arbavl * izq ();
        Arbavl * der();
        primero = new Nodo (izq, der, elemento);
        actualizar_alturas(this);
    }
}



template class Arbavl<int>;
int main () {
    Arbavl<int> * arb = new Arbavl<int> ();
       
}