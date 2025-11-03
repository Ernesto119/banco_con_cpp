/*
sistema de banco en c++
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector> // Si quieres guardar los valores en un vector
#define BASE_DE_DATOS "database.csv"
using namespace std;

int obtener_indice_columna(stringstream& ss_header, const string& nombre_columna_buscada) {
    string campo_nombre;
    int indice = 0;
    
    while (getline(ss_header, campo_nombre, ',')) {
        if (campo_nombre == nombre_columna_buscada) {
            return indice;
        }
        indice++;
    }
    
    return -1;
}


// --- Programa Principal Ajustado ---
int main() {
    const string NOMBRE_ARCHIVO = BASE_DE_DATOS; 
    
    // 💡 CAMBIO CLAVE: Dos variables de entrada separadas
    string nombre_buscado;
    string contrasena_buscada; 
    bool encontrado = false;
    
    int indice_nombre = -1;
    int indice_contrasena = -1;

    // 1. Pedir el Nombre
    cout << "Ingrese su Nombre de Usuario: ";
    getline(cin, nombre_buscado); 
    
    // 2. Pedir la Contraseña
    cout << "Ingrese su Contrasena: ";
    getline(cin, contrasena_buscada); 
    
    cout << "Buscando credenciales para '" << nombre_buscado << "' en " << NOMBRE_ARCHIVO << "..." << endl;

    // 3. Abrir el archivo CSV
    ifstream archivo(NOMBRE_ARCHIVO);
    string linea;

    if (!archivo.is_open()) {
        cerr << "❌ Error: No se pudo abrir el archivo " << NOMBRE_ARCHIVO << "." << endl;
        return 1;
    }
    
    // 4. Leer y parsear el encabezado para obtener índices (se mantiene igual)
    if (getline(archivo, linea)) {
        stringstream ss_header(linea);
        
        indice_nombre = obtener_indice_columna(ss_header, "NOMBRE");
        
        ss_header.clear(); 
        ss_header.seekg(0); 
        indice_contrasena = obtener_indice_columna(ss_header, "CONTRASEÑA"); 
        
        if (indice_nombre == -1 || indice_contrasena == -1) {
            cerr << "❌ Error: No se encontró la columna 'Nombre' y/o 'Contrasena' en el encabezado." << endl;
            archivo.close();
            return 1;
        }
    } else {
        cerr << "❌ Error: El archivo está vacío o no se pudo leer el encabezado." << endl;
        archivo.close();
        return 1;
    }
    
    // 5. Leer y comparar el resto de las líneas (los datos)
    while (getline(archivo, linea) && !encontrado) { 
        
        stringstream ss(linea);
        string campo;
        vector<string> campos_de_linea; 

        // 5.1. Parsear y almacenar todos los campos
        while (getline(ss, campo, ',')) {
            campos_de_linea.push_back(campo);
        }

        // 5.2. Verificar y comparar los campos de Nombre y Contraseña
        if (campos_de_linea.size() > indice_nombre && campos_de_linea.size() > indice_contrasena) {
            
            string nombre_del_csv = campos_de_linea[indice_nombre];
            string contrasena_del_csv = campos_de_linea[indice_contrasena]; 
            
            // 🔑 LÓGICA DE DOBLE CONDICIÓN:
            // 1. Nombre del CSV debe coincidir con nombre_buscado.
            // 2. Contraseña del CSV debe coincidir con contrasena_buscada.
            if (nombre_del_csv == nombre_buscado && contrasena_del_csv == contrasena_buscada) {
                
                cout << "\n✅ OK. ¡Autenticación exitosa!" << endl;
                cout << "   -> Usuario: " << nombre_del_csv << endl;
                encontrado = true; 
            }
        }
    }

    // 6. Cerrar el archivo y reportar resultado
    archivo.close();

    if (!encontrado) {
        cout << "\n❌ Error de Autenticación: Nombre de usuario o Contraseña incorrectos." << endl;
    }
   
    return 0;
}