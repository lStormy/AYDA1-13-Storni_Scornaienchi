#include "ArbAVL.cpp"
#include <iostream>
#include "Contacto.cpp"


class Agenda  {
    private:
        Avl<Contacto> * contactos;
        const Avl<Contacto> * encontrar (string apellido_nombre, Avl<Contacto> * con) const {
            if (!con->vacio()) {
                if (con->dato().apellido_nombre() == apellido_nombre) {
                    return con;
                } 
                else if (con->dato().apellido_nombre() < apellido_nombre) {
                    return encontrar (apellido_nombre, con->sub_der());
                } 
                else if (con->dato().apellido_nombre() > apellido_nombre) {
                    return encontrar(apellido_nombre, con->sub_izq());
                }
            } else {
                cout << "No existe el contacto" << endl;
                return new Avl<Contacto> ();
            }
        }

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
            Contacto del = Contacto (recuperar(elemento));
           
            contactos->borrar(del); 
        }
        const Contacto & recuperar(const string & apellido_nombre) const {
            assert (!contactos->vacio());
            if (contactos->dato().apellido_nombre() == apellido_nombre) {
                return contactos->dato();
            }
            else if (contactos->dato().apellido_nombre() > apellido_nombre) {
                return encontrar(apellido_nombre, contactos->sub_izq())->dato();
            }
            else if (contactos->dato().apellido_nombre() < apellido_nombre) {
                return encontrar(apellido_nombre, contactos->sub_der())->dato();
            }
        } 
        void mostrar_contactos () {
            contactos->inorden();
        }
};