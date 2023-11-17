#include "contacto.h"
#include <iostream>

using namespace std;

Contacto::Contacto(string & n, string & a, string & m, string & d, string & o, string & p, string & _notas, string & cel, string & c, Lista<string> &otro) {
            nombre = n;
            apellido = a;
            mail = m;
            direccion = d;
            organizacion = o;
            puesto = p;
            notas = _notas;
            numero = cel;
            cumple = c;
            links = otro;
}

Contacto::Contacto() {
    links = Lista<string>();
}

Contacto & Contacto::operator=(const Contacto & otro) {
            
    this->nombre = otro.nombre;
    this->apellido = otro.apellido;
    this->cumple = otro.cumple;
    this->direccion = otro.direccion;
    this->mail = otro.mail;
    this->notas = otro.notas;
    this->numero = otro.numero;
    this->organizacion = otro.organizacion;
    this->puesto = otro.puesto;
            
    this->links = Lista<string>(otro.links);
    return * this;
}

bool Contacto::operator >(const Contacto & otro) const {
    if (this->apellido != otro.apellido) {
        return this->apellido > otro.apellido;
    }
    else if (this->nombre != otro.nombre) {
        return this->nombre > otro.nombre;
    }
    return this->numero > otro.numero;
}

bool Contacto::operator <(const Contacto & otro) const {
    if (this->apellido != otro.apellido) {
        return this->apellido < otro.apellido;
    }
    else if (this->nombre != otro.nombre) {
        return this->nombre < otro.nombre;
    }
    return this->numero < otro.numero;
}

bool Contacto::operator== (const Contacto & otro) const {
    return ((this->nombre == otro.nombre) && (this->apellido == otro.apellido) && (this->numero == otro.numero));
}

const string Contacto::recuperar_apellido () const {
    return apellido;
}

const string Contacto::recuperar_nombre () const {
    return nombre;
}


