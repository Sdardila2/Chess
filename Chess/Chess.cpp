#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib> 
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class Elemento
{
public:
	int jugador;
	int movimientos;
	string nombre;
	string tipo;
	Elemento()
	{
	}
	Elemento(int x, string y, string z, int w)
	{
		jugador = x;
		nombre = y;
		tipo = z;
		movimientos = w;
	}
};

class Casilla
{
public:
	vector <int> posicion;
	Elemento* elemento;
	vector <string> historial;
	Casilla() {
	}
	Casilla(vector <int> v, Elemento* e, vector <string> h) {
		posicion = v;
		elemento = e;
		historial = h;
	}
};

class Jugador
{
public:
	string nombre;
	string capturas;
	int numero;

	Jugador()
	{
	}
	Jugador(string x, string y, int z)
	{
		nombre = x;
		capturas = y;
		numero = z;
	}
};

void liberar_memoria(Casilla* tablero[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (tablero[i][j]) {
				delete tablero[i][j]->elemento;
				tablero[i][j]->elemento = nullptr;
			}
			delete tablero[i][j];
			tablero[i][j] = nullptr;
		}
	}
	cout << "Memoria liberada" << endl;
}

void guardar(string ruta_guardado, string nombre_archivo, Casilla* tablero[8][8], string estado, Jugador jugador_actual, Jugador jugador_1, Jugador jugador_2, int movimientos, vector<string> movimientos_totales) {
	ofstream archivo(ruta_guardado + nombre_archivo + ".txt");
	if (archivo.is_open()) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tablero[i][j]->elemento != nullptr) {
					Elemento* elem = tablero[i][j]->elemento;
					archivo << elem->jugador << ";"
						<< elem->nombre << ";"
						<< elem->tipo << ";"
						<< elem->movimientos << ";"
						<< tablero[i][j]->posicion[0] << "," << tablero[i][j]->posicion[1] << "\n";
					cout << elem->jugador << endl;
					cout << elem->nombre << endl;
					cout << elem->movimientos << endl;
				}
				else {
					archivo << "-1;  ;Vacio;-1;" << i << "," << j << "\n";
				}
			}
		}
		archivo << estado << "\n";
		archivo << jugador_actual.capturas << "\n";
		archivo << jugador_actual.nombre << "\n";
		archivo << jugador_actual.numero << "\n";
		archivo << jugador_1.capturas << "\n";
		archivo << jugador_1.nombre << "\n";
		archivo << jugador_1.numero << "\n";
		archivo << jugador_2.capturas << "\n";
		archivo << jugador_2.nombre << "\n";
		archivo << jugador_2.numero << "\n";
		archivo << jugador_actual.nombre << "\n";
		archivo << movimientos << "\n";
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				for (string jugada : tablero[i][j]->historial) {
					archivo << jugada << "/";
				}
				archivo << "\n";
			}
		}
		for (string elemento : movimientos_totales) {
			archivo << elemento << "\n";
		}
		archivo.close();
		cout << "Archivo creado y escrito exitosamente.\n";
	}
	else {
		cerr << "Error al abrir el archivo.\n";
	}
}

void cargar(string ruta_guardado, string* nombre_archivo, Casilla* tablero[8][8], string* estado, Jugador* jugador_actual, Jugador* jugador_1, Jugador* jugador_2, string* ganador, int* movimientos, vector<string>* movimientos_totales, vector<string>* lista_de_directorios) {

	cout << "Lista de partidas: " << endl;
	for (string archivo : *lista_de_directorios) {
		cout << archivo << endl;
	}

	cout << "Ingrese el nombre de la partida que desea cargar: " << endl;
	while (true) {
		cin >> *nombre_archivo;
		if (find(lista_de_directorios->begin(), lista_de_directorios->end(), *nombre_archivo) == lista_de_directorios->end()) {
			cout << "No existe archivo con ese nombre, intente nuevamente." << endl;
			continue;
		}
		else {
			break;
		}
	}
	ifstream archivo(ruta_guardado + *nombre_archivo + ".txt");
	string linea;
	int linea_num = 0;

	if (archivo.is_open()) {
		int i = 0;
		int j = 0;
		while (getline(archivo, linea)) {
			linea_num++;
			if (linea_num <= 64) {

				stringstream linea_externa(linea);
				string token;

				getline(linea_externa, token, ';');
				int jugador = stoi(token);

				getline(linea_externa, token, ';');
				string nombre = token;


				getline(linea_externa, token, ';');
				string tipo = token;


				getline(linea_externa, token, ';');
				int movimientos = stoi(token);


				getline(linea_externa, token);
				stringstream linea_interna(token);
				string parte;
				getline(linea_interna, parte, ',');
				int fila = stoi(parte);
				getline(linea_interna, parte, ',');
				int columna = stoi(parte);

				if (jugador != -1) {
					tablero[fila][columna]->elemento = new Elemento(jugador, nombre, tipo, movimientos);
				}
				else {
					tablero[fila][columna]->elemento = nullptr;
				}
			}
			else if (linea_num == 65) *estado = linea;
			else if (linea_num == 66) jugador_actual->capturas = linea;
			else if (linea_num == 67) jugador_actual->nombre = linea;
			else if (linea_num == 68) jugador_actual->numero = stoi(linea);
			else if (linea_num == 69) jugador_1->capturas = linea;
			else if (linea_num == 70) jugador_1->nombre = linea;
			else if (linea_num == 71) jugador_1->numero = stoi(linea);
			else if (linea_num == 72) jugador_2->capturas = linea;
			else if (linea_num == 73) jugador_2->nombre = linea;
			else if (linea_num == 74) jugador_2->numero = stoi(linea);
			else if (linea_num == 75) *ganador = linea;
			else if (linea_num == 76) *movimientos = stoi(linea);
			else if (linea_num <= 140) {
				stringstream ss2(linea);
				string temporal;
				char delimitador = '/';
				while (getline(ss2, temporal, delimitador)) {

					tablero[i][j]->historial.push_back(temporal);
				}

				j++;
				if (j == 8) {
					j = 0;
					i++;
				}
			}
			else {
				movimientos_totales->push_back(linea);
			}
		}
		archivo.close();
	}
	cout << endl;
	cout << "Historial de jugadas: " << endl;
	cout << endl;

	int contador = 0;
	while (contador < *movimientos) {
		cout << "Movimiento " << contador + 1 << endl;
		cout << (*movimientos_totales)[contador] << endl;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				stringstream aux(tablero[i][j]->historial[contador]);
				string temporal2;
				char delimitador2 = ';';
				getline(aux, temporal2, delimitador2);
				getline(aux, temporal2, delimitador2);
				bool casillaClara = (i + j) % 2 == 0;

				string fondo = casillaClara ? "\033[47m" : "\033[43m";
				string texto = casillaClara ? "\033[30m" : "\033[30m";
				string reset = "\033[0m";

				string nombre = temporal2;

				if (nombre.empty()) {
					cout << fondo << texto << "  " << reset;
				}
				else {
					if (nombre.length() == 1) nombre = " " + nombre;
					cout << fondo << texto << nombre << reset;
				}
			}
			cout << endl;
		}

		contador++;
		cout << endl;
	}
	if (*estado == "finished") {
		cout << "Este juego ya finalizó, te mostraremos el resultado final del tablero y los movimientos de cada jugador." << endl;
		cout << "Resultado final: " << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				bool casillaClara = (i + j) % 2 == 0;

				string fondo = casillaClara ? "\033[47m" : "\033[43m";
				string texto = casillaClara ? "\033[30m" : "\033[30m";
				string reset = "\033[0m";
				string nombre;

				if (tablero[i][j]->elemento != nullptr) {
					nombre = tablero[i][j]->elemento->nombre;
				}
				else {
					nombre = "";
				}
				if (nombre.empty()) {
					cout << fondo << texto << "  " << reset;
				}
				else {
					if (nombre.length() == 1) nombre = " " + nombre;
					cout << fondo << texto << nombre << reset;
				}
			}
			cout << endl;
		}
		cout << endl;


		cout << "Movimientos totales: " << *movimientos << endl;
		cout << "Capturas " << jugador_1->nombre << ": " << jugador_1->capturas << endl;
		cout << "Capturas " << jugador_2->nombre << ": " << jugador_2->capturas << endl;
		cout << "Lista de movimientos" << endl;
		for (string elemento : *movimientos_totales) {
			cout << elemento << endl;
		}
		cout << "Ganador: " << *ganador << endl;
		liberar_memoria(tablero);
	}
}

void crear_tablero(Jugador* jugador_1, Jugador* jugador_2, Jugador* jugador_actual, string* nombre_archivo, Casilla* tablero[8][8], filesystem::path* ruta_carpeta, vector<string>* lista_de_directorios) {

	cout << "Lista de partidas: " << endl;
	for (string archivo : *lista_de_directorios) {
		cout << archivo << endl;
	}
	*jugador_1 = Jugador("", "", 0);
	*jugador_2 = Jugador("", "", 1);

	cout << "Ingrese el nombre la partida que desea crear: " << endl;
	while (true) {
		cin >> *nombre_archivo;
		if (find(lista_de_directorios->begin(), lista_de_directorios->end(), *nombre_archivo) == lista_de_directorios->end()) {
			break;
		}
		else {
			cout << "Ya existe una partida con ese nombre. Intente con un nombre diferente." << endl;
			continue;
		}
	}
	cout << "Ingrese el nombre del jugador 0: " << endl;
	cin >> jugador_1->nombre;
	cout << "Ingrese el nombre del jugador 1: " << endl;
	cin >> jugador_2->nombre;
	*jugador_actual = *jugador_1;

	tablero[1][0]->elemento = new Elemento(jugador_1->numero, "P1", "peon", 0);
	tablero[1][1]->elemento = new Elemento(jugador_1->numero, "P2", "peon", 0);
	tablero[1][2]->elemento = new Elemento(jugador_1->numero, "P3", "peon", 0);
	tablero[1][3]->elemento = new Elemento(jugador_1->numero, "P4", "peon", 0);
	tablero[1][4]->elemento = new Elemento(jugador_1->numero, "P5", "peon", 0);
	tablero[1][5]->elemento = new Elemento(jugador_1->numero, "P6", "peon", 0);
	tablero[1][6]->elemento = new Elemento(jugador_1->numero, "P7", "peon", 0);
	tablero[1][7]->elemento = new Elemento(jugador_1->numero, "P8", "peon", 0);

	tablero[0][0]->elemento = new Elemento(jugador_1->numero, "T1", "torre", 0);
	tablero[0][1]->elemento = new Elemento(jugador_1->numero, "C1", "caballo", 0);
	tablero[0][2]->elemento = new Elemento(jugador_1->numero, "A1", "alfil", 0);
	tablero[0][3]->elemento = new Elemento(jugador_1->numero, "R1", "rey", 0);
	tablero[0][4]->elemento = new Elemento(jugador_1->numero, "D1", "dama", 0);
	tablero[0][5]->elemento = new Elemento(jugador_1->numero, "A2", "alfil", 0);
	tablero[0][6]->elemento = new Elemento(jugador_1->numero, "C2", "caballo", 0);
	tablero[0][7]->elemento = new Elemento(jugador_1->numero, "T2", "torre", 0);

	tablero[6][0]->elemento = new Elemento(jugador_2->numero, "PA", "peon", 0);
	tablero[6][1]->elemento = new Elemento(jugador_2->numero, "PB", "peon", 0);
	tablero[6][2]->elemento = new Elemento(jugador_2->numero, "PC", "peon", 0);
	tablero[6][3]->elemento = new Elemento(jugador_2->numero, "PD", "peon", 0);
	tablero[6][4]->elemento = new Elemento(jugador_2->numero, "PE", "peon", 0);
	tablero[6][5]->elemento = new Elemento(jugador_2->numero, "PF", "peon", 0);
	tablero[6][6]->elemento = new Elemento(jugador_2->numero, "PG", "peon", 0);
	tablero[6][7]->elemento = new Elemento(jugador_2->numero, "PH", "peon", 0);

	tablero[7][0]->elemento = new Elemento(jugador_2->numero, "TA", "torre", 0);
	tablero[7][1]->elemento = new Elemento(jugador_2->numero, "CA", "caballo", 0);
	tablero[7][2]->elemento = new Elemento(jugador_2->numero, "AA", "alfil", 0);
	tablero[7][3]->elemento = new Elemento(jugador_2->numero, "RA", "rey", 0);
	tablero[7][4]->elemento = new Elemento(jugador_2->numero, "DA", "dama", 0);
	tablero[7][5]->elemento = new Elemento(jugador_2->numero, "AB", "alfil", 0);
	tablero[7][6]->elemento = new Elemento(jugador_2->numero, "CB", "caballo", 0);
	tablero[7][7]->elemento = new Elemento(jugador_2->numero, "TB", "torre", 0);

}

void mostrar_tablero(Casilla* tablero[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			bool casillaClara = (i + j) % 2 == 0;

			string fondo = casillaClara ? "\033[47m" : "\033[43m";  // Blanco o marrón (amarillo oscuro)
			string texto = casillaClara ? "\033[30m" : "\033[30m";  // Texto negro en ambos casos
			string reset = "\033[0m";
			string nombre;

			if (tablero[i][j]->elemento != nullptr) {
				nombre = tablero[i][j]->elemento->nombre;
			}
			else {
				nombre = "";
			}
			if (nombre.empty()) {
				cout << fondo << texto << "  " << reset;
			}
			else {
				if (nombre.length() == 1) nombre = " " + nombre;
				cout << fondo << texto << nombre << reset;
			}
		}
		cout << endl;
	}
}

int main()
{

	filesystem::path newDirectoryPath = filesystem::path(getenv("APPDATA")) / "Chess";
	string ruta_guardado = (newDirectoryPath / "").string();
	filesystem::create_directory(newDirectoryPath);
	vector<string> lista_de_archivos = {};

	for (const auto& entry : fs::directory_iterator(newDirectoryPath)) {
		lista_de_archivos.push_back(entry.path().stem().string());
	}

	int movimientos = 0;
	int filas_movidas;
	int columnas_movidas;
	int init_i, init_j, final_i, final_j;

	string respuesta;
	string ganador;
	string estado = "active";
	string nombre_archivo;
	vector<string> movimientos_totales = {};
	Jugador jugador_actual;
	Jugador jugador_1;
	Jugador jugador_2;
	Casilla* tablero[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tablero[i][j] = new Casilla({ i, j }, nullptr, {});
		}
	}

	int op;
	cout << "Desea crear una nueva partida o cargar una? (0 = nueva, 1 = cargar partida): " << endl;
	cin >> op;
	if (op == 0) {
		crear_tablero(&jugador_1, &jugador_2, &jugador_actual, &nombre_archivo, tablero, &newDirectoryPath, &lista_de_archivos);
		guardar(ruta_guardado, nombre_archivo, tablero, estado, jugador_actual, jugador_1, jugador_2, movimientos, movimientos_totales);
	}
	else {
		cargar(ruta_guardado, &nombre_archivo, tablero, &estado, &jugador_actual, &jugador_1, &jugador_2, &ganador, &movimientos, &movimientos_totales, &lista_de_archivos);
		if (estado == "finished") {
			return 0;
		}
	}



	while (true)
	{
		cout << "Movimiento actual: " << movimientos + 1 << endl;
		cout << "Jugador actual: " << jugador_actual.nombre << endl;
		mostrar_tablero(tablero);

		cout << "Elementos y posiciones disponibles:" << endl;

		for (int i = 0; i <= 8 - 1; i++)
		{
			for (int j = 0; j <= 8 - 1; j++)
			{
				if (tablero[i][j]->elemento != nullptr) {
					if (tablero[i][j]->elemento->jugador == jugador_actual.numero)
					{
						cout << tablero[i][j]->posicion[0] << tablero[i][j]->posicion[1] << ":" << tablero[i][j]->elemento->nombre << endl;
					}
				}
			}
		}

		cout << endl << "Capturas: " << endl;
		switch (jugador_actual.numero) {
		case 0:
			cout << jugador_1.capturas << endl;
			break;
		case 1:
			cout << jugador_2.capturas << endl;
		}



		while (true)
		{
			while (true) {
				while (true) {
					cout << "Posicion inicial de i: ";
					cin >> init_i;
					if (cin.fail()) {
						cout << "Ingrese solo valores permitidos (numeros enteros)." << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						continue;
					}
					if (init_i < 0 || init_i > 7) {
						cout << "Fuera de indice." << endl;
						continue;
					}
					break;
				}

				while (true) {
					cout << "Posicion inicial de j: ";
					cin >> init_j;
					if (cin.fail()) {
						cout << "Ingrese solo valores permitidos (numeros enteros)." << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						continue;
					}
					if (init_j < 0 || init_j > 7) {
						cout << "Fuera de indice." << endl;
						continue;
					}
					break;
				}


				if (tablero[init_i][init_j]->elemento != nullptr) {
					if (tablero[init_i][init_j]->elemento->jugador != jugador_actual.numero) {
						cout << "No puede seleccionar una ficha ajena." << endl;
						continue;
					}
				}
				else {
					cout << "No puede seleccionar una casilla vacia." << endl;
					continue;
				}
				cout << "Ficha seleccionada: " << tablero[init_i][init_j]->elemento->tipo << endl;
				cout << "Movimientos: " << tablero[init_i][init_j]->elemento->movimientos << endl;

				break;
			}

			while (true) {

				while (true) {
					cout << "Posicion final de i: ";
					cin >> final_i;
					if (cin.fail()) {
						cout << "Ingrese solo valores permitidos (numeros enteros)." << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						continue;
					}
					if (final_i < 0 || final_i > 7) {
						cout << "Fuera de indice." << endl;
						continue;
					}
					break;
				}

				while (true) {
					cout << "Posicion final de j: ";
					cin >> final_j;
					if (cin.fail()) {
						cout << "Ingrese solo valores permitidos (numeros enteros)." << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						continue;
					}
					if (final_j < 0 || final_j > 7) {
						cout << "Fuera de indice." << endl;
						continue;
					}
					break;
				}

				if (tablero[final_i][final_j]->elemento != nullptr) {
					if (tablero[final_i][final_j]->elemento->jugador == jugador_actual.numero) {
						cout << "No puede sobreescribir sus propias fichas." << endl;
						continue;
					}
				}

				filas_movidas = abs(final_i - init_i);
				columnas_movidas = abs(final_j - init_j);
				cout << filas_movidas << endl;
				cout << columnas_movidas << endl;

				if (tablero[init_i][init_j]->elemento->tipo == "torre")
				{
					if (init_i == final_i && init_j != final_j)
					{
						cout << "Movimiento horizontal." << endl;
						break;
					}
					else
					{
						if (init_j == final_j && init_i != final_i)
						{
							cout << "Movimiento vertical." << endl;
							break;

						}
						else {
							cout << "Movimiento invalido." << endl;
							continue;
						}
					}
				}

				else if (tablero[init_i][init_j]->elemento->tipo == "caballo") {
					if (filas_movidas == 2 && columnas_movidas == 1) {
						break;
					}
					else {
						if (columnas_movidas == 2 && filas_movidas == 1) {
							break;
						}
						else {
							cout << "Movimiento invalido." << endl;
							continue;
						}
					}
				}

				else if (tablero[init_i][init_j]->elemento->tipo == "alfil") {
					if (filas_movidas == columnas_movidas) {
						break;
					}
					else {
						cout << "Movimiento invalido." << endl;
						continue;
					}
					break;

				}

				else if (tablero[init_i][init_j]->elemento->tipo == "dama") {
					if (filas_movidas == 0 && columnas_movidas != 0)
					{
						break;
					}
					else
					{
						if (columnas_movidas == 0 && filas_movidas != 0)
						{
							break;

						}
						else {
							if (filas_movidas == columnas_movidas) {
								break;
							}
							else {
								cout << "Movimiento invalido." << endl;
								continue;
							}
						}
					}
				}

				else if (tablero[init_i][init_j]->elemento->tipo == "rey") {
					if (columnas_movidas == 0 && filas_movidas == 1)
					{
						cout << "Movimiento horizontal" << endl;
						break;
					}
					else
					{
						if (filas_movidas == 0 && columnas_movidas == 1)
						{
							cout << "Movimiento vertical" << endl;
							break;

						}
						else {
							if (filas_movidas == columnas_movidas && filas_movidas + columnas_movidas == 2) {
								cout << "Movimiento diagonal" << endl;
								break;
							}
							else {
								cout << "Movimiento invalido" << endl;
								continue;
							}
						}
					}
				}


				else if (tablero[init_i][init_j]->elemento->tipo == "peon") {
					int max_filas = 2;
					if (tablero[init_i][init_j]->elemento->movimientos > 0) {
						max_filas = 1;
					}
					if (tablero[init_i][init_j]->elemento->jugador == 2) {
						max_filas = -(max_filas);
					}

					if (columnas_movidas == 0 && filas_movidas <= max_filas && tablero[final_i][final_j]->elemento == nullptr) {
						cout << "Movimiento vertical unitario" << endl;
						break;
					}
					else {
						if (columnas_movidas == 1 && filas_movidas == 1 && tablero[final_i][final_j]->elemento != nullptr) {
							cout << "Movimiento diagonal unitario" << endl;
							break;
						}
						else {
							cout << "Movimiento invalido." << endl;
							continue;
						}
					}

				}
			}
			break;
		}

		string movement = tablero[init_i][init_j]->elemento->nombre + ":{" + to_string(init_i) + ',' + to_string(init_j) + "}->{" + to_string(final_i) + "," + to_string(final_j) + "}" + " (" + jugador_actual.nombre + ")";
		cout << movement << endl;

		if (tablero[final_i][final_j]->elemento != nullptr) {
			if (tablero[final_i][final_j]->elemento->tipo != "rey")
			{
				if (jugador_actual.numero == 0) {
					jugador_1.capturas += tablero[init_i][init_j]->elemento->nombre + "->" + tablero[final_i][final_j]->elemento->nombre + ";";
				}
				else {
					jugador_2.capturas += tablero[init_i][init_j]->elemento->nombre + "->" + tablero[final_i][final_j]->elemento->nombre + ";";
				}
			}

			else
			{
				if (tablero[final_i][final_j]->elemento->tipo == "rey") {
					cout << "Jaque mate!" << endl;

					movimientos++;
					movimientos_totales.push_back(movement);

					if (jugador_actual.numero == 0) {
						jugador_1.capturas += tablero[init_i][init_j]->elemento->nombre + "->" + tablero[final_i][final_j]->elemento->nombre + ";";
					}
					else {
						jugador_2.capturas += tablero[init_i][init_j]->elemento->nombre + "->" + tablero[final_i][final_j]->elemento->nombre + ";";
					}

					tablero[init_i][init_j]->elemento->movimientos++;
					tablero[final_i][final_j]->elemento = tablero[init_i][init_j]->elemento;
					tablero[init_i][init_j]->elemento = nullptr;


					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (tablero[i][j]->elemento != nullptr) {
								string evento = to_string(tablero[i][j]->elemento->jugador) + ";" +
									tablero[i][j]->elemento->nombre + ";" +
									tablero[i][j]->elemento->tipo + ";" +
									to_string(tablero[i][j]->elemento->movimientos) + ";" +
									to_string(tablero[i][j]->posicion[0]) + "," +
									to_string(tablero[i][j]->posicion[1]);
								tablero[i][j]->historial.push_back(evento);
							}
							else {
								tablero[i][j]->historial.push_back("-1;  ;Vacio;-1;" + to_string(i) + "," + to_string(j));
							}
						}
					}

					estado = "finished";

					guardar(ruta_guardado, nombre_archivo, tablero, estado, jugador_actual, jugador_1, jugador_2, movimientos, movimientos_totales);
					liberar_memoria(tablero);

					return 0;
				}
			}
		}

		movimientos++;
		tablero[init_i][init_j]->elemento->movimientos++;

		cout << tablero[final_i][final_j]->elemento << endl;
		cout << tablero[init_i][init_j]->elemento << endl;
		tablero[final_i][final_j]->elemento = tablero[init_i][init_j]->elemento;
		tablero[init_i][init_j]->elemento = nullptr;

		if (jugador_actual.numero == 0)
		{
			jugador_actual = jugador_2;
		}
		else
		{
			jugador_actual = jugador_1;
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tablero[i][j]->elemento != nullptr) {
					string evento = to_string(tablero[i][j]->elemento->jugador) + ";" +
						tablero[i][j]->elemento->nombre + ";" +
						tablero[i][j]->elemento->tipo + ";" +
						to_string(tablero[i][j]->elemento->movimientos) + ";" +
						to_string(tablero[i][j]->posicion[0]) + "," +
						to_string(tablero[i][j]->posicion[1]);
					tablero[i][j]->historial.push_back(evento);
				}
				else {
					tablero[i][j]->historial.push_back("-1;  ;Vacio;-1;" + to_string(i) + "," + to_string(j));
				}
			}
		}

		movimientos_totales.push_back(movement);

		cout << "Continuar?" << endl;
		cin >> respuesta;
		if (respuesta == "n") {
			guardar(ruta_guardado, nombre_archivo, tablero, estado, jugador_actual, jugador_1, jugador_2, movimientos, movimientos_totales);
			liberar_memoria(tablero);
			return 0;
		}
		system("cls");
	}
	return 0;
}