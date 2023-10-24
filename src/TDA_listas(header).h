//Header file

#ifndef LISTA_H
#define LISTA_H

struct NodoLista {
	int dato;
	NodoLista *ste;
};

class Lista {
	private: 
		NodoLista * lista;
		
	public:
		Lista();		
		void cargar_lista();
		bool eliminar_nodo(int dato);
		bool existe_nodo(int dato) const;
		bool eliminar_nodo();
		void ver_lista() const;
};

#endif //LISTA_H