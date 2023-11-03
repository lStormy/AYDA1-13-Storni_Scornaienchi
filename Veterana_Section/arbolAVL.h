#ifndef ARBOLAVL_H_INCLUDED
#define ARBOLAVL_H_INCLUDED

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
        Nodo * primero;
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
        Avl<T> * sub_izq() const;
        Avl<T> * sub_der() const;
        const T & dato () const;
        Avl<T> * operator=(const Avl<T> * otro);
        bool buscar (const T & dato) const; //Busca e imprime si lo encuentra
        int altura_nodo() const;
        void inorden() const;
        bool vacio () const;

        //Modificadoras
        void balancear();
        void agregar(const T & elemento);
        void borrar(const T & dato);
};

#endif // ARBOLAVL_H_INCLUDED
