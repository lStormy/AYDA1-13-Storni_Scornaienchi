#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
#include <stdlib.h>
#include "agenda.h"


using namespace std;

/**
 * Abre el archivo según el origen, procesa las líneas del mismo y
 * almacena la información resultante en el contenedor pasado por referencia.
 **/

void separar_nombre_apellido(const string & nombre_apellid, string & nombre, string & apellido);
void cargar_links (Lista<string> & links, string redes);
void procesar_archivo_entrada(string origen, Agenda constactos);//, Contenedor & contenedor);
void cargar_links_consola (Lista<string> & links);
void acciones(Agenda & contactos, int opcion);
void menu(Agenda & contactos);


int main() {
    Agenda contactos;
    setlocale(LC_ALL, ""); //asegurarse que el archivo de texto fue guardado como Ansi y no como Unicode
    procesar_archivo_entrada("contactos.csv", contactos);
    menu(contactos);
    return 0;
}

void separar_nombre_apellido (const string & nombre_apellido, string & nombre, string & apellido) {
    bool cambio = false; //Marca cuando cambia de nombre a apellido. Si es false significa que seguimos cargando el nombre
    for (int i = 0; nombre_apellido[i] != '\0'; i++) {
        if (nombre_apellido[i] == ' ') {
            cambio = true;
        }
        if (!cambio) {
            if (nombre == " ") {
                nombre = nombre_apellido[i];
            }
            else {
                nombre += nombre_apellido[i];
            }
        }
        else {
            if (apellido == " ") {
                apellido = nombre_apellido[i];
            }
            else {
                apellido += nombre_apellido[i];
            }
            
        }
    }
}

void cargar_links (Lista<string> & links, string redes) {
    string aux(" ");
    for (int i = 1; redes[i] != '\0'; i++) {
        if ((redes[i] == ';') || (redes[i] == ']')) {
            links.insertar(aux);
            aux = " ";
        } else {
            aux += redes[i];
        }
    }
}


//Comentarios: atoi y atof requieren un char * para converter a número, usamos c_str de la clase string.
void procesar_archivo_entrada(string origen, Agenda contactos) {
    ifstream archivo(origen);
    if (!archivo.is_open())
        cout << "No se pudo abrir el archivo: " << origen << endl;
    else {
        string linea;
        getline(archivo, linea);
        int cantidad_contactos = atoi(linea.c_str());
        cout << "Se cargarón " << cantidad_contactos << " contactos." << endl;

        //Leemos de una linea completa por vez (getline).
        int nroContacto = 1;
        while (getline(archivo, linea)) {
            //Primer posición del separador ;
            int pos_inicial = 0;
            int pos_final = linea.find(',');

            
            //Informacion entre pos_inicial y pos_final
            string nombre_apellido = linea.substr(pos_inicial, pos_final);
            string nombre (" ");
            string apellido (" ");
            
            separar_nombre_apellido(nombre_apellido, nombre, apellido);

             //Segunda posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(',', pos_inicial);
            string telefono = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Tercera posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(',', pos_inicial);
            string email = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Cuarta posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(',', pos_inicial);
            string direccion = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Quinta posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(',', pos_inicial);
            string fecha_nacimiento = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Sexta posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(',', pos_inicial);
            string organizacion = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Septima posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(',', pos_inicial);
            string puesto = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Octava posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(',', pos_inicial);
            string notas = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Novena posición del separador ;
             //LISTA de REDES
            pos_inicial = pos_final + 1;
            pos_final = linea.find(',', pos_inicial);

            string lst_redes = linea.substr(pos_inicial, pos_final - pos_inicial);
            Lista<string> lista_redes = Lista<string> ();
            
            cargar_links(lista_redes, lst_redes);
            Contacto aux = Contacto (nombre, apellido, email, direccion, organizacion, puesto, notas, telefono, fecha_nacimiento, lista_redes);
            contactos.cargar_contacto(aux);
            
            nroContacto++;
            
        }
    }
}

void cargar_links_consola (Lista<string> & lista) {
    cout << "<Inicio de carga de Links>" << endl;
    string link(" ");
    int seguir = 1;
    while (seguir == 1)  {
        cout << "Ingrese el link sin espacio: ";
        cin >> link;
        lista.insertar(link);
        cout << "Quiere seguir cargando?\n1: si\n0:no\nCargue: ";
        cin >> seguir;
        while (seguir != 0 && seguir != 1) {
            cout << "Ingreso invalido: ";
            cin >> seguir;
        }
    }
}


void acciones (Agenda & contactos, int opcion) {
    string nombre(" ");
    string apellido (" ");
    Contacto aux;
    switch (opcion) {
            case 1: 
                cout << "Ingrese el nombre y el apellido separado con espacios: ";
                cin >> nombre;
                cin >> apellido;
                cout << endl;
                contactos.eliminar_contacto(apellido, nombre);
                break;
            case 2: 
                cout << "Ingrese el nombre y apellido con espacios: ";
                cin >> nombre;
                cin >> apellido;
                cout << endl;
                aux = contactos.recuperar(apellido, nombre);
                cout << "hola" << endl;
                if (aux.recuperar_apellido() != " ") {
                    cout << aux << endl;
                }
                break;
            case 3:
                contactos.mostrar_contactos();
                break;
            case 4: 
                string mail, direccion,  organizacion, puesto, notas, numero, cumple;
                Lista<string> links;
                int cargar = 0;
                cout << "<Cargue los datos del contacto>" << endl;
                cout << "Nombre: ";
                cin >> nombre;
                cout << endl;
                cout << "Apellido: ";
                cin >> apellido;
                cout << endl;
                cout << "Mail: ";
                cin >> mail;
                cout << endl;
                cout << "Dirección: ";
                cin >> direccion;
                cout << endl;
                cout << "Organización: ";
                cin >> organizacion;
                cout << endl;
                cout << "Puesto: ";
                cin >> puesto;
                cout << endl;
                cout << "Notas: ";
                cin >> notas;
                cout << endl; 
                cout << "Numero: ";
                cin >> numero;
                cout << endl;
                cout << "Fecha de cumpleaños: ";
                cin >> cumple;
                cout << endl;
                cout << "¿Quiere cargar links de redes sociales?\n0: No\n1:Si\ninsertar: ";
                cin >> cargar;
                while (cargar !=0 && cargar != 1) {
                    cout << "Valor incorrecto. Cargue denuevo: ";
                    cin >> cargar;
                }
                if (cargar == 1) {
                    cargar_links_consola(links);
                }
                cout << "<fin de carga>" << endl;
                contactos.cargar_contacto(Contacto(nombre, apellido, mail, direccion, organizacion, puesto, notas, numero, cumple, links));
                break;
        }
}

void menu(Agenda & contactos) {
    int opcion = 3;
    while ((opcion >= 1 && opcion <= 4)) {
        cout << "<Ingrese la acción que quiera llevar a cabo>" << endl;
        cout << "Eliminar un contacto: 1." << endl;
        cout << "Recuperar un contacto dado un nombre: 2." << endl;
        cout << "Mostrar todos los contactos: 3." << endl;
        cout << "Agregar un contacto: 4" << endl;
        cout << "Salir: Un número que no esté en las opciones. " <<endl;
        cout << "Ingrese: ";
        cin >> opcion;
        cout << "<Fin>" << endl;
        system("clear");
        acciones(contactos, opcion);
    }
}