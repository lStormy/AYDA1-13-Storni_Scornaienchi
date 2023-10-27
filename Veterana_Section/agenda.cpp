#include "arbolAVL.cpp"
#include <iostream>
#include "Contacto.cpp"


class Agenda  {
    private:
        Avl<Contacto> * contactos;
    public:
        Agenda() {
            contactos = new Avl<Contacto>();
        }
        Agenda(const Agenda & otro) {
            contactos = otro.contactos;
        }
        void cargar_contacto (const Contacto & elemento) {
            contactos->agregar(elemento);
        }
        void eliminar_contacto (const Contacto & elemento) {
            contactos->borrar(elemento);
        }
        void recuperar(const string & nombre) const {
            Contacto nuevo = Contacto();
            nuevo.modificar_nombre(nombre);
            contactos->buscar(nuevo);
        }
};
