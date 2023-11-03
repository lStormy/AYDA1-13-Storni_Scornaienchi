#include <iostream>
#include <fstream>
#include <clocale>

using namespace std;

/**
 * Abre el archivo según el origen, procesa las líneas del mismo y
 * almacena la información resultante en el contenedor pasado por referencia.
 **/
void procesar_archivo_entrada(string origen);//, Contenedor & contenedor);

int main()
{
    setlocale(LC_ALL, ""); //asegurarse que el archivo de texto fue guardado como Ansi y no como Unicode
    procesar_archivo_entrada("contactos.csv");
    return 0;
}

//Comentarios: atoi y atof requieren un char * para converter a número, usamos c_str de la clase string.
void procesar_archivo_entrada(string origen)
{
    ifstream archivo(origen);
    if (!archivo.is_open())
        cout << "No se pudo abrir el archivo: " << origen << endl;
    else {
        string linea;
        getline(archivo, linea);
        int cantidad_contactos = atoi(linea.c_str());
        cout << "Se cargarán " << cantidad_contactos << " contactos." << endl;

        //Leemos de una linea completa por vez (getline).
        int nroContacto = 1;
        while (getline(archivo, linea)) {
            //Primer posición del separador ;
            int pos_inicial = 0;
            int pos_final = linea.find(',');


            //Informacion entre pos_inicial y pos_final
            string nombre = linea.substr(pos_inicial, pos_final);

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

            cout << "CONTACTO "<< nroContacto << ": "<< nombre  << endl;
            cout << "   TE: " << telefono << endl;
            cout << "   MAIL: " << email << endl;
            cout << "   DIRECCION: " << direccion << endl;
            cout << "   FECHA NAC: " << fecha_nacimiento<<endl;
            cout << "   ORGANIZACION: " << organizacion<< endl;
            cout << "   PUESTO: " << puesto<< endl;
            cout << "   NOTAS: " << notas <<endl;

            cout << "   REDES: " << lst_redes<<endl;

            //TO DO: Completar la lectura separada de las redes de la cancion


            nroContacto++;
        }
    }
}

