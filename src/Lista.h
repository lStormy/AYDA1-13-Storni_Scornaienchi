//Header file
#include
#ifndef LISTA_H
#define LISTA_H

template<typename T> class Lista {
	private:
		struct NodoLista {
			T dato;
			NodoLista *ste;
		}; 
		NodoLista * lista;
		
	public:
		Lista() {
			lista = new NodoLista();
			lista = NULL; 
			lista->ste = NULL;
		}	
		Lista (Lista<T> & otra) {
			lista = new NodoLista();
			lista->ste = otro->ste;
			lista->dato = otro->dato;
		}
		Lista<T> operator=(const Lista<T> & otro);	
		void insertar(const T & elemento)
		bool eliminar_nodo(int pos);
		bool existe_nodo(int dato) const;
		void ver_lista() const;
};

#endif //LISTA_H