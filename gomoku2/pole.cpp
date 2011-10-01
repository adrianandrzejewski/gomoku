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
#include "pole.h"
using namespace std;

Pole::Pole(int typ,int pn,int pz):typ(typ),wart(0),pn(pn),pz(pz){
		for(int i=0;i<4;i++){t[i].resize(9,' ');}
	};
	int Pole::get_typ() { return typ; };
	void Pole::set_typ(int typ){this->typ=typ;};
	Wsp Pole::get_Pozycja(){
		Wsp pozycja;
		pozycja.pion=pn;
		pozycja.poziom=pz;
		return pozycja;
	};
	void Pole::usunTyp(){this->typ=3;};
	void Pole::set_wart(int w){wart=w;};
	string Pole::getSymbol(){
		switch(typ){
			case 1: return "X";
			case 2: return "0";
			case 3: return " ";
			case 4: return "#";
		}
		return " ";
	}

	bool Pole::czyWolny(){return (typ==3) ? true : false;}


	bool Pole::czyNalezy(char kto,string zagrozenie){
		int found=0;
		for(string::size_type i=0; i<4;i++){
			t[i][4]=kto;
			found=t[i].find(zagrozenie);
				if(found >=0 && found<=t[i].size()) wart+=10;
			t[i][4]=' ';
		}
		return (wart>0) ? true:false;
	}
	int Pole::get_wart(){return wart;};

	bool Pole::czyObokNiepuste(){
		for(int i=0;i<4;i++){
			if(t[i][3] == '0' || t[i][5] == '0' || t[i][3] == 'X' || t[i][5] == 'X')
				return true;
		}
		return false;
	}