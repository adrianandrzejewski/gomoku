#ifndef Plansza_H
#define Plansza_H

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
#include "Pole.h"
#include "Gracz.h"
using namespace std;


/**
* Klasa odpowiedzialna na przechowywanie planszy
* Pole[17][17] - tablica dwuwymiarowa sk�adaj�ca si� z element�w typu Pole
*
*/
class Plansza{	
protected:
	Pole *pole[17][17];
	string szablon[2];
public:
	/**
	* Tworzy pust� plansz�, dla ka�dego pola uaktualnia kierunki  i wstawia 2 pocz�tkowe znaki
	*
	* @param typy - pusta plansza otoczona scianami
	*/
	Plansza(vector<vector <int>>);

	/**
	* Metoda rysujaca plansz�
	*
	*/
	void rysuj_plansze();

	/**
	* Metoda uaktualniaj�ca kierunki dla pola wskazanego w argumencie
	*
	* @param pn - pion
	* @param pz - poziom
	*/
	void uaktualnijKierunki(int , int );

	/**
	* Sprawdza czy pole wskazane z agrumencie nalezy do wygrywaj�cej pi�tki
	*
	* @param stanGry - do pobrania informacji czyja jest kolej
	* @param pn - pion
	* @param pz - poziom
	*/
	bool czyNalezy(StanGry*,int , int );

	/**
	* Metoda uaktualniaj�ca kierunki po ruchu dla pola wskazanego w argumencie we wszystkich 4 kierunkach
	*
	* @param pn - pion
	* @param pz - poziom
	*/
	void uaktualnijKierunkiPoRuchu(int , int );

	/**
	* Metoda wpisuj�ca do tablicy string�w s�siednie pola dla wskazanego pola
	*
	* @param pn - pion
	* @param pz - poziom
	* @param kierunki - tablica string�w do kt�rej wpisujemy symbole s�siednich p�l
	*/
	void get_kierunki(int , int ,string[] );

	/**
	* Metoda sprawdza czy wszystkie pola na planszy s� zaj�te
	*
	* @return true je�li przynajmniej jedno pole jest wolne
	*/
	bool czy_zajete();

	/**
	* Metoda czyszcz�ca plansz�, tj ustawiaj�ce same puste pola
	*
	*/
	void wyczyscPlansze();

	/**
	* Destruktor planszy
	*
	*/
	~Plansza();

	friend class Gra;
	friend class Osoba;
	friend class Komputer;
	friend void StanGry::zapiszStanGry(Plansza*,vector<Gracz*>&);
	friend bool StanGry::wczytajStanGry(Plansza*,vector<Gracz*>&,BazaDanych&);
};

#endif