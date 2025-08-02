#pragma once
#include <string>
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

