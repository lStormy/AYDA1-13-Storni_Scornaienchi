#include "contacto.h"
#include "arbolAVL.h"

#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED

class Agenda  {
    private:
        Avl<Contacto> * contactos;
        
    public:
        Agenda();
        Agenda(const Agenda & otro);
        void cargar_contacto (const Contacto & elemento);
        void eliminar_contacto (const string & apellido, const string & nombre);
        void imprimir_contacto(const string & apellido, const string & nombre);
        void mostrar_contactos() const;
};

#endif // AGENDA_H_INCLUDED
