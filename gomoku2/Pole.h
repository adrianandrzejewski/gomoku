#ifndef pole_H
#define pole_H

#include <deque>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <istream>
#include <stdio.h>
#include <string>
#include "gomoku.h"
#include "Gracz.h"
using namespace std;

/**
* Klasa rezprezentuj�ca jedno pole, ma sw�j typ, pozycj� pionow� i poziom�, warto��
* tablica string�w t[] przechowuje informacje o s�siednich polach  w ka�dym z 4 kierunk�w
*
*/
class Pole{
protected:
	int typ;
	int pn;
	int pz;
	int wart;
	string t[4];
public:

	/**
	* Tworzy nowe pole o zadanym typie, ustawia pozycj� pola(pion, poziom)
	* Wartosc pola przy tworzeniu ustawiana jest na 0
	*
	* @param typ typ pola
	* @param pn pion
	* @param pn poziom
	*/
	Pole(int ,int ,int );

	/**
	* Zwraca typ pola
	* 1 - X kolor czarny
	* 2 - 0 kolor bialy
	* 3 - # sciana
	* 4 - ' ' puste pole
	*
	* @return liczba od 1 do 4
	*/
	int get_typ();

	/**
	* Ustawia typ pola zadany w argumencie
	*
	* @param typ typ pola do ustawienia
	*/
	void set_typ(int );

	/**
	* Zwraca pozycj� pola
	*
	* @return pozycja - pozycja.pion i pozycja.poziom
	*/
	Wsp get_Pozycja();

	/**
	* Ustawia wartosc pola na 3 czyli ' '(pole puste)
	*
	*/
	void usunTyp();

	/**
	* Ustawia wartosc pola
	*
	* @param wartosc - wartosc do ustawienia
	*/
	void set_wart(int);

	/**
	* Zwraca symbol pola w zaleznosci od typu
	* 1 - X kolor czarny
	* 2 - 0 kolor bialy
	* 3 - # sciana
	* 4 - ' ' puste pole
	* @return symbol - symbol pola jako string
	*/
	string getSymbol();

	/**
	* Sprawdza czy pole nie jest zaj�te
	*
	* @return true jesli pole jest wolne
	*/
	bool czyWolny();

	/**
	* Sprawdza czy jesli postawimy tu pionek to czy stworzymy zagrozenie,
	* ktore jest przekazywane jako parametr
	*
	* @param kto - dla kogo sprawdzamy (komputer czy czlowiek)
	* @param zagrozenie - rodzaj zagrozenia ktorego szukamy
	* @return true jesli stworzymy zagrozenie
	*/
	bool czyNalezy(char ,string );

	/**
	* Zwraca obecn� warto�� pola
	*
	* @return warto��
	*/
	int get_wart();

	/**
	* Sprawdza czy obok pola jest jakie� pole zajmowane przez jakiego� z graczy
	*
	* @return true je�li obok jest pole niepuste
	*/
	bool czyObokNiepuste();

	friend Plansza;
};
#endif