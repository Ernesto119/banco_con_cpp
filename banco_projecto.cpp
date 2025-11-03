#include <iostream>
#include <cstdlib> // Necesario para system()
#include <limits>  // 
using namespace std;

void limpiar_pantalla() {
    // Si el sistema es Windows, ejecuta "cls"
    #ifdef _WIN32
        system("cls");
    // Si es cualquier otro sistema (Linux, macOS), ejecuta "clear"
    #else
        system("clear");
    #endif
}

void esperar_enter() {
    // Limpia el búfer de entrada de cualquier caracter sobrante (como el Enter anterior)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPresiona ENTER para continuar...";
    cin.get(); 
}

int main() {
    
    int monto = 0, seleccion,ajuste;

    while (true)
    {
        limpiar_pantalla();
        cout << "1.Consulta\n2.Depositar\n3.Retirar\n4.Tranferir\n5.Salir";
        cout << "\nSeleccione: ";
        cin >> seleccion;
        limpiar_pantalla(); 

        switch (seleccion) {
            case 1:
                cout << monto;
                esperar_enter();
                break;
            case 2:
                cout <<"ingrese el monto a depositar: ";
                cin >> ajuste;
                monto = monto + ajuste;
                esperar_enter();
                break;
            case 3:
                cout << "cuanto quiere sacar. ";
                cin >> ajuste;
                if (ajuste > monto)
                {
                    cout << "dinero insuficiente: ";
                     esperar_enter();
                } else 
                {
                    monto = monto - ajuste;
                }
                
                break;
            case 4:
                cout << "ingrse el numero de cuenta: ";
                cin >> seleccion;
                cout << "cuanto quiere transferir: ";
                cin >> ajuste;
                if (ajuste > monto)
                {
                    cout << "dinero insuficiente: ";
                     esperar_enter();
                } else 
                {
                    monto = monto - ajuste;
                }
                break;
            case 5:
                return 0;
            
            default:
                cout << "opcion invalida." << endl;
                break;
            }
    }
    return 0;
}