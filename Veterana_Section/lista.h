#include <iostream>

#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

template <typename T>
class Lista {
    protected:
        struct Nodo {
            T dato;
            Nodo * ste;
        };

    private:
        Nodo * primero;
        Nodo * nuevo (const T & dato);
        void vaciar (Nodo * lista);
        void imprimir_lista (Nodo * listita);

    public:
        //Constructoras
        Lista ();
        Lista (const Lista<T> & otro);

        //Destructora
        ~Lista();

        //Modificadoras
        void insertar (const T & dato);
        void eliminar (const int & pos);

        //Observadoras
        bool vacio () const;
        int len() const;
        const T & operator()(const int & pos) const;
        Lista<T>& operator= (const Lista<T>& otro) const;
        void mostrar () const;
        friend std::ostream& operator << (std::ostream&os, const Lista<T> & l);
};


#endif // LISTA_H_INCLUDED
