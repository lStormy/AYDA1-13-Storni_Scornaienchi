#include <iostream>
using namespace std;

template <typename T> class Avl {
    protected:
        class Nodo {
            private:
             Avl * izq;
             Avl * der;
                T dato;
            public:
                Nodo  (Avl<T> *& izq, Avl<T> *& der, const T & elemento) {
                    this->dato = elemento;
                    this->izq = izq;
                    this->der = der;
                }
             Avl<T> * HijoIzq () {return izq;}
             Avl<T> * HijoDer () {return der;}
                const T & raiz () const {return dato;}
        };
        void vaciar (Avl<T> * raiz);
        bool balanceado () const;
        Avl<T> *  rotar(Avl<T> * raiz);
    private: 
        Nodo * primero;
        int altura;
        Avl<T> * rotar_izq (Avl<T> * raiz);
        Avl<T> * rotar_der (Avl<T> * raiz);
        void actualizar_alturas(const Avl * raiz);
        void insertar (const T & elemento);
    public:
        Avl ();
        Avl (const Avl<T> *  otro);
        ~Avl () {vaciar (this);}
        Avl<T> * operator=(Avl<T> * otro);
        Avl<T> * sub_izq() {return primero->HijoIzq();}
        Avl<T> * sub_der() {return primero->HijoDer();}
        const T & dato () const {return primero->raiz();}
        void agregar(const T & elemento) {
            this->insertar(elemento);
            actualizar_alturas(this);
            this->actualizar();
        }
        //void eliminar ();
        int altura_nodo() const;
        bool vacio () const {return primero == NULL;}
        void balancear();
};

template <typename T> Avl<T>:: Avl() {
    primero = NULL;
    altura = 0;
}

template <typename T> Avl<T>:: Avl(const Avl<T> * otro) {
    altura = otro->altura;
    this->operator=(otro);
}

template <typename T> void Avl<T>::vaciar (Avl * raiz) {
    if (!vacio()) {
        vaciar (raiz->sub_izq());
        vaciar (raiz->sub_der());
        delete raiz;
    }
}

template <typename T> Avl<T> * Avl<T>::operator=(Avl<T> * otro) {
    if (otro->vacio()) {
        primero = NULL;
        altura = 0;
    }
    else {
        primero = new Nodo (otro->sub_izq(), otro->sub_der(), otro->dato());
        altura = otro->altura;
    }
    return this;
}


template <typename T> int Avl<T>::altura_nodo () const {
    if (!vacio()) {
        if ((!this->sub_izq()->vacio()) || (!this->sub_der()->vacio())) {
            return 1 + max (this->sub_izq()->altura_nodo(),this->sub_der()->altura_nodo());
        }
        else {
            return 0;
        }
    }
    return 0;
}

template <typename T> void Avl<T>::actualizar_alturas(const Avl * raiz) {
    if (!vacio()) {
        altura = this->altura_nodo();
        actualizar_alturas(this->sub_izq());
        actualizar_alturas(this->sub_der());
    }
    else {
        altura = 0;
    }
}

template <typename T> bool Avl<T>::balanceado() const { //Chequea si un nodo está balanceado.
    if (((this->sub_izq()->altura - this->sub_der()->altura) > 1) && ((this->sub_izq()->altura - this->sub_der()->altura < -1))) {
        return false;
    }
    else {
        return true;
    }
}

template <typename T> Avl<T> * Avl<T>::rotar_izq (Avl<T> * raiz) {
    Avl * aux (raiz->sub_der());
    Avl * aux2 (aux->sub_izq());
    aux->sub_izq()->operator=( aux);
    this->sub_der()->operator=( aux2);
    actualizar_alturas(aux);
    actualizar_alturas(raiz);
    return raiz;
}

template <typename T> Avl<T> * Avl<T>::rotar_der (Avl<T> * raiz) {
    Avl * aux (raiz->sub_izq());
    Avl * aux2 (aux->sub_der());
    aux->sub_der()->operator=(aux);
    raiz->sub_izq()->operator=(aux2);
    actualizar_alturas(aux);
    actualizar_alturas(raiz);
    return raiz;
}

template <typename T> Avl<T> * Avl <T>::rotar(Avl<T> * raiz) {
    
    if (!vacio()) {
        int balance = (raiz->sub_izq()->altura - raiz->sub_der()->altura);
        if (balance > 1 && dato() < raiz->sub_izq()->dato()) {
            raiz = rotar_der(raiz);
        } else if (balance < -1 && dato() > sub_der()->dato()) {
            raiz = rotar_izq(raiz);
        } else if  (balance > 1 && dato() > sub_izq()->dato()){
            raiz->sub_izq()->operator=(rotar_izq(raiz->sub_izq()));
            raiz = rotar_der(raiz);            
        } else {
            raiz->sub_der()->operator=(rotar_der(sub_der()));
            raiz = rotar_izq(raiz);
        }
        
    }
    return raiz;
}

template <typename T> void Avl<T>::balancear () {
    if (!vacio()) {
        if (!balanceado()) {
            rotar();
        } else {

            this->sub_izq()->actualizar();
            this->sub_der()->actualizar();
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
        Avl * izq = new Avl();
        Avl * der = new Avl();
        primero = new Nodo (izq, der, elemento);
        actualizar_alturas(this);
    }
}



template class Avl<int>;
int main () {
    Avl<int> * arb = new Avl<int> ();
       
}