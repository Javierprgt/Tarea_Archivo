#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void menu(int& opc) {
	cout << "\033[2J\033[3J\033[1;1H";
	cout << "=== Archio ===" << endl;
	cout << " 1) Ingresar datos" << endl;
	cout << " 2) Mostrar Factura.txt" << endl;
	cout << " 3) Salir" << endl;
	cout << "Ingrese una opcion: "; cin >> opc;
	cin.ignore();
}

void ingresar() {
	cout << "\033[2J\033[3J\033[1;1H";
	int cantidad;
    string detalle;
    double valorUnitario, subtotal, iva, totalPagar;

    cout << "=== Generador de Factura ===" << endl;
    cout << "Detalle del producto: ";
    getline(cin, detalle);
    cout << "Cantidad: ";
    cin >> cantidad;
    cout << "Valor unitario: ";
    cin >> valorUnitario;
    subtotal = cantidad * valorUnitario;
    iva = subtotal * 0.15;
    totalPagar = subtotal + iva;

    ofstream archivo("factura.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "\n====== FACTURA GENERADA ======" << endl;
        archivo << "Detalle: " << detalle << endl;
        archivo << "Cantidad: " << cantidad << endl;
        archivo << "Valor Unitario: $" << valorUnitario << endl;
        archivo << "--------------------------------" << endl;
        archivo << "Subtotal: $" << subtotal << endl;
        archivo << "IVA (15%): $" << iva << endl;
        archivo << "TOTAL A PAGAR: $" << totalPagar << endl;
        archivo << "--------------------------------\n" << endl;

        archivo.close();
        cout << "\nDatos guardados con éxito!\n" << endl;
    } else {
        cout << "\nERROR: Al abrir el archivo!\n" << endl;
    }
    cin.ignore();
    cin.get();
}

void mostrar() {
	cout << "\033[2J\033[3J\033[1;1H";
	string linea;
	ifstream archivo("factura.txt");
	if (archivo.is_open()) {
		while (getline(archivo, linea)) {
			cout << linea << endl;
		}
		archivo.close();
	} else {
		cout << "\nERROR: Archivo no se puede abrir!\n";
	}
	cin.ignore();
	cin.get();
}

int main() {
    int opc = 0;
    do {
    	menu(opc);
    	switch (opc) {
    		case 1: { ingresar(); break; }
			case 2: { mostrar(); break; }
		}
    	
	} while (opc != 3);

    return 0;
}
