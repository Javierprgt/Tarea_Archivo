#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void menu(int& opc) {
	cout << "\033[2J\033[3J\033[1;1H";
	cout << "=== Archio ===" << endl;
	cout << " 1) Ingresar materia" << endl;
	cout << " 2) Mostrar materias" << endl;
	cout << " 3) Salir" << endl;
	cout << "Ingrese una opcion: "; cin >> opc;
	cin.ignore();
}

void agregarMateria() {
    cout << "\033[2J\033[1;1H";
    string nombreMateria, codigo;
    ofstream archivo("materias.txt", ios::app);
    
    if (archivo.is_open()) {
        cout << "=== Registrar Nueva Materia ===" << endl;
        cout << "Nombre de la materia: ";
        getline(cin, nombreMateria);
        cout << "Codigo de la materia: ";
        getline(cin, codigo);
        
        archivo << "Codigo: " << codigo << " | Materia: " << nombreMateria << endl;
        archivo.close();
        cout << "\nMateria guardada exitosamente!\n" << endl;
    } else {
        cout << "\nERROR: Al abrir el archivo de materias!\n" << endl;
    }
    cin.get();
}

void verMaterias() {
    cout << "\033[2J\033[1;1H";
    string linea;
    ifstream archivo("materias.txt");
    
    cout << "=== Lista de Materias Registradas ===" << endl;
    if (archivo.is_open()) {
        bool vacio = true;
        while (getline(archivo, linea)) {
            cout << "- " << linea << endl;
            vacio = false;
        }
        if (vacio) cout << "No hay materias registradas aun." << endl;
        archivo.close();
    } else {
        cout << "El archivo no existe o no se puede leer." << endl;
    }
    cout << "\nPresione Enter para volver...";
    cin.get();
}

int main() {
    int opc;
    do {
        menu(opc);
        switch (opc) {
            case 1: { agregarMateria(); break; }
            case 2: { verMaterias(); break; }
        }
    } while (opc != 3);
    
    return 0;
}
