#ifndef Gracz_H
#define Gracz_H

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
#include "Plansza.h"
using namespace std;

class Gracz{
protected:
	string nazwa;
	StanGry* stanGry;
	Plansza* plansza;
public:
	Gracz(string);
	virtual bool rusz(int,int)=0;
	virtual Wsp znajdz_wsp()=0;
	virtual void wygrany()=0;
	virtual void przegrany()=0;
	virtual void wypisz()=0;
	virtual int get_id()=0;
	virtual void ustawStanPlansze(StanGry* , Plansza* );
};

#endif