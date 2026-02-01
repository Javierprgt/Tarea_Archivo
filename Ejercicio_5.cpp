#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Helado {
    string codigo;
    string sabor;
    double precio;
};

void menu(int& opc) {
	cout << "\033[2J\033[3J\033[1;1H";
	cout << "=== Heladeria ===" << endl;
	cout << " 1) Ingresar 10 helados" << endl;
	cout << " 2) Analizar ventas" << endl;
	cout << " 3) Salir" << endl;
	cout << "Ingrese una opcion: "; cin >> opc;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void registrarVentas() {
	cout << "\033[2J\033[3J\033[1;1H";
    ofstream archivo("ventas_helados.txt", ios::app);
    if (!archivo.is_open()) return;

    cout << "=== Registro de 10 Ventas de Helados ===\n";
    for (int i = 0; i < 10; i++) {
        Helado h;
        cout << "\nHelado #" << i + 1 << endl;
        cout << "Código: "; cin >> h.codigo;
        cout << "Sabor: "; cin.ignore(); getline(cin, h.sabor);
        cout << "Precio: "; cin >> h.precio;

        archivo << h.codigo << "," << h.sabor << "," << h.precio << endl;
    }
    archivo.close();
    cout << "\n¡Datos guardados exitosamente!\n";
    cin.get();
}

void procesarInformacion() {
	cout << "\033[2J\033[3J\033[1;1H";
    ifstream archivo("ventas_helados.txt");
    string linea, dato;
    vector<Helado> inventario;

    if (!archivo.is_open()) {
        cout << "Error: No existe el archivo de ventas." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        Helado h;
        size_t p1 = linea.find(",");
        size_t p2 = linea.find(",", p1 + 1);

        h.codigo = linea.substr(0, p1);
        h.sabor = linea.substr(p1 + 1, p2 - p1 - 1);
        h.precio = stod(linea.substr(p2 + 1));
        inventario.push_back(h);
    }
    archivo.close();

    double sumaTotal = 0;
    Helado masBarato = inventario[0];
    bool encontradoMora = false;

    cout << "\n=== RESULTADOS DEL ANALISIS ===\n";
    cout << fixed << setprecision(2);

    for (const auto& h : inventario) {
        sumaTotal += h.precio;

        if (h.precio < masBarato.precio) {
            masBarato = h;
        }

        string saborMin = h.sabor;
        transform(saborMin.begin(), saborMin.end(), saborMin.begin(), ::tolower);
        if (saborMin == "mora") {
            cout << "[MORA DETECTADO] Cod: " << h.codigo << " | Precio: $" << h.precio << endl;
            encontradoMora = true;
        }
    }

    if (!encontradoMora) cout << "No se registraron helados de sabor Mora." << endl;

    cout << "\nHelado con precio más bajo: " << masBarato.sabor << " ($" << masBarato.precio << ")" << endl;
    cout << "Suma total de ventas: $" << sumaTotal << endl;
    cin.get();
}

int main() {
    int opc = 0;
    do {
        menu(opc);
        switch (opc) {
			case 1: { registrarVentas(); break;}
			case 2: { procesarInformacion(); break; }
		}
    } while (opc != 3);

    return 0;
}
