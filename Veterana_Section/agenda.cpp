#include "arbolAVL.h"
#include <iostream>
#include <string>
#include "agenda.h"
#include "contacto.h"

template <typename Contacto>
Agenda<Contacto>::Agenda() {
    contactos = new Avl<Contacto>();
}

template <typename Contacto>
Agenda<Contacto>::Agenda(const Agenda & otro) {
    contactos = otro.contactos;
}

template <typename Contacto>
void Agenda<Contacto>::cargar_contacto(const Contacto & elemento){
    contactos->agregar(elemento);
}

template <typename Contacto>
void Agenda<Contacto>::eliminar_contacto(const Contacto & elemento) {
    contactos->borrar(elemento);
}

template <typename Contacto>
void Agenda<Contacto>::recuperar(const string & nombre) const {
    Contacto nuevo = Contacto();
    nuevo.modificar_nombre(nombre);
    contactos->buscar(nuevo);
}








