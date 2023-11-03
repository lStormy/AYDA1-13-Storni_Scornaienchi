#include "arbolAVL.h"
#include <iostream>
#include <string>
#include "agenda.h"
#include "contacto.h"

Agenda::Agenda() {
    contactos = new Avl<Contacto>();
}

Agenda::Agenda(const Agenda & otro) {
    contactos = otro.contactos;
}

void Agenda::cargar_contacto(const Contacto & elemento){
    contactos->agregar(elemento);
}


void Agenda::eliminar_contacto(const Contacto & elemento) {
    contactos->borrar(elemento);
}

void Agenda::recuperar(const string & nombre) const {
    Contacto nuevo = Contacto();
    nuevo.modificar_nombre(nombre);
    contactos->buscar(nuevo);
}
