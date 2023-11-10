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
void Agenda::eliminar_contacto(const Contacto & elemento) {
    contactos->borrar(elemento);
}

//Observadoras
void Agenda::recuperar(const string & nombre) const {
    Contacto nuevo = Contacto();
    nuevo.modificar_nombre(nombre);
    contactos->buscar(nuevo);
}

void Agenda::mostrar_contactos() const {
    contactos->inorden();
}
