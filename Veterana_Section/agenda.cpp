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
    Contacto del = Contacto (recuperar(apellido, nombre));
    if (del.recuperar_apellido() != " " && del.recuperar_nombre() != " ") {
        contactos->borrar(del); 
    }   
}

const Avl<Contacto> * Agenda::encontrar (const string & apellido, const string & nombre, Avl<Contacto> * con) const {
            /*
            Esta función fue hecha para poder encontrar un contacto dado un nombre y un apellido. El problema estaba en que necesitabamos todos los datos d
            */
            if (!con->vacio()) {
                if(con->dato().recuperar_apellido() == apellido) { //Es necesario hacer la misma comparación de antes.
                    if (con->dato().recuperar_nombre() == nombre) {
                        return con;
                    }
                    else {
                        if (con->dato().recuperar_nombre() > nombre) {
                            return encontrar(apellido, nombre, con->sub_izq());
                        }
                        else {
                            return encontrar(apellido, nombre, con->sub_der());
                        }
                    }
                }
                else {
                    if (con->dato().recuperar_apellido() < apellido) {
                        return encontrar(apellido, nombre, con->sub_der());
                    }
                    else {
                        return encontrar(apellido, nombre, con->sub_izq());
                    }
                }
            }           
            cout << "[NO EXISTE EL CONTACTO]" <<endl;
            return (new Avl<Contacto> ());
        }


//Observadoras
const Contacto & Agenda::recuperar(const string & apellido, const string & nombre) const {
    if (contactos->dato().recuperar_apellido() == apellido) { //El arbol está ordenado por apellido, después por nombre.
        if (contactos->dato().recuperar_nombre() == nombre) {
            return contactos->dato();
        }
        else {
            return encontrar(apellido, nombre, contactos)->dato();
        }
    } 
    else { 
    /*
    El apellido no es igual, comparamos si es mayor o menor y llamamos a encontrar. Además verificamos que el arbol que devuelva no este vacío
    Si el arbol que devuelve la función encontrar está vacío significa que el contacto no existe en la agenda. Por lo tanto tendríamos que devolver un tipo contacto vacío.
    */
        if (contactos->dato().recuperar_apellido() < apellido) {
            const Avl<Contacto> * aux = new Avl<Contacto>();
            aux = encontrar(apellido, nombre, contactos->sub_der());
            if (!aux->vacio()) {
                return aux->dato();
            }
        }
        else if (contactos->dato().recuperar_apellido() > apellido) {
            const Avl<Contacto> * aux = new Avl<Contacto>();
            aux = encontrar (apellido, nombre, contactos->sub_izq());
            if (!aux->vacio()){
                return aux->dato();
            }
        }
    }
            
    //Si el programa llegó hasta esta instancia significa que el contacto no existe.
    return Contacto(); //Devolvemos un contacto vacío para que no nos de un error a la hora de compilarlo
}

void Agenda::mostrar_contactos() const {
    contactos->inorden();
}
