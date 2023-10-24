void liberar_memoria(Nodo *&nodo) {
    delete nodo;
    nodo = NULL;
}

void reemplazar(Nodo *&arbol, Nodo *nuevoNodo) {
    if (arbol->padre) {
        if (arbol == arbol->padre->men) {
            arbol->padre->men = nuevoNodo;
        } 
		else if (arbol == arbol->padre->may) {
            arbol->padre->may = nuevoNodo;
        }
    }
    if (nuevoNodo) {
        nuevoNodo->padre = arbol->padre;
    }
}

Nodo *minimo(Nodo *arbol) {
    while (arbol->men) {
        arbol = arbol->men;
    }
    return arbol;
}

void eliminarNodo(Nodo *&arbol, int dato) {
    if (arbol == NULL) {
        return;
    }
	//Recorremos el arbol, buscando el nodo
    if (dato < arbol->dato) {
        eliminarNodo(arbol->men, dato);
    } else if (dato > arbol->dato) {
        eliminarNodo(arbol->may, dato);
    } else {
        // Nodo encontrado, proceder a eliminarlo
        if (arbol->men && arbol->may) {
            Nodo *menor = minimo(arbol->may); //Le mandas directamente la rama derecha
            arbol->dato = menor->dato; //Asignas valores
            eliminarNodo(arbol->may, menor->dato); //Llama a recursion
        } else {
            Nodo *nodoReemplazo = (arbol->men != NULL) ? arbol->men : arbol->may;
            if (arbol->padre == NULL) {
                arbol = nodoReemplazo; // El nodo a eliminar es la raíz
            } else {
                reemplazar(arbol, nodoReemplazo);
                liberar_memoria(arbol);
            }
        }
    }
}