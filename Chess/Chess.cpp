#include <iostream>
#include <vector>
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
	Casilla() {
	}
	Casilla(vector <int> v, Elemento e) {
		posicion = v;
		elemento = e;
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

	int filas_movidas;
	int columnas_movidas;
	string capturas_totales = "";
	Jugador jugador_1 = Jugador("Samuel", "", 0);
	Jugador jugador_2 = Jugador("Salome", "", 1);
	Jugador jugador_actual = jugador_1;
	Casilla tablero[8][8];

	for (int i = 0; i <= 8 - 1; i++)
	{
		for (int j = 0; j <= 8 - 1; j++)
		{
			tablero[i][j] = Casilla({ i, j }, Elemento(-1, "  ", "vacio", -1, { i, j }));
		}
	}

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

	while (true)
	{
		cout << "Turno jugador " << jugador_actual.nombre << endl << endl;
		for (int i = 0; i <= 8 - 1; i++)
		{
			for (int j = 0; j <= 8 - 1; j++)
			{
				cout << tablero[i][j].elemento.nombre << " ";
			}
			cout << endl;
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

				else if (tablero[init_i][init_j].elemento.tipo == "peon"){
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
		if (tablero[final_i][final_j].elemento.jugador != -1 && tablero[final_i][final_j].elemento.tipo != "rey")
		{
			capturas_totales += tablero[init_i][init_j].elemento.nombre + "->" + tablero[final_i][final_j].elemento.nombre + "\n";
			if (jugador_actual.numero == 0) {
				jugador_1.capturas += tablero[init_i][init_j].elemento.nombre + "->" + tablero[final_i][final_j].elemento.nombre + "\n";
			}
			else {
				jugador_2.capturas += tablero[init_i][init_j].elemento.nombre + "->" + tablero[final_i][final_j].elemento.nombre + "\n";
			}
		}

		else
		{
			if (tablero[final_i][final_j].elemento.tipo == "rey") {
				cout << "Jaque mate!" << endl;
				cout << "Capturas" << endl;
				cout << capturas_totales << endl;
				return 0;
			}
		}
		tablero[init_i][init_j].elemento.movimientos++;
		tablero[init_i][init_j].elemento.posicion = { final_i, final_j };
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
		system("cls");
	}
	return 0;
}
