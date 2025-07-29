#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib> 
#include <vector>
#include <list>

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
	Elemento elemento;
	vector <string> historial;
	Casilla() {
	}
	Casilla(vector <int> v, Elemento e, vector <string> h) {
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



int main()
{

	int movimientos = 0;
	int filas_movidas;
	int columnas_movidas;
	string respuesta;
	string ganador;
	string estado = "active";
	string nombre_archivo;
	vector<string> movimientos_totales = {};
	Jugador jugador_actual;
	Jugador jugador_1;
	Jugador jugador_2;
	Casilla tablero[8][8];

	for (int i = 0; i <= 8 - 1; i++)
	{
		for (int j = 0; j <= 8 - 1; j++)
		{
			tablero[i][j] = Casilla({ i, j }, Elemento(-1, "  ", "vacio", -1, { i, j }), {});
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
		tablero[1][0].elemento = Elemento(jugador_1.numero, "P1", "peon", 0, tablero[1][0].posicion);
		tablero[1][1].elemento = Elemento(jugador_1.numero, "P2", "peon", 0, tablero[1][1].posicion);
		tablero[1][2].elemento = Elemento(jugador_1.numero, "P3", "peon", 0, tablero[1][2].posicion);
		tablero[1][3].elemento = Elemento(jugador_1.numero, "P4", "peon", 0, tablero[1][3].posicion);
		tablero[1][4].elemento = Elemento(jugador_1.numero, "P5", "peon", 0, tablero[1][4].posicion);
		tablero[1][5].elemento = Elemento(jugador_1.numero, "P6", "peon", 0, tablero[1][5].posicion);
		tablero[1][6].elemento = Elemento(jugador_1.numero, "P7", "peon", 0, tablero[1][6].posicion);
		tablero[1][7].elemento = Elemento(jugador_1.numero, "P8", "peon", 0, tablero[1][7].posicion);

		// Piezas principales del jugador 0
		tablero[0][0].elemento = Elemento(jugador_1.numero, "T1", "torre", 0, tablero[0][0].posicion);
		tablero[0][1].elemento = Elemento(jugador_1.numero, "C1", "caballo", 0, tablero[0][1].posicion);
		tablero[0][2].elemento = Elemento(jugador_1.numero, "A1", "alfil", 0, tablero[0][2].posicion);
		tablero[0][3].elemento = Elemento(jugador_1.numero, "R1", "rey", 0, tablero[0][3].posicion);
		tablero[0][4].elemento = Elemento(jugador_1.numero, "D1", "dama", 0, tablero[0][4].posicion);
		tablero[0][5].elemento = Elemento(jugador_1.numero, "A2", "alfil", 0, tablero[0][5].posicion);
		tablero[0][6].elemento = Elemento(jugador_1.numero, "C2", "caballo", 0, tablero[0][6].posicion);
		tablero[0][7].elemento = Elemento(jugador_1.numero, "T2", "torre", 0, tablero[0][7].posicion);

		// Peones del jugador 1 (negras)
		tablero[6][0].elemento = Elemento(jugador_2.numero, "PA", "peon", 0, tablero[6][0].posicion);
		tablero[6][1].elemento = Elemento(jugador_2.numero, "PB", "peon", 0, tablero[6][1].posicion);
		tablero[6][2].elemento = Elemento(jugador_2.numero, "PC", "peon", 0, tablero[6][2].posicion);
		tablero[6][3].elemento = Elemento(jugador_2.numero, "PD", "peon", 0, tablero[6][3].posicion);
		tablero[6][4].elemento = Elemento(jugador_2.numero, "PE", "peon", 0, tablero[6][4].posicion);
		tablero[6][5].elemento = Elemento(jugador_2.numero, "PF", "peon", 0, tablero[6][5].posicion);
		tablero[6][6].elemento = Elemento(jugador_2.numero, "PG", "peon", 0, tablero[6][6].posicion);
		tablero[6][7].elemento = Elemento(jugador_2.numero, "PH", "peon", 0, tablero[6][7].posicion);

		// Piezas principales del jugador 1
		tablero[7][0].elemento = Elemento(jugador_2.numero, "TA", "torre", 0, tablero[7][0].posicion);
		tablero[7][1].elemento = Elemento(jugador_2.numero, "CA", "caballo", 0, tablero[7][1].posicion);
		tablero[7][2].elemento = Elemento(jugador_2.numero, "AA", "alfil", 0, tablero[7][2].posicion);
		tablero[7][3].elemento = Elemento(jugador_2.numero, "RA", "rey", 0, tablero[7][3].posicion);
		tablero[7][4].elemento = Elemento(jugador_2.numero, "DA", "dama", 0, tablero[7][4].posicion);
		tablero[7][5].elemento = Elemento(jugador_2.numero, "AB", "alfil", 0, tablero[7][5].posicion);
		tablero[7][6].elemento = Elemento(jugador_2.numero, "CB", "caballo", 0, tablero[7][6].posicion);
		tablero[7][7].elemento = Elemento(jugador_2.numero, "TB", "torre", 0, tablero[7][7].posicion);

		ofstream archivo(nombre_archivo + ".txt");

		if (archivo.is_open()) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					Elemento elem = tablero[i][j].elemento;
					archivo << elem.jugador << ";"
						<< elem.nombre << ";"
						<< elem.tipo << ";"
						<< elem.movimientos << ";"
						<< elem.posicion[0] << "," << elem.posicion[1] << "\n";
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
			archivo << "NA" << "\n";
			archivo << movimientos << "\n";
			archivo.close();
			cout << "Archivo creado y escrito exitosamente.\n";
		}
		else {
			cerr << "Error al abrir el archivo.\n";
		}

	}
	else {
		/*cout << "Tablero antes de ser registrado:" << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cout << i << ", " << j << endl;
				for (string elemento : tablero[i][j].historial) {
					cout << elemento << "//";
				}
				cout << endl;
			}
		}*/

		cout << "Ingrese el nombre de la partida a cargar: " << endl;
		cin >> nombre_archivo;
		ifstream archivo(nombre_archivo + ".txt");
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
					tablero[fila][columna].elemento = Elemento(jugador, nombre, tipo, movimientos, { fila, columna });
				}
				else if (linea_num == 65) estado = linea;
				else if (linea_num == 66) jugador_actual.capturas = linea;
				else if (linea_num == 67) jugador_actual.nombre = linea;
				else if (linea_num == 68) jugador_actual.numero = stoi(linea);
				else if (linea_num == 69) jugador_1.capturas = linea;
				else if (linea_num == 70) jugador_1.nombre = linea;
				else if (linea_num == 71) jugador_1.numero = stoi(linea);
				else if (linea_num == 72) jugador_2.capturas = linea;
				else if (linea_num == 73) jugador_2.nombre = linea;
				else if (linea_num == 74) jugador_2.numero = stoi(linea);
				else if (linea_num == 75) ganador = linea;
				else if (linea_num == 76) movimientos = stoi(linea);
				else if (linea_num <= 140) {
					//cout << linea_num - 76 << endl;
					stringstream ss2(linea);
					string temporal;
					char delimitador = '/';
					while (getline(ss2, temporal, delimitador)) {
						//cout << "\"" << temporal << "\"" << " " << endl;

						tablero[i][j].historial.push_back(temporal);
					}

					j++;
					if (j == 8) {
						j = 0;
						i++;
					}
				}
				else {
					movimientos_totales.push_back(linea);
				}
			}
			archivo.close();
		}
		/*for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cout << i << ", " << j << endl;
				for (string elemento : tablero[i][j].historial) {
					cout << elemento << "//";
				}
				cout << endl;
			}
		}
		*/
		cout << endl;

		cout << "Historial de jugadas: " << endl;
		cout << endl;

		int contador = 0;
		while (contador < movimientos) {
			cout << "Movimiento " << contador + 1 << endl;
			cout << movimientos_totales[contador] << endl;

			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					stringstream aux(tablero[i][j].historial[contador]);
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


	}

	if (estado == "finished") {
		cout << "Este juego ya finalizó, te mostraremos el resultado final del tablero y los movimientos de cada jugador." << endl;
		cout << "Resultado final: " << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				bool casillaClara = (i + j) % 2 == 0;

				string fondo = casillaClara ? "\033[47m" : "\033[43m";  // Blanco o marrón (amarillo oscuro)
				string texto = casillaClara ? "\033[30m" : "\033[30m";  // Texto negro en ambos casos
				string reset = "\033[0m";

				string nombre = tablero[i][j].elemento.nombre;

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




		cout << "Movimientos totales: " << movimientos << endl;
		cout << "Capturas " << jugador_1.nombre << ": " << jugador_1.capturas << endl;
		cout << "Capturas " << jugador_2.nombre << ": " << jugador_2.capturas << endl;
		cout << "Lista de movimientos" << endl;
		for (string elemento : movimientos_totales) {
			cout << elemento << endl;
		}
		cout << "Ganador: " << ganador << endl;


		return 0;
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

				string nombre = tablero[i][j].elemento.nombre;

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
				if (tablero[i][j].elemento.jugador == jugador_actual.numero)
				{
					cout << tablero[i][j].posicion[0] << tablero[i][j].posicion[1] << ":" << tablero[i][j].elemento.nombre << endl;
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


		int init_i, init_j, final_i, final_j;

		while (true)
		{
			while (true) {
				cout << "Posicion inicial de i: ";
				cin >> init_i;
				cout << "Posicion inicial de j: ";
				cin >> init_j;
				if (tablero[init_i][init_j].elemento.jugador != jugador_actual.numero) {
					cout << "No puede seleccionar una ficha ajena." << endl;
					continue;
				}
				cout << "Ficha seleccionada: " << tablero[init_i][init_j].elemento.tipo << endl;
				cout << "Movimientos: " << tablero[init_i][init_j].elemento.movimientos << endl;

				break;
			}

			while (true) {
				cout << "Posicion final de i: ";
				cin >> final_i;
				cout << "Posicion final de j: ";
				cin >> final_j;
				if (tablero[final_i][final_j].elemento.jugador == jugador_actual.numero) {
					cout << "No puede sobreescribir sus propias fichas." << endl;
					continue;
				}

				filas_movidas = abs(final_i - init_i);
				columnas_movidas = abs(final_j - init_j);

				if (tablero[init_i][init_j].elemento.tipo == "torre")
				{
					if (init_i == final_i && init_j != final_j)
					{
						break;
					}
					else
					{
						if (init_j == final_j && init_i != final_i)
						{
							break;

						}
						else {
							cout << "Movimiento invalido." << endl;
							continue;
						}
					}
				}

				else if (tablero[init_i][init_j].elemento.tipo == "caballo") {
					if (filas_movidas == 2 && columnas_movidas == 1) {
						break;
					}
					else {
						if (columnas_movidas == 2 && filas_movidas == 1) {
							cout << "Movimiento invalido." << endl;
							break;
						}
						else {
							continue;
						}
					}
				}

				else if (tablero[init_i][init_j].elemento.tipo == "alfil") {
					if (filas_movidas == columnas_movidas) {
						break;
					}
					else {
						cout << "Movimiento invalido." << endl;
						continue;
					}
					break;

				}

				else if (tablero[init_i][init_j].elemento.tipo == "dama") {
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

				else if (tablero[init_i][init_j].elemento.tipo == "rey") {
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

				else if (tablero[init_i][init_j].elemento.tipo == "peon") {
					if (columnas_movidas == 0 && filas_movidas == 1) {
						cout << "Movimiento vertical unitario" << endl;
					}
					if (columnas_movidas == 1 && filas_movidas == 1 && tablero[init_i][init_j].elemento.jugador != -1) {
						cout << "Movimiento diagonal unitario" << endl;
					}

				}

				/*
				if (tablero[init_i][init_j].tipo == "peon")
				{

					int movimiento_maximo_peon;
					int movimiento_minimo_peon;
					int adelante_peon_superior;
					int adelante_peon_inferior;

					if (tablero[init_i][init_j].movimientos == 0)
					{
						movimiento_maximo_peon = 2;
						movimiento_minimo_peon = 1;
						if (tablero[init_i][init_j].jugador == 0)
						{
							adelante_peon_superior = 2;
							adelante_peon_inferior = 1;
						}
						if (tablero[init_i][init_j].jugador == 1)
						{
							adelante_peon_superior = -2;
							adelante_peon_inferior = -1;
						}

					}
					else
					{
						movimiento_minimo_peon = 1;
						movimiento_maximo_peon = movimiento_minimo_peon;
						if (tablero[init_i][init_j].jugador == 0)
						{
							adelante_peon_superior = 1;
							adelante_peon_inferior = 1;
						}
						if (tablero[init_i][init_j].jugador == 1)
						{
							adelante_peon_superior = -1;
							adelante_peon_inferior = -1;
						}

					}
					if ((abs(final_i - init_i) <= movimiento_maximo_peon && abs(final_i - init_i) >= movimiento_minimo_peon) && (final_j == init_j) && (tablero[final_i][final_j].jugador == -1) && (final_i - init_i == adelante_peon_superior || final_i - init_i == adelante_peon_inferior))
					{
						break;
					}
					else
					{
						if ((abs(final_i - init_i) == movimiento_minimo_peon) && (final_j - init_j == 1 || init_j - final_j == 1) && (tablero[final_i][final_j].jugador != -1) && (final_i - init_i == adelante_peon_superior || final_i - init_i == adelante_peon_inferior))
						{
							break;



						}

						else
						{
							cout << "Los peones no pueden realizar estos movimientos." << endl;
							continue;
						}
					}
				}*/
				break;
			}
			break;
		}

		string movement = tablero[init_i][init_j].elemento.nombre + ":{" + to_string(init_i) + ',' + to_string(init_j) + "}->{" + to_string(final_i) + "," + to_string(final_j) + "}" + " ("+jugador_actual.nombre+")";
		// cout << movement << endl;

		if (tablero[final_i][final_j].elemento.jugador != -1 && tablero[final_i][final_j].elemento.tipo != "rey")
		{
			if (jugador_actual.numero == 0) {
				jugador_1.capturas += tablero[init_i][init_j].elemento.nombre + "->" + tablero[final_i][final_j].elemento.nombre + ";";
			}
			else {
				jugador_2.capturas += tablero[init_i][init_j].elemento.nombre + "->" + tablero[final_i][final_j].elemento.nombre + ";";
			}
		}

		else
		{
			if (tablero[final_i][final_j].elemento.tipo == "rey") {
				cout << "Jaque mate!" << endl;

				movimientos++;
				movimientos_totales.push_back(movement);

				if (jugador_actual.numero == 0) {
					jugador_1.capturas += tablero[init_i][init_j].elemento.nombre + "->" + tablero[final_i][final_j].elemento.nombre + ";";
				}
				else {
					jugador_2.capturas += tablero[init_i][init_j].elemento.nombre + "->" + tablero[final_i][final_j].elemento.nombre + ";";
				}

				tablero[init_i][init_j].elemento.movimientos++;
				tablero[init_i][init_j].elemento.posicion = tablero[final_i][final_j].posicion;
				tablero[final_i][final_j].elemento = tablero[init_i][init_j].elemento;
				tablero[init_i][init_j].elemento = Elemento(-1, "  ", "casilla", -1, { init_i, init_j });

				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						string evento = to_string(tablero[i][j].elemento.jugador) + ";" +
							tablero[i][j].elemento.nombre + ";" +
							tablero[i][j].elemento.tipo + ";" +
							to_string(tablero[i][j].elemento.movimientos) + ";" +
							to_string(tablero[i][j].elemento.posicion[0]) + "," +
							to_string(tablero[i][j].elemento.posicion[1]);
						tablero[i][j].historial.push_back(evento);
					}
				}

				estado = "finished";

				ofstream archivo(nombre_archivo + ".txt");

				if (archivo.is_open()) {
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							Elemento elem = tablero[i][j].elemento;
							archivo << elem.jugador << ";"
								<< elem.nombre << ";"
								<< elem.tipo << ";"
								<< elem.movimientos << ";"
								<< elem.posicion[0] << "," << elem.posicion[1] << "\n";
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
							for (const string& jugada : tablero[i][j].historial) {
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

				return 0;
			}
		}

		movimientos++;
		tablero[init_i][init_j].elemento.movimientos++;
		tablero[init_i][init_j].elemento.posicion = tablero[final_i][final_j].posicion;
		tablero[final_i][final_j].elemento = tablero[init_i][init_j].elemento;
		tablero[init_i][init_j].elemento = Elemento(-1, "  ", "casilla", -1, { init_i, init_j });

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
				string evento = to_string(tablero[i][j].elemento.jugador) + ";" +
					tablero[i][j].elemento.nombre + ";" +
					tablero[i][j].elemento.tipo + ";" +
					to_string(tablero[i][j].elemento.movimientos) + ";" +
					to_string(tablero[i][j].elemento.posicion[0]) + "," +
					to_string(tablero[i][j].elemento.posicion[1]);
				tablero[i][j].historial.push_back(evento);
			}
		}

		movimientos_totales.push_back(movement);

		cout << "Continuar?" << endl;
		cin >> respuesta;
		if (respuesta == "n") {
			ofstream archivo(nombre_archivo + ".txt");

			if (archivo.is_open()) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						Elemento elem = tablero[i][j].elemento;

						archivo << elem.jugador << ";"
							<< elem.nombre << ";"
							<< elem.tipo << ";"
							<< elem.movimientos << ";"
							<< elem.posicion[0] << "," << elem.posicion[1] << "\n";
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
				archivo << "NA" << "\n";
				archivo << movimientos << "\n";
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						for (const string& jugada : tablero[i][j].historial) {
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

			return 0;
		}
		system("cls");
	}
	return 0;
}
