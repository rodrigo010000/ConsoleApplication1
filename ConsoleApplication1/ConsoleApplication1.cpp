#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class MiembroClub {
private:
    string nombre;
    int edad;
    string correo;

public:
    // Constructor que inicializa los atributos del miembro
    MiembroClub(string nombre, int edad, string correo) {
        this->nombre = nombre;
        this->edad = edad;
        this->correo = correo;
    }

    // Método para guardar los datos del miembro en un archivo
    void guardarEnArchivo() {
        ofstream archivo("club.txt", ios::app); // Abrir archivo en modo "append"
        if (archivo.is_open()) {
            archivo << nombre << "," << edad << "," << correo << "\n";
            archivo.close();
            cout << "Miembro guardado en el archivo." << endl;
        }
        else {
            cout << "No se pudo abrir el archivo para guardar." << endl;
        }
    }

    // Método para leer y mostrar los datos guardados en el archivo
    static void leerDesdeArchivo() {
        ifstream archivo("club.txt");
        string linea;
        if (archivo.is_open()) {
            while (getline(archivo, linea)) {
                stringstream ss(linea);
                string nombre, correo;
                int edad;
                getline(ss, nombre, ',');
                ss >> edad;
                ss.ignore(); // Ignorar la coma
                getline(ss, correo);
                cout << "Nombre: " << nombre << ", Edad: " << edad << ", Correo: " << correo << endl;
            }
            archivo.close();
        }
        else {
            cout << "El archivo 'club.txt' no existe o no se pudo abrir." << endl;
        }
    }

    // Método para actualizar la información de un miembro
    static void actualizarMiembro(string nombre, int nuevaEdad, string nuevoCorreo) {
        ifstream archivo("club.txt");
        vector<string> lineas;
        string linea;
        bool encontrado = false;

        if (archivo.is_open()) {
            while (getline(archivo, linea)) {
                stringstream ss(linea);
                string n, correo;
                int edad;
                getline(ss, n, ',');
                ss >> edad;
                ss.ignore();
                getline(ss, correo);

                // Si encontramos el miembro por nombre, actualizamos los datos
                if (n == nombre) {
                    encontrado = true;
                    lineas.push_back(n + "," + to_string(nuevaEdad) + "," + nuevoCorreo);
                }
                else {
                    lineas.push_back(linea);
                }
            }
            archivo.close();

            // Si se encontró el miembro, sobrescribimos el archivo con los cambios
            if (encontrado) {
                ofstream archivo("club.txt", ios::trunc); // Abrir archivo en modo "truncate"
                if (archivo.is_open()) {
                    for (const string& l : lineas) {
                        archivo << l << "\n";
                    }
                    archivo.close();
                    cout << "Miembro " << nombre << " actualizado." << endl;
                }
                else {
                    cout << "No se pudo abrir el archivo para actualizar." << endl;
                }
            }
            else {
                cout << "No se encontró el miembro con el nombre " << nombre << "." << endl;
            }
        }
        else {
            cout << "El archivo 'club.txt' no existe o no se pudo abrir." << endl;
        }
    }

    // Método para eliminar un miembro del archivo
    static void eliminarMiembro(string nombre) {
        ifstream archivo("club.txt");
        vector<string> lineas;
        string linea;
        bool encontrado = false;

        if (archivo.is_open()) {
            while (getline(archivo, linea)) {
                stringstream ss(linea);
                string n, correo;
                int edad;
                getline(ss, n, ',');
                ss >> edad;
                ss.ignore();
                getline(ss, correo);

                // Si el nombre no coincide, agregamos la línea al vector
                if (n != nombre) {
                    lineas.push_back(linea);
                }
                else {
                    encontrado = true;
                }
            }
            archivo.close();

            // Si se encontró el miembro, sobrescribimos el archivo sin él
            if (encontrado) {
                ofstream archivo("club.txt", ios::trunc); // Abrir archivo en modo "truncate"
                if (archivo.is_open()) {
                    for (const string& l : lineas) {
                        archivo << l << "\n";
                    }
                    archivo.close();
                    cout << "Miembro " << nombre << " eliminado." << endl;
                }
                else {
                    cout << "No se pudo abrir el archivo para eliminar." << endl;
                }
            }
            else {
                cout << "No se encontró el miembro con el nombre " << nombre << "." << endl;
            }
        }
        else {
            cout << "El archivo 'club.txt' no existe o no se pudo abrir." << endl;
        }
    }
};

int main() {
    // Crear un miembro y guardarlo en el archivo
    MiembroClub miembro1("Juan Perez", 30, "juan.perez@email.com");
    miembro1.guardarEnArchivo();

    // Mostrar los miembros guardados
    cout << "\nMiembros guardados:\n";
    MiembroClub::leerDesdeArchivo();

    // Actualizar un miembro
    cout << "\nActualizando miembro...\n";
    MiembroClub::actualizarMiembro("Juan Perez", 31, "juan.perez@nuevoemail.com");

    // Mostrar los miembros después de la actualización
    cout << "\nMiembros después de la actualización:\n";
    MiembroClub::leerDesdeArchivo();

    // Eliminar un miembro
    cout << "\nEliminando miembro...\n";
    MiembroClub::eliminarMiembro("Juan Perez");

    // Mostrar los miembros después de la eliminación
    cout << "\nMiembros después de la eliminación:\n";
    MiembroClub::leerDesdeArchivo();

    return 0;
}

