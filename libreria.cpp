#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void mostrarlibros()
{
    ifstream archivo("libros.txt");
    string linea;

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    cout << "\n=== Contenido de la libros ===" << endl;
    while (getline(archivo, linea))
    {
        cout << linea << endl;
    }
    cout << "--------------------------------------------------\n"
         << endl;

    archivo.close();
}

void agregarLibro()
{
    float precio;
    string nombre, codigo;

    cout << "ingrese el codigo del libro: ";
    cin >> codigo;
    cout << "ingrese el nombre del libro: ";
    cin >> nombre;
    cout << "ingrese el precio del libro: ";
    cin >> precio;

    ofstream libros("libros.txt", std::ios::app);
    libros << codigo << " " << nombre << " RD$" << precio << "\n";
    libros.close();

    cout << "Libro agregado exitosamente." << endl;
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void limpiarPantalla()
{
    system("clear");
}

int main()
{
    int opcion = 0;

    while (opcion != 3)
    {
        cout << "\n=== Menu Principal ===" << endl;
        cout << "1. Agregar libro" << endl;
        cout << "2. Mostrar libros" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Validar si la entrada fue un número válido
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida. Intente de nuevo." << endl;
            continue;
        }

        switch (opcion)
        {
        case 1:
            limpiarPantalla();
            agregarLibro();
            limpiarPantalla();
            break;
        case 2:
            limpiarPantalla();
            mostrarlibros();
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        case 3:
            limpiarPantalla();
            cout << "¡Hasta luego!" << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    }

    return 0;
}