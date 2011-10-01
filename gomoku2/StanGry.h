#ifndef StanGry_H
#define StanGry_H

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
using namespace std;


/**
* Klasa przechowuj¹ca informacjê o aktualnym stanie gry
*
*/

class StanGry{
protected:
	int czyjaKolej;
public:
	/**
	* Tworzy nowy stanGry - ustawia kolej ruchu
	*
	* @param czyjaKolej - ustawia czyja jest teraz kolej ruchu
	*/
	StanGry(int);

	/**
	* Ustawia czyja kolej
	*
	* @param czyjaKolej
	*/
	void set_czyjaKolej(int);

	/**
	* Zwraca czyja jest kolej
	*
	* @return  czyjaKolej
	*/
	int get_czyjaKolej();

	/**
	* Zmienia kolej z 0 na 1 lub odwrotnie
	*
	* @return true jesli pole jest wolne
	*/
	void zmienKolej();

	/**
	* Zapisuje aktualny stan gry do pliku stangry.txt
	*
	* @param gracze - aktualnie ustawieni gracze
	* @param plansza
	*/
	void zapiszStanGry(Plansza*,vector<Gracz*>&);

	/**
	* Wczytuje stan gry z pliku stangry.txt i ustawia aktualnych graczy
	*
	* @param plansza
	* @param gracze - ustawia graczy
	* @param baza danych - 
	*/
	bool wczytajStanGry(Plansza*,vector<Gracz*>&,BazaDanych&);

	/**
	* Zwraca znak osoby której jest teraz kolej
	*
	* @return X jesli czyjaKolej==0, 0 w P.P
	*/
	string getZnak();
};
#endif