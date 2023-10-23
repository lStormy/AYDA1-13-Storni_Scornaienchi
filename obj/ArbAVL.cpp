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
                const T & raiz () const {return dato;}
        };
        void vaciar (Avl<T> * raiz);
        
        Avl<T> * rotar(Avl<T> * raiz);
    private: 
        Nodo * primero;
        int altura;
        Avl<T> * rotar_izq (Avl<T> * raiz);
        Avl<T> * rotar_der (Avl<T> * raiz);
        void actualizar_alturas();
        void insertar (const T & elemento);
    public:
        Avl ();
        Avl (const Avl<T> *  otro);
        ~Avl () {vaciar (this);}
        Avl<T> * operator=(const Avl<T> & otro);
        Avl<T> * sub_izq() const {return primero->HijoIzq();}
        Avl<T> * sub_der() const {return primero->HijoDer();}
        const T & dato () const {return primero->raiz();}
        void agregar(const T & elemento) {
            this->insertar(elemento);
            this->actualizar_alturas();
            this->balancear();
        }
        bool balanceado () const;
        //void eliminar();
        int altura_nodo() const;
        bool vacio () const {return primero == NULL;}
        void balancear();
};

template <typename T> Avl<T>::Avl() {
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

template <typename T> Avl<T> * Avl<T>::operator=(const Avl<T> & otro) {
    vaciar (this);
    if (otro.vacio()) {
        cout << "Che toro, asigné un NULL " <<endl;
        primero = NULL;
        altura = 0;
    }
    else {
        cout << "Che toro, no asigné un NULL " <<endl;
        primero = new Nodo (otro.sub_izq(), otro.sub_der(), otro.dato());
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
    Avl<T> * aux (raiz->sub_der());
    Avl<T> * aux2 (aux->sub_izq());
    if (!aux2->vacio()) {
        cout << "ERROR ERROR" <<endl;
    } else {
        cout <<"Todo joya" <<endl;
        
    }
    cout << "Llegué hasta acá por lo menos?" <<endl;
    raiz->sub_der()->operator=(aux2);
    cout << "Hola" <<endl;
    aux->sub_izq()->operator=(raiz);
    
    cout << "Hola" <<endl;
    aux->actualizar_alturas();
    raiz->actualizar_alturas();
    return aux;
}

template <typename T> Avl<T> * Avl<T>::rotar_der (Avl<T> * raiz) {
    Avl * aux (raiz->sub_izq());
    Avl * aux2 (aux->sub_der());
    aux->sub_der()->operator=(aux);
    raiz->sub_izq()->operator=(aux2);
    aux->actualizar_alturas();
    raiz->actualizar_alturas();
    
    return raiz;
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

int getRandomNumber(int min, int max) {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    // Generate a random number between min and max
    return min + std::rand() % (max - min + 1);
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
void mostrar (Avl<int> * arb) {
    if (!arb->vacio()){
        cout << arb->dato() << " ";
        mostrar (arb->sub_izq());
        mostrar (arb->sub_der());
    }
}

void balance(const Avl<int> & arb) {
    if (arb.balanceado()) {
        cout <<"Está balanceado" <<endl;
    }
    else {
        cout << "No está balanceado" <<endl;
    }
}

template class Avl<int>;
int main () {
    Avl<int> * arb = new Avl<int> ();
    int dato = 0;
    do {
        cout << "Ingrese un dato al arreglo: ";
        cin >> dato;
        arb->agregar(dato);
        balance(*arb);
        mostrar(arb);
        cout <<endl;
    }while (dato > 0);
}