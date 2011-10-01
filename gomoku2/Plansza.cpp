#include <deque>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <istream>
#include <stdio.h>
#include <string>
#include "Pole.h"
#include "Plansza.h"
#include "gomoku.h"
using namespace std;


	Plansza::Plansza(vector<vector <int>> typy){
		szablon[0]="XXXXX";
		szablon[1]="00000";

		for(int i=0; i<N+2 ; i++){
			for(int j=0 ; j<N+2 ; j++){
				pole[i][j]=new Pole(typy[i][j],i,j);
			}
		}
		pole[7][7]->set_typ(2);
		pole[8][8]->set_typ(1);
		/*
		pole[6][7]->set_typ(2);
		pole[5][7]->set_typ(2);
		pole[8][5]->set_typ(2);
		pole[8][6]->set_typ(2);
		pole[8][4]->set_typ(2);
		pole[3][7]->set_typ(1);
		pole[9][7]->set_typ(1);
		pole[8][2]->set_typ(1);
		*/
		
	//	pole[8][7]->set_typ(2);
	//	pole[7][9]->set_typ(1);

		for(int i=1; i<N ; i++){
			for(int j=1 ; j<N ; j++){
				this->uaktualnijKierunki(i,j);
			}
		}
	}

	void Plansza::rysuj_plansze(){
		for(int k=0; k<16; k++){
			if(k>0 && k<10) cout <<  k << " " ;
			else if(k>9) cout << k;
			else if(k==0) cout<<"    ";
		}
		cout<<endl;
		for(int i=0; i<17 ; i++){
			if(i>0 && i<10)cout<<i<<" ";
			else if(i>9 && i<16)cout<<i;
			else if(i==0 || i==16)cout<<"  ";
			for(int j=0 ; j<17 ; j++){
				cout<< pole[i][j]->getSymbol();
				(pole[i][j]->get_typ()==4) ? cout<<pole[i][j]->getSymbol() : cout << " ";
			}
		cout<<endl;
		}
	}

	void Plansza::uaktualnijKierunki(int pn, int pz){
		string *wsk=pole[pn][pz]->t;
		get_kierunki(pn,pz,wsk);
	}

	bool Plansza::czyNalezy(StanGry *sg,int pn, int pz){
		int found;
		for(int i=0;i<4;i++){
		found=pole[pn][pz]->t[i].find(szablon[sg->get_czyjaKolej()]);
		if(found >=0 && found<=pole[pn][pz]->t[0].size()) return true;
		}
		return false;
	}

	void Plansza::uaktualnijKierunkiPoRuchu(int pn, int pz){
		for(int i=0;i<9;i++){
			string pom;
			if(pn-4+i>=0 && pn-4+i<16) uaktualnijKierunki(pn-4+i,pz);
			if(pz-4+i>=0 && pz-4+i<16) uaktualnijKierunki(pn,pz-4+i);
			if(pn-4+i>=0 && pn-4+i<16 && pz+4-i>=0 && pz+4-i<16) uaktualnijKierunki(pn-4+i,pz+4-i);
			if(pn-4+i>=0 && pn-4+i<16 && pz-4+i>=0 && pz-4+i<16) uaktualnijKierunki(pn-4+i,pz-4+i);
		}
	}

	void Plansza::get_kierunki(int pn, int pz,string t[] ){
		for(int i=0;i<9;i++){
			string pom;
			pom=(pn-4+i>=0 && pn-4+i<16) ? pole[pn-4+i][pz]->getSymbol() : "_";
			t[0][i]=pom[0];

			pom=(pz-4+i>=0 && pz-4+i<16) ? pole[pn][pz-4+i]->getSymbol() : "_";
			t[1][i]=pom[0];

			pom=(pn-4+i>=0 && pn-4+i<16 && pz+4-i>=0 && pz+4-i<16) ? pole[pn-4+i][pz+4-i]->getSymbol() : "_";
			t[2][i]=pom[0];

			pom=(pn-4+i>=0 && pn-4+i<16 && pz-4+i>=0 && pz-4+i<16) ? pole[pn-4+i][pz-4+i]->getSymbol() : "_";
			t[3][i]=pom[0];

		}
	}

	bool Plansza::czy_zajete(){
		for(int i=1; i<N ; i++){
			for(int j=1 ; j<N ; j++){	
				if(pole[i][j]->get_typ()==3)
					return true;
			}
		}
		return false;
	}

	void Plansza::wyczyscPlansze(){
		for(int i=0;i<N+2;i++){
			for(int j=0;j<N+2;j++){
				(i==0 || i==16) ? pole[i][j]->set_typ(4) : ((j==0 || j==16) ? pole[i][j]->set_typ(4) : pole[i][j]->set_typ(3));
			}
		}
	}
	Plansza::~Plansza(){
		for(int i=0;i<N+2;i++){
			for(int j=0;j<N+2;j++){
				delete pole[i][j];
			}
		}
	}
