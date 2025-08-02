#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib> 
#include <vector>
#include <list>
#include <filesystem>
#include <SFML/Graphics.hpp>


using namespace std;

class Elemento
{
public:
	int jugador;
	int movimientos;
	string nombre;
	string tipo;
	vector <int> posicion;
	Elemento()
	{
	}
	Elemento(int x, string y, string z, int w, vector <int> v)
	{
		jugador = x;
		nombre = y;
		tipo = z;
		movimientos = w;
		posicion = v;
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

void guardar(string ruta_guardado, string nombre_archivo, Casilla* tablero[8][8], string* estado, Jugador jugador_actual, Jugador jugador_1, Jugador jugador_2, int movimientos, vector<string> movimientos_totales) {
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
						<< elem->posicion[0] << "," << elem->posicion[1] << "\n";
					cout << elem->jugador << endl;
					cout << elem->nombre << endl;
					cout << elem->movimientos << endl;
				}
				else {
					archivo << "-1;  ;Vacio;-1;" << i << "," << j << "\n";
				}
			}
		}
		archivo << *estado << "\n";
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

void liberar_memoria(Casilla* tablero[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete tablero[i][j];
		}
	}
	cout << "Memoria liberada" << endl;
}

void cargar(string ruta_guardado, string* nombre_archivo, Casilla* tablero[8][8], string* estado, Jugador* jugador_actual, Jugador* jugador_1, Jugador* jugador_2, string* ganador, int* movimientos, vector<string>* movimientos_totales) {
	cout << "Ingrese el nombre de la partida a cargar: " << endl;
	cin >> *nombre_archivo;
	ifstream archivo(ruta_guardado + *nombre_archivo + ".txt");
	string linea;
	int linea_num = 0;

	if (archivo.is_open()) {
		int i = 0;
		int j = 0;
		while (getline(archivo, linea)) {
			linea_num++;
			if (linea_num <= 64) {
				// Datos de las fichas
				stringstream linea_externa(linea);
				string token;

				// jugador
				getline(linea_externa, token, ';');
				int jugador = stoi(token);
				// nombre
				getline(linea_externa, token, ';');
				string nombre = token;

				// tipo
				getline(linea_externa, token, ';');
				string tipo = token;

				// movimientos
				getline(linea_externa, token, ';');
				int movimientos = stoi(token);

				// posicion (fila,columna)
				getline(linea_externa, token); // "fila,columna"
				stringstream linea_interna(token);
				string parte;
				getline(linea_interna, parte, ',');
				int fila = stoi(parte);
				getline(linea_interna, parte, ',');
				int columna = stoi(parte);

				// Crear y asignar ficha al tablero
				if (jugador != -1) {
					tablero[fila][columna]->elemento = new Elemento(jugador, nombre, tipo, movimientos, { fila, columna });
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
				//cout << linea_num - 76 << endl;
				stringstream ss2(linea);
				string temporal;
				char delimitador = '/';
				while (getline(ss2, temporal, delimitador)) {
					//cout << "\"" << temporal << "\"" << " " << endl;

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
				cout << linea << endl;
			}
		}
		archivo.close();
	}
	cout << endl;
	cout << "Historial de jugadas: " << endl;
	cout << endl;

	int contador = 0;
	string movimiento_hecho;
	while (contador < *movimientos) {
		cout << "Movimiento " << contador + 1 << endl;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				stringstream aux(tablero[i][j]->historial[contador]);
				string temporal2;
				char delimitador2 = ';';
				getline(aux, temporal2, delimitador2);
				getline(aux, temporal2, delimitador2);
				bool casillaClara = (i + j) % 2 == 0;

				string fondo = casillaClara ? "\033[47m" : "\033[43m";  // Blanco o marrón (amarillo oscuro)
				string texto = casillaClara ? "\033[30m" : "\033[30m";  // Texto negro en ambos casos
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

int main()
{

	filesystem::path newDirectoryPath = filesystem::path(getenv("APPDATA")) / "Chess";
	string ruta_guardado = (newDirectoryPath / "").string();
	filesystem::create_directory(newDirectoryPath);


	//gittest


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
			if (i != 0 || i != 1 || i != 6 || i != 7) {
				tablero[i][j] = new Casilla({ i, j }, nullptr, {});
			}
		}
	}

	int op;
	cout << "Desea crear una nueva partida o cargar una? (0 = nueva, 1 = cargar partida): " << endl;
	cin >> op;
	if (op == 0) {
		jugador_1 = Jugador("", "", 0);
		jugador_2 = Jugador("", "", 1);
		cout << "Ingrese el nombre de su nueva partida: " << endl;
		cin >> nombre_archivo;
		cout << "Ingrese el nombre del jugador 0: " << endl;
		cin >> jugador_1.nombre;
		cout << "Ingrese el nombre del jugador 1: " << endl;
		cin >> jugador_2.nombre;
		jugador_actual = jugador_1;

		// Peones del jugador 0 (blancas)
		tablero[1][0] = new Casilla({ 1, 0 }, new Elemento(jugador_1.numero, "P1", "peon", 0, { 1, 0 }), {});
		tablero[1][1] = new Casilla({ 1, 1 }, new Elemento(jugador_1.numero, "P2", "peon", 0, { 1, 1 }), {});
		tablero[1][2] = new Casilla({ 1, 2 }, new Elemento(jugador_1.numero, "P3", "peon", 0, { 1, 2 }), {});
		tablero[1][3] = new Casilla({ 1, 3 }, new Elemento(jugador_1.numero, "P4", "peon", 0, { 1, 3 }), {});
		tablero[1][4] = new Casilla({ 1, 4 }, new Elemento(jugador_1.numero, "P5", "peon", 0, { 1, 4 }), {});
		tablero[1][5] = new Casilla({ 1, 5 }, new Elemento(jugador_1.numero, "P6", "peon", 0, { 1, 5 }), {});
		tablero[1][6] = new Casilla({ 1, 6 }, new Elemento(jugador_1.numero, "P7", "peon", 0, { 1, 6 }), {});
		tablero[1][7] = new Casilla({ 1, 7 }, new Elemento(jugador_1.numero, "P8", "peon", 0, { 1, 7 }), {});

		// Piezas principales del jugador 0
		tablero[0][0] = new Casilla({ 0, 0 }, new Elemento(jugador_1.numero, "T1", "torre", 0, { 0, 0 }), {});
		tablero[0][1] = new Casilla({ 0, 1 }, new Elemento(jugador_1.numero, "C1", "caballo", 0, { 0, 1 }), {});
		tablero[0][2] = new Casilla({ 0, 2 }, new Elemento(jugador_1.numero, "A1", "alfil", 0, { 0, 2 }), {});
		tablero[0][3] = new Casilla({ 0, 3 }, new Elemento(jugador_1.numero, "R1", "rey", 0, { 0, 3 }), {});
		tablero[0][4] = new Casilla({ 0, 4 }, new Elemento(jugador_1.numero, "D1", "dama", 0, { 0, 4 }), {});
		tablero[0][5] = new Casilla({ 0, 5 }, new Elemento(jugador_1.numero, "A2", "alfil", 0, { 0, 5 }), {});
		tablero[0][6] = new Casilla({ 0, 6 }, new Elemento(jugador_1.numero, "C2", "caballo", 0, { 0, 6 }), {});
		tablero[0][7] = new Casilla({ 0, 7 }, new Elemento(jugador_1.numero, "T2", "torre", 0, { 0, 7 }), {});

		// Peones del jugador 1 (negras)
		tablero[6][0] = new Casilla({ 6, 0 }, new Elemento(jugador_2.numero, "PA", "peon", 0, { 6, 0 }), {});
		tablero[6][1] = new Casilla({ 6, 1 }, new Elemento(jugador_2.numero, "PB", "peon", 0, { 6, 1 }), {});
		tablero[6][2] = new Casilla({ 6, 2 }, new Elemento(jugador_2.numero, "PC", "peon", 0, { 6, 2 }), {});
		tablero[6][3] = new Casilla({ 6, 3 }, new Elemento(jugador_2.numero, "PD", "peon", 0, { 6, 3 }), {});
		tablero[6][4] = new Casilla({ 6, 4 }, new Elemento(jugador_2.numero, "PE", "peon", 0, { 6, 4 }), {});
		tablero[6][5] = new Casilla({ 6, 5 }, new Elemento(jugador_2.numero, "PF", "peon", 0, { 6, 5 }), {});
		tablero[6][6] = new Casilla({ 6, 6 }, new Elemento(jugador_2.numero, "PG", "peon", 0, { 6, 6 }), {});
		tablero[6][7] = new Casilla({ 6, 7 }, new Elemento(jugador_2.numero, "PH", "peon", 0, { 6, 7 }), {});

		// Piezas principales del jugador 1
		tablero[7][0] = new Casilla({ 7, 0 }, new Elemento(jugador_2.numero, "TA", "torre", 0, { 7, 0 }), {});
		tablero[7][1] = new Casilla({ 7, 1 }, new Elemento(jugador_2.numero, "CA", "caballo", 0, { 7, 1 }), {});
		tablero[7][2] = new Casilla({ 7, 2 }, new Elemento(jugador_2.numero, "AA", "alfil", 0, { 7, 2 }), {});
		tablero[7][3] = new Casilla({ 7, 3 }, new Elemento(jugador_2.numero, "RA", "rey", 0, { 7, 3 }), {});
		tablero[7][4] = new Casilla({ 7, 4 }, new Elemento(jugador_2.numero, "DA", "dama", 0, { 7, 4 }), {});
		tablero[7][5] = new Casilla({ 7, 5 }, new Elemento(jugador_2.numero, "AB", "alfil", 0, { 7, 5 }), {});
		tablero[7][6] = new Casilla({ 7, 6 }, new Elemento(jugador_2.numero, "CB", "caballo", 0, { 7, 6 }), {});
		tablero[7][7] = new Casilla({ 7, 7 }, new Elemento(jugador_2.numero, "TB", "torre", 0, { 7, 7 }), {});

		guardar(ruta_guardado, nombre_archivo, tablero, &estado, jugador_actual, jugador_1, jugador_2, movimientos, movimientos_totales);
	}
	else {
		cargar(ruta_guardado, &nombre_archivo, tablero, &estado, &jugador_actual, &jugador_1, &jugador_2, &ganador, &movimientos, &movimientos_totales);
		if (estado == "finished") {
			return 0;
		}
	}



	while (true)
	{
		cout << "Movimiento actual: " << movimientos << endl;
		cout << "Jugador actual: " << jugador_actual.nombre << endl;
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
				cout << "Posicion inicial de i: ";
				cin >> init_i;
				cout << "Posicion inicial de j: ";
				cin >> init_j;
				if (tablero[init_i][init_j]->elemento->jugador != jugador_actual.numero) {
					cout << "No puede seleccionar una ficha ajena." << endl;
					continue;
				}
				cout << "Ficha seleccionada: " << tablero[init_i][init_j]->elemento->tipo << endl;
				cout << "Movimientos: " << tablero[init_i][init_j]->elemento->movimientos << endl;

				break;
			}

			while (true) {
				cout << "Posicion final de i: ";
				cin >> final_i;
				cout << "Posicion final de j: ";
				cin >> final_j;
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
			cout << "test" << endl;
			if (tablero[final_i][final_j]->elemento->tipo != "rey")
			{
				if (jugador_actual.numero == 0) {
					jugador_1.capturas += tablero[init_i][init_j]->elemento->nombre + "->" + tablero[final_i][final_j]->elemento->nombre + ";";
				}
				else {
					jugador_2.capturas += tablero[init_i][init_j]->elemento->nombre + "->" + tablero[final_i][final_j]->elemento->nombre + ";";
				}
				cout << "Good" << endl;
			}

			else
			{
				if (tablero[final_i][final_j]->elemento->tipo == "rey") {
					cout << "Jaque mate!" << endl;

					movimientos++;
					movimientos_totales.push_back(movement);
					cout << "King test" << endl;

					if (jugador_actual.numero == 0) {
						jugador_1.capturas += tablero[init_i][init_j]->elemento->nombre + "->" + tablero[final_i][final_j]->elemento->nombre + ";";
					}
					else {
						jugador_2.capturas += tablero[init_i][init_j]->elemento->nombre + "->" + tablero[final_i][final_j]->elemento->nombre + ";";
					}

					tablero[init_i][init_j]->elemento->movimientos++;
					tablero[init_i][init_j]->elemento->posicion = tablero[final_i][final_j]->posicion;
					tablero[final_i][final_j]->elemento = tablero[init_i][init_j]->elemento;
					tablero[init_i][init_j]->elemento = nullptr;

					cout << "King test 2" << endl;

					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (tablero[i][j]->elemento != nullptr) {
								string evento = to_string(tablero[i][j]->elemento->jugador) + ";" +
									tablero[i][j]->elemento->nombre + ";" +
									tablero[i][j]->elemento->tipo + ";" +
									to_string(tablero[i][j]->elemento->movimientos) + ";" +
									to_string(tablero[i][j]->elemento->posicion[0]) + "," +
									to_string(tablero[i][j]->elemento->posicion[1]);
								tablero[i][j]->historial.push_back(evento);
							}
							else {
								tablero[i][j]->historial.push_back("-1;  ;Vacio;-1;" + to_string(i) + "," + to_string(j));
							}
						}
					}

					estado = "finished";

					guardar(ruta_guardado, nombre_archivo, tablero, &estado, jugador_actual, jugador_1, jugador_2, movimientos, movimientos_totales);
					liberar_memoria(tablero);

					return 0;
				}
			}
		}

		movimientos++;
		tablero[init_i][init_j]->elemento->movimientos++;
		tablero[init_i][init_j]->elemento->posicion = tablero[final_i][final_j]->posicion;

		cout << "Test" << endl;
		cout << tablero[final_i][final_j]->elemento << endl;
		cout << tablero[init_i][init_j]->elemento << endl;
		tablero[final_i][final_j]->elemento = tablero[init_i][init_j]->elemento;
		tablero[init_i][init_j]->elemento = nullptr;
		cout << "Test2" << endl;

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
						to_string(tablero[i][j]->elemento->posicion[0]) + "," +
						to_string(tablero[i][j]->elemento->posicion[1]);
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
			guardar(ruta_guardado, nombre_archivo, tablero, &estado, jugador_actual, jugador_1, jugador_2, movimientos, movimientos_totales);
			liberar_memoria(tablero);
			return 0;
		}
		system("cls");
	}
	return 0;
}