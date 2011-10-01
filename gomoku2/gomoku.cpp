#include <fstream>
#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <istream>
#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <ctime> 
#include "gomoku.h"

using namespace std;


extern bool czyKoniec=false;
extern string zagrozeniaX[]={" XXXX","X XXX","XX XX","XXX X","XXXX "," XXXX ","  XXX  "," XXX  ","  XXX "," X XX "," XX X "};
extern string zagrozenia0[]={" 0000","0 000","00 00","000 0","0000 "," 0000 ","  000  "," 000  ","  000 "," 0 00 "," 00 0 "};
class Gracz;
class Osoba;
class Komputer;
class Plansza;
class BazaDanych;
int kontrola_wprowadzania_danych(int,int);

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

	


	StanGry::StanGry(int ck):czyjaKolej(ck){};
	void StanGry::set_czyjaKolej(int ck){czyjaKolej=ck;}
	int StanGry::get_czyjaKolej() {return czyjaKolej;};
	void StanGry::zmienKolej(){czyjaKolej=++czyjaKolej%2;}
	string StanGry::getZnak(){return (czyjaKolej==0) ? "X" : "0";}


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
		pole[7][7]->set_typ(2);
		pole[8][8]->set_typ(1);
	}
	Plansza::~Plansza(){
		for(int i=0;i<N+2;i++){
			for(int j=0;j<N+2;j++){
				delete pole[i][j];
			}
		}
	}

	Gracz::Gracz(string nazwa):nazwa(nazwa),stanGry(NULL),plansza(NULL){};

	void Gracz::ustawStanPlansze(StanGry* sg, Plansza* p){
		stanGry=sg;
		plansza=p;
	}



	Osoba::Osoba(int id,string nazwa, int w, int p):Gracz(nazwa),id(id),wygrane(w),przegrane(p){};

	bool Osoba::rusz(int pn, int pz){
		plansza->pole[pn][pz]->set_typ(stanGry->get_czyjaKolej()+1);
		plansza->uaktualnijKierunkiPoRuchu(pn,pz);
		if( plansza->czyNalezy(stanGry,pn,pz) )
			return true;
		stanGry->zmienKolej();
		return false;
	}

	Wsp Osoba::znajdz_wsp(){
		Wsp wsp;
		cout<<"podaj wspolrzedne ruchu: pionowo/poziomo(0 wroc do menu glownego)"<<endl;
		cin>>wsp.pion;
		if(wsp.pion==0){
			cout << "Powrot do menu glownego. Zapisano gre.";
			return wsp;
		}
		else
		cin>>wsp.poziom;
		return wsp;	
	}

	void Osoba::wygrany(){wygrane++;}
	void Osoba::przegrany(){przegrane++;}
	void Osoba::wypisz(){cout << "Gracz: " << id << " " << nazwa << endl; }
	void Osoba::set_nazwa(string nazwa){this->nazwa=nazwa;}
	void Osoba::set_wygrane(int w){this->wygrane=w;}
	void Osoba::set_przegrane(int p){this->przegrane=p;}
	int Osoba::get_id(){return id;};
	string Osoba::get_nazwa(){return nazwa;};
	int Osoba::get_wygrane(){return wygrane;};
	int Osoba::get_przegrane(){return przegrane;};


bool maksymalny_ruch(Pole* a, Pole* b) { return a->get_wart() < b->get_wart(); }
bool sortuj_nazwa(Osoba* a, Osoba* b) { return a->get_nazwa() < b->get_nazwa(); }
bool sortuj_id(Osoba* a, Osoba* b) { return a->get_id() < b->get_id(); }
bool sortuj_wygrane(Osoba* a, Osoba* b) { return a->get_wygrane() < b->get_wygrane(); }
bool sortuj_przegrane(Osoba* a, Osoba* b) { return a->get_przegrane() < b->get_przegrane(); }


	Komputer::Komputer():Gracz("komputer"){};

	int Komputer::get_id(){return -1;};

	Wsp Komputer::znajdz_wsp(){
			Wsp wsp;
			vector <int> max;
			vector <Pole*> zagrozenia;
			string kto;
			vector <Pole*> ruchy;

			//SZUKAMY 5 atak
			for(int i=1;i<N+1;i++){
				for(int j=1;j<N+1;j++){
					if(plansza->pole[i][j]->czyWolny() && plansza->pole[i][j]->czyObokNiepuste()){
							if(plansza->pole[i][j]->czyNalezy('0',"00000")){
								wsp.pion=i;
								wsp.poziom=j;
								return wsp;
							}
							ruchy.push_back(plansza->pole[i][j]);
					}
				}
			}

			//SZUKAMY 4 - OBRONA
			for(string::size_type i=0;i<ruchy.size();i++){
				if(ruchy[i]->czyNalezy('X',"XXXXX")){ 
					return ruchy[i]->get_Pozycja();}
			}
			
			//SZUKAMY MOZLIWOSCI STWORZENIA CZWORKI W LINI
			for(string::size_type i=0;i<ruchy.size();i++){
				if(ruchy[i]->czyNalezy('0'," 0000 ")){
					return ruchy[i]->get_Pozycja();
				}
			}
			//SZUKAMY MOZLIWOSCI STWORZENIA CZWORKI JAKIEJKOLWIEK
			for(string::size_type i=0;i<ruchy.size();i++){
				for(int k=0;k<5;k++){
					if(ruchy[i]->czyNalezy('0',zagrozenia0[k])){
						zagrozenia.push_back(ruchy[i]);
						break;
					}
				}
			}
			if(!zagrozenia.empty()){
				for(string::size_type i=0;i<zagrozenia.size();i++) szukajDodatkowychZagrozen(zagrozenia[i]);
				vector<Pole*>::iterator it = max_element(zagrozenia.begin(),zagrozenia.end(),maksymalny_ruch);
				return (*it)->get_Pozycja();
			}


			//OBRONA PRZED STWORZENIEM CZWORKI W LINI
			for(string::size_type i=0;i<ruchy.size();i++){
				if(ruchy[i]->czyNalezy('X'," XXXX ")){
					zagrozenia.push_back(ruchy[i]);
					
				}
			}
			if(!zagrozenia.empty()){
				for(string::size_type i=0;i<zagrozenia.size();i++) szukajDodatkowychZagrozen(zagrozenia[i]);
				vector<Pole*>::iterator it = max_element(zagrozenia.begin(),zagrozenia.end(),maksymalny_ruch);
				return (*it)->get_Pozycja();
			}

			//OBRONA PRZED STWORZENIEM 4 W OGOLE
			for(string::size_type i=0;i<ruchy.size();i++){
				for(int k=0;k<5;k++){
					if(ruchy[i]->czyNalezy('X',zagrozeniaX[k])){
						zagrozenia.push_back(ruchy[i]);
						break;
					}
				}
			}
			if(!zagrozenia.empty()){
				for(string::size_type i=0;i<zagrozenia.size();i++) szukajDodatkowychZagrozen(zagrozenia[i]);
				vector<Pole*>::iterator it = max_element(zagrozenia.begin(),zagrozenia.end(),maksymalny_ruch);
				return (*it)->get_Pozycja();
			}
			//ATAK - MOZLIWOSC STWORZENIA 3
			for(string::size_type i=0;i<ruchy.size();i++){
				for(int k=5;k<11;k++){
					if(ruchy[i]->czyNalezy('0',zagrozenia0[k])){
						zagrozenia.push_back(ruchy[i]);
						break;
					}
				}
			}
			if(!zagrozenia.empty()){
				for(string::size_type i=0;i<zagrozenia.size();i++) szukajDodatkowychZagrozen(zagrozenia[i]);
				vector<Pole*>::iterator it = max_element(zagrozenia.begin(),zagrozenia.end(),maksymalny_ruch);
				return (*it)->get_Pozycja();
			}
			//OBRONA - MOZLIWOSC STWORZENIA 3
			for(string::size_type i=0;i<ruchy.size();i++){
				for(int k=5;k<11;k++){
					if(ruchy[i]->czyNalezy('X',zagrozeniaX[k])){
						zagrozenia.push_back(ruchy[i]);
						break;
					}
				}
			}
			if(!zagrozenia.empty()){
				for(string::size_type i=0;i<zagrozenia.size();i++) szukajDodatkowychZagrozen(zagrozenia[i]);
				vector<Pole*>::iterator it = max_element(zagrozenia.begin(),zagrozenia.end(),maksymalny_ruch);
				return (*it)->get_Pozycja();
			}
			
			return ruchy[0]->get_Pozycja();
		
	}

	void Komputer::szukajDodatkowychZagrozen(Pole* p){
		p->set_wart(0);
		for(int i=0;i<11;i++){
			p->czyNalezy('0',zagrozenia0[i]);
		}
	}

	bool Komputer::rusz(int pn, int pz){
		plansza->pole[pn][pz]->set_typ(stanGry->get_czyjaKolej()+1);
		plansza->uaktualnijKierunkiPoRuchu(pn,pz);
		if( plansza->czyNalezy(stanGry,pn,pz) )
			return true;
		stanGry->zmienKolej();
		return false;
	}

	void Komputer::wygrany(){};
	void Komputer::przegrany(){};
	void Komputer::wypisz(){cout << "Gracz: " << nazwa  << " poziom: Sredni" << endl;}


	BazaDanych::BazaDanych(){
		Komputer* k;
		k=new Komputer();
		komp.push_back(k);
		k=new Komputer();
		komp.push_back(k);
		gracze.push_back(NULL);
		gracze.push_back(NULL);
	}

	void BazaDanych::wczytajGraczy(){
		vector<int> pom;
		int id;
		fstream stream;
		stream.open("gracze.txt",ios::in);
		if(stream.is_open()){
			stream >> id;
			 while( !stream.eof() ){
				pom.push_back(id);
				stream >> id;
			}
		
		stream.close();
		for(string::size_type i=0;i<pom.size();i++){ wybierzGracza(i,pom[i]);	}
		}
		else{
			fstream stream2;
			stream2.open("gracze.txt",ios::out);
			stream2.close();
			return;
		}
	}

	void BazaDanych::zapiszGraczy(){
		fstream stream;
		vector<Osoba*>::iterator v;
		if(gracze[0] != NULL || gracze[1] != NULL ){
			stream.open("gracze.txt",ios::out);
			if(!stream.good())
				exit(1);
			for ( v=gracze.begin();v!=gracze.end();++v)
				if((*v)!=NULL)
					stream << (*v)->get_id() << " ";
			stream.close();
		}
	}

	bool BazaDanych::dodaj(){
		string nazwa;
		int id=1;
		Osoba *nowy;
		cout << "Podaj nazwe uzytkowanika: ";
		cin >> nazwa;

		for ( p=baza.begin();p!=baza.end();++p){
			if((*p)->get_nazwa() == nazwa){
				cout << "Nazwa uzytkownika juz istnieje w bazie danych" << endl;
				return false;
			}
		}
		if(!baza.empty()){
			p = max_element(baza.begin(),baza.end(),sortuj_id);
			id=(*p)->get_id();
			id++;
		}

		nowy=new Osoba(id,nazwa,0,0);
		baza.push_back(nowy);
		cout << endl;
		return true;
	}

	void BazaDanych::wczytaj(){
		fstream stream;
		Osoba *t;
		char nazwa[100];
		int id,w,p;
		stream.open("database.txt",ios::in);
		if(!stream.is_open()){
			fstream stream2;
			stream2.open("database.txt",ios::out);
			stream2.close();
			return;
		}
		 while( !stream.eof() ){
			stream >> id >> nazwa >> w >> p;
			t=new Osoba(id,nazwa,w,p);
			baza.push_back(t);
		}
		 baza.pop_back();
		 delete t;
		stream.close();
	}

	
	
	void BazaDanych::zapisz(){
		fstream stream;
		stream.open("database.txt",ios::out);
		if(!stream.good())
			exit(1);
		for ( p=baza.begin();p!=baza.end();++p)
			stream << (*p)->get_id() << " " << (*p)->get_nazwa() << " " << (*p)->get_wygrane() << " " << (*p)->get_przegrane()<< endl;
		stream.close();
	}
	void BazaDanych::wyswietl(){
		if(baza.empty()){
			cout << "Baza danych jest pusta" << endl;
			return;
		}
		cout.setf(ios::left);
		cout.width(5);
		cout << "Id";
		cout.width(20);
		cout << "nazwa" ;
		cout.width(10);
		cout << "wygrane";
		cout << "przegrane"<< endl;
		
		for ( p=baza.begin();p!=baza.end();++p){
			cout.width(5);
			cout << (*p)->get_id();
			cout.width(20);
			cout << (*p)->get_nazwa() ;
			cout.width(10);
			cout << (*p)->get_wygrane(); 
			cout << (*p)->get_przegrane() << endl;
		}
		cout << endl;
	}

	bool BazaDanych::usun(){
		if(baza.empty()) return false;
		string nazwa;
		cout << "Podaj nazwe uzytkownika, ktorego chcesz usunac: ";
		cin >> nazwa;
		cout << endl;
		for(p=baza.begin();p!=baza.end();p++){
			if((*p)->get_nazwa()==nazwa){
				if(gracze[0]!=NULL){
					if(gracze[0]->get_id() == (*p)->get_id())
						gracze[0] = NULL;
				}
				if(gracze[1]!=NULL){
					if(gracze[1]->get_id() == (*p)->get_id())
						gracze[1] = NULL;
				}
				baza.erase(p);
				return true;
			}
		}
		return false;
	}


	void BazaDanych::sortuj(){
		if(baza.empty()) return;
		int wybor;
		cout << endl;
		cout << "Menu" << endl;
		cout << "1 - Sortuj wzgledem id" <<endl;
		cout << "2 - Sortuj wzgledem nazwy" <<endl;
		cout << "3 - Sortuj wzgledem wygranych" <<endl;
		cout << "4 - Sortuj wzgledem przegranych" <<endl;
		wybor=kontrola_wprowadzania_danych(1,4);
		switch(wybor){
			case 1:	
				sort(baza.begin(),baza.end(),sortuj_id);
				return;
			case 2:
				sort(baza.begin(),baza.end(),sortuj_nazwa);
				return;
			case 3:
				sort(baza.begin(),baza.end(),sortuj_wygrane);
				return;
			case 4:
				sort(baza.begin(),baza.end(),sortuj_przegrane);
				return;
		}
		
	}
	
	Gracz* BazaDanych::get_gracz(int i){return gracze[i];};
	Gracz* BazaDanych::get_komp(int i){return komp[i];};

	bool BazaDanych::wybierzGracza(int nr,int id){
		for(p=baza.begin();p != baza.end(); ++p){
			if((*p)->get_id()==id){
				gracze[nr]=(*p);
				return true;
			}
		}
		return false;
	}

	void BazaDanych::pokazGraczy(){
		if(gracze[0]!=NULL)
		cout << "Gracz 1:  " << gracze[0]->get_id() << "  " << gracze[0]->get_nazwa() << endl;
		else
			cout << "Nie ustawiono gracza 1" << endl;
		if(gracze[1]!=NULL)
		cout << "Gracz 2:  " << gracze[1]->get_id() << "  " << gracze[1]->get_nazwa() << endl;
		else
			cout << "Nie ustawiono gracza 2" << endl;
	}
	bool BazaDanych::czyUstawiony(int nr){return (gracze[nr] == NULL) ? false : true;}

	bool BazaDanych::czyPusta(){return (baza.empty()) ? true:false;};


	BazaDanych::~BazaDanych(){
		if(!baza.empty()){
			for(string::size_type i=0;i<baza.size();i++)
				delete baza[i];
		}
		delete komp[0];
		delete komp[1];
	}


	Gra::Gra(){
	vector < vector <int> > typy(17,17);
	for(int i=0;i<N+2;i++){
		for(int j=0;j<N+2;j++){
			if(i==0 || i==16)
				typy[i][j]=4;
			else{
				if(j==0 || j==16)
					typy[i][j]=4;
				else
					typy[i][j]=3;
			}
		}
	}

	plansza=new Plansza(typy);
	stanGry=new StanGry(0);
	bazaDanych=new BazaDanych();
	this->wczytajBaze();
	bazaDanych->wczytajGraczy();
	if(stanGry->wczytajStanGry(plansza,g,*bazaDanych))
		czyJestRozgrywka=1;
	else
		czyJestRozgrywka=0;
	}

	void Gra::pokaz_plansze(){plansza->rysuj_plansze();}
	void Gra::wczytajBaze(){bazaDanych->wczytaj();}
	void Gra::wyswietl_menu_glowne(){
		int wybor;
		cout << endl;
		cout << "Menu" << endl;
		cout << "1 - Nowa gra" <<endl;
		cout << "2 - Wyniki" <<endl;
		cout << "3 - Opcje" <<endl;
		cout << "4 - Koniec" <<endl;
		wybor=kontrola_wprowadzania_danych(1,4);
		switch(wybor){
			case 1:	
				this->wyswietl_menu_gry();
				return;
			case 2:
				this->wyswietl_wyniki();
				return;
			case 3:
				this->wyswietl_opcje();
				return;
			case 4:
				bazaDanych->zapisz();
				bazaDanych->zapiszGraczy();
				if(this->czyJestRozgrywka)
					this->wyswietl_menu_zapisu();
				czyKoniec=true;
				return;
		}
	}

	void Gra::wyswietl_opcje(){
		if(bazaDanych->czyPusta()){
			cout << "Baza danych jest pusta, dodaj najpierw uzytkownikow"<< endl;
			return;
		}
		int wybor;
		int id;
		cout << endl;
		cout << "OPCJE" << endl;
		cout << endl;
		bazaDanych->pokazGraczy();
		cout << endl;
		cout << "1 - Ustaw gracz nr 1" <<endl;
		cout << "2 - Ustaw gracz nr 2" <<endl;
		cout << "3 - Powrot do menu glownego" <<endl;
		wybor=kontrola_wprowadzania_danych(1,3);
		switch(wybor){
			case 1:	
				bazaDanych->wyswietl();
				cout << "Podaj id gracza: ";
				cin >> id;
				while(!bazaDanych->wybierzGracza(0,id)){
					cout << "Podaj id gracza: ";
					cin >> id;
				}
				bazaDanych->zapiszGraczy();
				wyswietl_opcje();
				return;
			case 2:
				bazaDanych->wyswietl();
				cout << "Podaj id gracza: ";
				cin >> id;
				while(!bazaDanych->wybierzGracza(1,id)){
					cout << "Podaj id gracza: ";
					cin >> id;
				}
				bazaDanych->zapiszGraczy();
				wyswietl_opcje();
				return;
			case 3:
				this->wyswietl_menu_glowne();
				return;
		}

	}

	void Gra::wyswietl_menu_gry(){
		int wybor,opcja;
		cout << "Menu" << endl;
		cout << "1 - Nowa gra" <<endl;
		cout << "2 - Kontynuuj gre" <<endl;
		cout << "3 - Powrot do menu glownego" << endl;
		wybor=kontrola_wprowadzania_danych(1,3);
		switch(wybor){
			case 1:
				if(this->czyJestRozgrywka){
					cout << "Uwaga: istnieje niedokonczona rozgrywka, co chcesz zrobic?" << endl;
					cout << "1. Graj -  poprzednia gra zostanie utracona" << endl;
					cout << "2. Wroc" << endl;
					opcja=kontrola_wprowadzania_danych(1,2);
					switch(opcja){
					case 1:
						remove("stangry.txt");
						czyJestRozgrywka=false;
						plansza->wyczyscPlansze();
						stanGry->set_czyjaKolej(0);
						g.clear();
						this->wyswietl_menu_nowej_gry();
						return;
					case 2:
						wyswietl_menu_gry();
						return;
					}
				}
				else 
					this->wyswietl_menu_nowej_gry();
					return;
			case 2:
				this->wyswietl_menu_kontynuacji();
				return;
			case 3:
				this->wyswietl_menu_glowne();
				return;
		}
	
	}

	void Gra::wyswietl_menu_kontynuacji(){
		if(this->czyJestRozgrywka){
			graj();
			wyswietl_menu_glowne();
			return;
		}
		else{
			cout << "Nie odnaleziono zapisanej gry" << endl;
			wyswietl_menu_gry();
		}
	}

	void Gra::wyswietl_menu_nowej_gry(){
		int wybor;
		cout << "Menu" << endl;
		cout << "1 - Gracz vs Gracz" <<endl;
		cout << "2 - Gracz vs Komputer" <<endl;
		cout << "3 - Powrot do menu glownego" << endl;
		wybor=kontrola_wprowadzania_danych(1,3);
		switch(wybor){
			case 1:
				if(!bazaDanych->czyUstawiony(0) || !bazaDanych->czyUstawiony(1)){
					cout << "UWAGA: Co najmniej jeden gracz nie jest ustawiony. Najpierw ustaw graczy w opcjach programu." << endl;
					this->wyswietl_menu_nowej_gry();
				}
				g.push_back(bazaDanych->get_gracz(0));
				g.push_back(bazaDanych->get_gracz(1));
				graj();
				return;
			case 2:
				if(!bazaDanych->czyUstawiony(0) && !bazaDanych->czyUstawiony(1)){
					cout << "UWAGA: Gracz nie jest ustawiony. Najpierw ustaw gracza w opcjach programu." << endl;
					this->wyswietl_menu_nowej_gry();
				}
				g.push_back(bazaDanych->get_gracz(0));
				g.push_back(bazaDanych->get_komp(0));
				graj();
				return;
			case 3:
				this->wyswietl_menu_glowne();
				return;
				
		}
	}

	void Gra::graj(){
		Wsp wsp;
		vector<Gracz*>::iterator p;
		g[0]->ustawStanPlansze(stanGry,plansza);
		g[1]->ustawStanPlansze(stanGry,plansza);
		this->czyJestRozgrywka=true;
		pokaz_plansze();
		while(plansza->czy_zajete()){
			g[stanGry->get_czyjaKolej()]->wypisz();
			wsp=g[stanGry->get_czyjaKolej()]->znajdz_wsp();
			if(wsp.pion==0){
				stanGry->zapiszStanGry(plansza,g);
				this->wyswietl_menu_glowne();
				return;
			}
			while(!plansza->pole[wsp.pion][wsp.poziom]->czyWolny())
				wsp=g[stanGry->get_czyjaKolej()]->znajdz_wsp();
			if(g[stanGry->get_czyjaKolej()]->rusz(wsp.pion,wsp.poziom)){
				g[stanGry->get_czyjaKolej()]->wygrany();
				int pom=stanGry->get_czyjaKolej()%2;
				g[stanGry->get_czyjaKolej()%2]->przegrany();
				pokaz_plansze();
				cout << "WYGRANY: " << endl;
				g[stanGry->get_czyjaKolej()]->wypisz();
				cout << endl;
				this->czyJestRozgrywka=false;
				break;
			}
			pokaz_plansze();
		}
		cout << "Remis" << endl;
		this->czyJestRozgrywka=false;
		pokaz_plansze();
		plansza->wyczyscPlansze();
		g.clear();
		return;
	}

	void Gra::wyswietl_menu_zapisu(){
		char wybor;
		cout << "Czy napewno chcesz zapisac stan gry?(t-TAK, n-NIE)" << endl;
		cin >> wybor;
		while(wybor!=116 && wybor!=110){
			cout << "Podaj poprawne dane" << endl;
			cin>>wybor;
		}
		if(wybor==110){
			remove("stangry.txt");
			return;
		}
		if(wybor==116){
			return;
		}
	}
	void Gra::wyswietl_wyniki(){
		int wybor;
		bazaDanych->wyswietl();
		cout << endl;
		cout << "1 - Dodaj uzytkownika" <<endl;
		cout << "2 - Usun uzytkownika" <<endl;
		cout << "3 - Sortuj dane" <<endl;
		cout << "4 - Powrot do menu" << endl;
		wybor=kontrola_wprowadzania_danych(1,4);
		switch(wybor){
			case 1:
				while(!bazaDanych->dodaj());
				this->wyswietl_wyniki();
				return;
			case 2:
				if(!bazaDanych->usun())
					cout << "Uzytkownika nie ma w bazie danych" <<endl;
				this->wyswietl_wyniki();
				return;
			case 3:
				bazaDanych->sortuj();
				cout << endl;
				this->wyswietl_wyniki();
				return;
			case 4:
				this->wyswietl_menu_glowne();
				return;

		}
	}

	
	

	Gra::~Gra(){		
		delete plansza;
		delete stanGry;
		delete bazaDanych;
	}


void  StanGry::zapiszStanGry(Plansza* plansza,vector<Gracz*>& gracze){
		fstream stream;
		vector <Gracz*>::iterator p;
		stream.open("stangry.txt",ios::out);
		if(!stream.good())
			exit(1);
		stream << this->czyjaKolej;
		for(p=gracze.begin();p != gracze.end(); ++p){
			Gracz& g=**p;
			stream << " " << g.get_id();
		}
		stream << endl;

		for(int i=0; i<N+2 ; i++){
			for(int j=0 ; j<N+2 ; j++){
				stream << plansza->pole[i][j]->get_typ() << " ";
			}
			stream << endl;
		}
		stream.close();
	}

bool StanGry::wczytajStanGry(Plansza* plansza,vector<Gracz*>& gracze,BazaDanych& baza){
		fstream stream;
		int p;
		stream.open("stangry.txt",ios::in);
		if(!stream.good())
			return false;
		stream >> this->czyjaKolej;
		for(int i=0;i<2;i++){
			stream >> p;
			if(p == (-1)){
				gracze.push_back(baza.get_komp(0));
			}
			else{
				baza.wybierzGracza(i,p);
				gracze.push_back(baza.get_gracz(i));
			}
		}
		
		for(int i=0; i<N+2 ; i++){
			for(int j=0 ; j<N+2 ; j++){
				stream >> p;
				plansza->pole[i][j]->set_typ(p);
			}
			
		}
		stream.close();
		remove("stangry.txt");
		return true;
	}

int kontrola_wprowadzania_danych(int lewy, int prawy){
	int wybor;
	cin>>wybor;
		while(wybor<lewy || wybor >prawy){
			cout << "Podaj poprawne dane" << endl;
			cin>>wybor;
		}
	return wybor;
}

int main(){

Gra *Ngra=new Gra();
while(!czyKoniec){
Ngra->wyswietl_menu_glowne();
}
delete Ngra;
_CrtDumpMemoryLeaks();
return 0;
}
