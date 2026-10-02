#pragma once

#include <iostream>
#include <conio.h>
#include <cstdlib>
using namespace std;
using namespace System;

// ============================================================
// ESCENA 1: la casita, el carrito y el personaje llegando
// ============================================================

void casita(int x, int y)
{
	string lineas[28] = {

"                            [[[|]]]    ",
"                    !!!!!!!!|--_--|!!!!!",
"                    [[[[[[[[\\_(X)_/]]]]]",
"            .-.     /-_--__-/_--_-\\-_--\\ ",
"            |=|    /-_---__/__-__-_\\__-_\\ ",
"        . . |=| ._/-__-__\\===========/-__\\_",
"        !!!!!!!!!\\========[ /]]|[[\\ ]=====/",
"       /-_--_-_-_[[[[[[[[[||==  == ||]]]]]]",
"      /-_--_--_--_|=  === ||=/^|^\\ ||== =|",
"     /-_-/^|^\\-_--| /^|^\\=|| | | | ||^\\= |",
"    /_-_-| | |-_--|=| | | ||=|_|_|=|| |==|",
"   /-__--|_|_|_-_-| |_|_|=||______=||_| =|",
"  /_-__--_-__-___-|_=__=_.`---------'._=_|__",
" /-----------------------\\===========/-----/",
"^^^\\^^^^^^^^^^^^^^^^^^^^^^[[|]]|[[|]]=====/",
"    |.' ..==::' '::==.. '.[/ ~~~~~\\]] ] ] ]",
"    | .'=[[[|]]|[[|]]]=`._||==  =  || =\\ ]",
"    ||== =|/ _____ \\|== = ||=/^|^\\=||^\\ ||",
"    || == `||-----||' = ==|| | | |=|| |=||",
"    ||= == ||:^M^:|| = == ||=| | | || |=||",
"    || = = ||:___:||= == =|| |_|_| ||_|=||",
"   _||_ = =||o---.|| = ==_||_= == =||==_||_",
"   \\__/= = ||:   :||= == \\__/[][][][][]\\__/",
"   [||]= ==||:___:|| = = [||]\\\\//\\\\//\\\\[||]",
"   }  {---' '-----' '- --}  {//\\\\//\\\\//}  {",
" __[==]__________________[==]\\\\//\\\\//\\\\[==]_",
"|`|~~~~|================|~~~~|~~~~~~~~|~~~~||",
"| |    |================|    |        |    ||"
	};

	for (int i = 0; i < 28; i++)
	{
		Console::SetCursorPosition(x, y + i);
		cout << lineas[i];
	}
}

void dibujar_carrito(int x, int y)
{
	string lineas[6] = {
"        _______",
"       //  ||\\ \\",
" _____//___||_\\ \\___",
" )  _          _    \\",
" |_/ \\________/ \\___|",
"___\\_/________\\_/______"
	};

	for (int i = 0; i < 6; i++)
	{
		Console::SetCursorPosition(x, y + i);
		cout << lineas[i];
	}
}

void carrito(int xinicial, int xfinal, int y)
{
	string espacios(30, ' ');

	for (int x = xinicial; x >= xfinal; x--)
	{
		dibujar_carrito(x, y);
		_sleep(100);

		if (x > xfinal)
		{
			for (int i = 0; i < 6; i++)
			{
				Console::SetCursorPosition(x, y + i);
				cout << espacios;
			}
		}
	}
}

void personaje_entra_casa(int xinicial, int xfinal, int y, int casa_x, int casa_y, int carrito_x, int carrito_y)
{
	string lineas[8] = {
"  _",
"_[_]_",
" (_)",
"//:\\\\",
"\\|~|/",
" |||",
" |||",
" - -"
	};

	string espacios(10, ' ');

	for (int x = xinicial; x >= xfinal; x--)
	{
		for (int i = 0; i < 8; i++)
		{
			Console::SetCursorPosition(x, y + i);
			cout << lineas[i];
		}

		_sleep(100);

		if (x > xfinal)
		{
			for (int i = 0; i < 8; i++)
			{
				Console::SetCursorPosition(x, y + i);
				cout << espacios;
			}

			casita(casa_x, casa_y);
			dibujar_carrito(carrito_x, carrito_y);
		}
	}

	_sleep(200);

	for (int i = 0; i < 8; i++)
	{
		Console::SetCursorPosition(xfinal, y + i);
		cout << espacios;
	}

	casita(casa_x, casa_y);
	dibujar_carrito(carrito_x, carrito_y);
}

// ============================================================
// ESCENA 2: la salita, la cortina y la puerta secreta
// ============================================================

void cortina(int x, int y)
{
	string lineas[16] = {
"(IIIIIIIIIIIIIIIIIII)",
")'.'.'.':;:;:'.'.'.'(",
"('.'.'.;' | `:.'.'.')",
")'.'.';'  |  `:'.'.'(",
"('.'.;'   |   `:.'.')",
")'.';'____|____`:'.'(",
"(==@'     |     `@==)",
")'.:     @()     :.'(",
"('.'.   ()@()   .'.')",
")'.'.  ()@()@)  .'.'(",
"('.'.   _\\|/_   .'.')",
")'.'.  |-----|  .'.'(",
"('.'.___\\___/___.'.')",
")'.'============='.'(",
"('.'             '.')",
" ~                 ~"
	};

	for (int i = 0; i < 16; i++)
	{
		Console::SetCursorPosition(x, y + i);
		cout << lineas[i];
	}
}

void puertita(int x, int y)
{
	string lineas[5] = {
" ______ ",
"|.-\"\"-.|",
"| |  | |",
"| |  | |",
"|_|__|_|"
	};

	for (int i = 0; i < 5; i++)
	{
		Console::SetCursorPosition(x, y + i);
		cout << lineas[i];
	}
}

void personaje_va_puerta(int xinicial, int xfinal, int y, int cortina_x, int cortina_y, int puerta_x, int puerta_y)
{
	string lineas[8] = {
"  _",
"_[_]_",
" (_)",
"//:\\\\",
"\\|~|/",
" |||",
" |||",
" - -"
	};

	string espacios(10, ' ');

	for (int x = xinicial; x >= xfinal; x--)
	{
		for (int i = 0; i < 8; i++)
		{
			Console::SetCursorPosition(x, y + i);
			cout << lineas[i];
		}

		_sleep(100);

		if (x > xfinal)
		{
			for (int i = 0; i < 8; i++)
			{
				Console::SetCursorPosition(x, y + i);
				cout << espacios;
			}

			cortina(cortina_x, cortina_y);
			puertita(puerta_x, puerta_y);
		}
	}

	// se queda parado frente a la puertita unos segundos
	_sleep(1500);

	// desaparece (entra por la puerta secreta)
	for (int i = 0; i < 8; i++)
	{
		Console::SetCursorPosition(xfinal, y + i);
		cout << espacios;
	}

	cortina(cortina_x, cortina_y);
	puertita(puerta_x, puerta_y);
}

// ============================================================
// MAIN: encadena las dos escenas
// ============================================================

void encadenaciondosEscenas()
{
	// --- Escena 1: llegada a la casita ---
	casita(7, 1);
	carrito(95, 52, 23);
	personaje_entra_casa(57, 20, 10, 7, 1, 52, 23);

	// --- Transición a la escena 2 ---
	system("cls");

	// --- Escena 2: la salita, cortina y puerta secreta ---
	int cortina_x = 50, cortina_y = 5;
	int puerta_x = 5, puerta_y = 12;

	cortina(cortina_x, cortina_y);
	puertita(puerta_x, puerta_y);

	personaje_va_puerta(55, puerta_x + 8, 12, cortina_x, cortina_y, puerta_x, puerta_y);
	_sleep(100);
}