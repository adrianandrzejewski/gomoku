#include <iterator>
#include <algorithm>
#include <time.h>
#include <istream>
#include <stdio.h>
#include <string>
#include "gomoku.h"
#include "Pole.h"
#include "Plansza.h"
#include "Gracz.h"
using namespace std;

Gracz::Gracz(string nazwa):nazwa(nazwa),stanGry(NULL),plansza(NULL){};

	void Gracz::ustawStanPlansze(StanGry* sg, Plansza* p){
		stanGry=sg;
		plansza=p;
	}