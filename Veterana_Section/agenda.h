#include "Contacto.h"
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
        void eliminar_contacto (const Contacto & elemento);
        void recuperar(const string & nombre) const;
};

#endif // AGENDA_H_INCLUDED
