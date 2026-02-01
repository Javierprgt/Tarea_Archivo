#include <iostream>
#include <fstream>
using namespace std;

void calcularProductoEscalar() {
    int k = 0;
    int arreglo[] = {10, 20, 30, 40, 50};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);
    
    cout << "=== Producto escalar ===" << endl;
    cout << "-Ingrese una variable k: "; cin >> k;
    cin.ignore();
    
    ofstream archivo("producto_escalar.txt");
    if (archivo.is_open()) {
        cout << "\nCalculando producto escalar..." << endl;
        archivo << "Valor de k: " << k << endl;
        archivo << "Arreglo original: [";
        for(int i = 0; i < n; i++) {
            archivo << arreglo[i] << (i == n - 1 ? "" : ", ");
        }
        archivo << "]" << endl;

        archivo << "Resultado (pe): [";
        for(int i = 0; i < n; i++) {
            int resultado = k * arreglo[i];
            archivo << resultado << (i == n - 1 ? "" : ", ");
        }
        archivo << "]" << endl;

        archivo.close();
        cout << "\nResultado guardado en 'producto_escalar.txt'\n" << endl;
    } else {
        cout << "\nERROR: Al crear el archivo!\n" << endl;
    }
}

void mostrar() {
	string linea;
	ifstream archivo("producto_escalar.txt");
	cout << "\n===== Resultado =====" << endl;
	if (archivo.is_open()) {
		while(getline(archivo, linea)){
			cout << "- " << linea << endl;
		}
	}
	archivo.close();
	}

int main() {
    calcularProductoEscalar();
    mostrar();
    return 0;
}
