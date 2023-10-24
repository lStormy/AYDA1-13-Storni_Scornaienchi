//Source file

#include "lista.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Lista::Lista(){
	this->lista = NULL;
}

NodoLista * crear_nodo(int &dato) {
	NodoLista *nodo = new NodoLista();
	nodo->dato = dato;
	nodo->ste = NULL;
	return nodo;
}

void insertar_ordenado(NodoLista *&lista, NodoLista * pNodo){
	if ((lista == NULL) || (lista->dato >= pNodo->dato)){
		pNodo->ste = lista;
		lista = pNodo;
	} else 
		insertar_ordenado(lista->ste, pNodo);
}

void Lista::cargar_lista(){
	int dato;
	NodoLista * pNodo;
	cout << "Ingrese elementos a la lista: ";
	cin >> dato;
	while (dato > 0) {
		pNodo = crear_nodo(dato);
		insertar_ordenado(lista, pNodo);
		cout << "Ingrese elementos a la lista: ";
		cin >> dato;
	}
}

void mostrar_lista(NodoLista *pLista){
	if (pLista != NULL) {
		cout << pLista->dato << " ";
		mostrar_lista(pLista->ste);
	}
}

void Lista::ver_lista() const{
	cout << "\nmostrando lista: \n";
	mostrar_lista(lista);
}

bool Lista::eliminar_nodo(int dato) {
	//Caso 1 - Eliminamos el primer nodo.
	if ((lista != NULL) && (lista->dato == dato)){
		NodoLista * pEliminar = lista;
		lista = lista->ste;
		delete pEliminar;
		return true;
	} else { //Caso 2 - En medio 
		NodoLista * cursor = lista;
		while ((cursor->ste->dato != dato) && (cursor->ste != NULL))
		    cursor = cursor->ste;
		if (cursor->ste->dato == dato) {
			NodoLista * pEliminar = cursor->ste;
			cursor->ste = cursor->ste->ste;
			delete pEliminar;
			return true;
		} 
	}
	return false;
}

bool Lista::existe_nodo(int dato) const {
	NodoLista * cursor = lista;
	while ((cursor != NULL) || (cursor->dato != dato)) {
		cursor = cursor->ste;
	}
	return (cursor != NULL);
}

