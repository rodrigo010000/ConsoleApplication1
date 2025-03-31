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
        } else {
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
        } else {
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
                } else {
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
                } else {
                    cout << "No se pudo abrir el archivo para actualizar." << endl;
                }
            } else {
                cout << "No se encontró el miembro con el nombre " << nombre << "." << endl;
            }
        } else {
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
                } else {
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
                } else {
                    cout << "No se pudo abrir el archivo para eliminar." << endl;
                }
            } else {
                cout << "No se encontró el miembro con el nombre " << nombre << "." << endl;
            }
        } else {
            cout << "El archivo 'club.txt' no existe o no se pudo abrir." << endl;
        }
    }
};

int main() {
    int opcion;
    string nombre, correo;
    int edad;

    do {
        cout << "\n--- Menu del Club ---\n";
        cout << "1. Agregar nuevo miembro\n";
        cout << "2. Mostrar miembros\n";
        cout << "3. Actualizar miembro\n";
        cout << "4. Eliminar miembro\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Agregar nuevo miembro
                cout << "Ingrese el nombre del nuevo miembro: ";
                cin.ignore(); // Para ignorar el salto de línea anterior
                getline(cin, nombre);
                cout << "Ingrese la edad: ";
                cin >> edad;
                cout << "Ingrese el correo: ";
                cin.ignore(); // Para ignorar el salto de línea anterior
                getline(cin, correo);

                {
                    MiembroClub nuevoMiembro(nombre, edad, correo);
                    nuevoMiembro.guardarEnArchivo();
                }
                break;

            case 2:
                // Mostrar miembros
                cout << "\n--- Miembros en el club ---\n";
                MiembroClub::leerDesdeArchivo();
                break;

            case 3:
                // Actualizar miembro
                cout << "Ingrese el nombre del miembro a actualizar: ";
                cin.ignore(); // Para ignorar el salto de línea anterior
                getline(cin, nombre);
                cout << "Ingrese la nueva edad: ";
                cin >> edad;
                cout << "Ingrese el nuevo correo: ";
                cin.ignore(); // Para ignorar el salto de línea anterior
                getline(cin, correo);

                MiembroClub::actualizarMiembro(nombre, edad, correo);
                break;

            case 4:
                // Eliminar miembro
                cout << "Ingrese el nombre del miembro a eliminar: ";
                cin.ignore(); // Para ignorar el salto de línea anterior
                getline(cin, nombre);

                MiembroClub::eliminarMiembro(nombre);
                break;

            case 5:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no válida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}


