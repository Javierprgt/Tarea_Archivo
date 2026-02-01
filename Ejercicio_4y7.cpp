#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
using namespace std;

struct Caracteristicas {
	string tipo;
	string codigo;
	string titulo;
	int anio;
	bool estado = false;
};
vector<Caracteristicas> biblioteca;

void menu(int& opc) {
	cout << "\033[2J\033[3J\033[1;1H";
	cout << "=== Biblioteca ===" << endl;
	cout << " 1) Ingresar Libro" << endl;
	cout << " 2) Prestar libro" << endl;
	cout << " 3) Devolver libro" << endl;
	cout << " 4) Mostrar libros" << endl;
	cout << " 5) Salir" << endl;
	cout << "Ingrese una opcion: "; cin >> opc;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void capitalizar(string& s) {
    if (s.empty()) {
        return;
    }
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    s[0] = static_cast<char>(toupper(static_cast<unsigned char>(s[0])));
}

void guardarTodo() {
    ofstream stock("LibrosEnStock.txt", ios::trunc);
    ofstream prestados("LibrosPrestados.txt", ios::trunc);

    for (const auto& b : biblioteca) {
        string info = "[" + b.tipo + "] Código: " + b.codigo + 
                      " | Titulo: " + b.titulo + 
                      " | Año: " + to_string(b.anio) + " |";
        if (b.estado) {
            prestados << info << " Estado: Prestado" << endl;
        } else {
            stock << info << " Estado: En stock" << endl;
        }
    }
    stock.close();
    prestados.close();
}

void cargarDatos() {
    biblioteca.clear();
    string archivos[] = {"LibrosEnStock.txt", "LibrosPrestados.txt"};
    
    for (const string& nombreArchivo : archivos) {
        ifstream archivo(nombreArchivo);
        string linea;
        
        if (archivo.is_open()) {
            while (getline(archivo, linea)) {
                if (linea.empty()) continue; 
                Caracteristicas temporal;
                temporal.estado = (nombreArchivo == "LibrosPrestados.txt");
                try {
                    size_t p1 = linea.find("[") + 1;
                    size_t p2 = linea.find("]");
                    temporal.tipo = linea.substr(p1, p2 - p1);
                    
                    p1 = linea.find("Código: ") + 8;
                    p2 = linea.find(" |", p1);
                    temporal.codigo = linea.substr(p1, p2 - p1);
                    
                    p1 = linea.find("Titulo: ") + 8;
                    p2 = linea.find(" |", p1);
                    temporal.titulo = linea.substr(p1, p2 - p1);
                    
                    p1 = linea.find("Año: ") + 5;
                    p2 = linea.find(" |", p1);
                    temporal.anio = stoi(linea.substr(p1, p2 - p1));
                    
                    biblioteca.push_back(temporal); 
                } catch (...) {
                    continue;
                }
            }
            archivo.close();
        }
    }
}


void crearNuevo() {
    cout << "\033[2J\033[3J\033[1;1H";
    Caracteristicas nuevo;
    cout << "=== Ingresar Nuevo ===\n";
    cout << "Tipo (libro/revista): "; getline(cin, nuevo.tipo);
    capitalizar(nuevo.tipo);
    cout << "Código: "; getline(cin, nuevo.codigo);
    cout << "Título: "; getline(cin, nuevo.titulo);
    capitalizar(nuevo.titulo);
    cout << "Año: "; cin >> nuevo.anio; cin.ignore();
    
    nuevo.estado = false;
    biblioteca.push_back(nuevo);
    guardarTodo();

    cout << "\n¡Guardado con éxito! Presione Enter...";
    cin.get();
}

void mostrar() {
    cout << "\033[2J\033[3J\033[1;1H";
    cout << "| " << left << setw(7) << "TIPO" 
		 << " | " << setw(7) << "COD" 
		 << " | " << setw(25) << "TITULO" 
		 << " | " << setw(4) << "AÑO" 
		 << " | " << setw(8) << "ESTADO" << " |" <<endl;
    cout << string(81, '-') << endl;

    for (const auto& b : biblioteca) {
        cout << "| " << left << setw(7) << b.tipo 
             << " | " << setw(7) << b.codigo 
             << " | " << setw(25) << b.titulo 
             << " | " << setw(4) << b.anio 
             << " | " << setw(8) << (b.estado ? "PRESTADO" : "EN STOCK") << " |" << endl;
    }
    cout << "\nTotal: " << biblioteca.size() << " items. Presione Enter...";
    cin.get();
}

void prestarDevolver(bool prestando) {
    cout << "\033[2J\033[3J\033[1;1H";
    string cod;
    cout << "Ingrese el código del item a " << (prestando ? "PRESTAR" : "DEVOLVER") << ": ";
    getline(cin, cod);

    bool encontrado = false;
    for (auto& b : biblioteca) {
        if (b.codigo == cod) {
            if (b.estado == prestando) {
            	cout << "El item ya se encuentra en ese estado." << endl;
            } else {
                b.estado = prestando;
                guardarTodo();
                cout << "Estado actualizado con éxito." << endl;
            }
            encontrado = true;
            break;
        }
    }
    if (!encontrado) cout << "Código no encontrado." << endl;
    cout << "\nPresione Enter...";
    cin.get();
}

int main() {
	cargarDatos();
    int opc = 0;
    do {
    	menu(opc);
    	switch (opc) {
    		case 1: { crearNuevo(); break; }
    		case 2: { prestarDevolver(true);; break; }
    		case 3: { prestarDevolver(false); break; }
			case 4: { mostrar(); break; }
		}
	} while (opc != 5);
    return 0;
}
