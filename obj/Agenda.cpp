#include "ArbAVL.cpp"
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
            /*
            Dado un contacto lo inserta en el arbol y lo rota si es necesario.
            */
            contactos->agregar(elemento);
        }
        void eliminar_contacto (const string & elemento) {
            /*
            Dado un contacto lo elimina del arbol
            */
            Contacto del;
            del.modificar_nombre(elemento);
            contactos->borrar(del);
        
        }
        void recuperar(const string & nombre) const {
            Contacto nuevo = Contacto();
            nuevo.modificar_nombre(nombre);
            contactos->buscar(nuevo);
            
        } 
        void mostrar_contactos () {
            contactos->inorden();
        }
};