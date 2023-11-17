#include "arbolAVL.h"
#include <iostream>
#include <string>
#include "agenda.h"
#include "contacto.h"
#include "arbolAVL.h"

//Constructor vacio
Agenda::Agenda() {
    contactos = new Avl<Contacto>();
}

//Constructor por copia
Agenda::Agenda(const Agenda & otro) {
    contactos = otro.contactos;
}

//Constructora basica
void Agenda::cargar_contacto(const Contacto & elemento){
    contactos->agregar(elemento);
}

//Modificadora
void Agenda::eliminar_contacto(const string & apellido,const string & nombre) {
    /*
    Dado un contacto lo elimina del arbol
    */
    Contacto del = Contacto();
    del.cambiar_nombre_apellido(apellido, nombre);
    if (contactos->buscar(del)) {
        contactos->borrar(del); 
    }
}

void Agenda::imprimir_contacto(const string & apellido, const string & nombre) {
    Contacto aux = Contacto();
    aux.cambiar_nombre_apellido(apellido, nombre);
    contactos->buscar(aux);
}

void Agenda::mostrar_contactos() const {
    contactos->inorden();
}
