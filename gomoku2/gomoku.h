#ifndef gomoku_H
#define gomoku_H

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

using namespace std;
#define N 15


class Gracz;
class Osoba;
class Komputer;
class Plansza;
class BazaDanych;
class Pole;

/**
* Funkcja wczytujaca liczb� od u�ytkownika
* i sprawdzaj�ca czy liczba jest z przedzia�u <lewy,prawy>
*
* @param lewy lewy koniec przedzialu
* @param prawy prawy koniec przedzialu 
* @return zwraca wybor uzykownika
*/
int kontrola_wprowadzania_danych(int,int);

/**
* Porownuje wartosc dw�ch p�l, wykorzystywana przy 
* algorytmie max_element
*
* @param a pierwsze pole
* @param b drugie pole
* @return true je�li b->wartosc > a->wartosc
*/
bool maksymalny_ruch(Pole* , Pole* );

/**
* Porownuje nazw� 2 u�ytkownik�w, wykorzystywana przy sortowaniu
*
* @param a pierwsze uzytkownik
* @param b drugie uzytkownik
* @return true je�li b->nazwa > a->nazwa
*/
bool sortuj_nazwa(Osoba* , Osoba* );

/**
* Porownuje id 2 u�ytkownik�w, wykorzystywana przy sortowaniu
*
* @param a pierwsze uzytkownik
* @param b drugie uzytkownik
* @return true je�li b->id > a->id
*/
bool sortuj_id(Osoba* , Osoba* );

/**
* Porownuje ilo�� wygranych 2 u�ytkownik�w, wykorzystywana przy sortowaniu
*
* @param a pierwsze uzytkownik
* @param b drugie uzytkownik
* @return true je�li b->wygrane > a->wygrane
*/
bool sortuj_wygrane(Osoba* , Osoba* );

/**
* Porownuje nilo�� przegranych 2 u�ytkownik�w, wykorzystywana przy sortowaniu
*
* @param a pierwsze uzytkownik
* @param b drugie uzytkownik
* @return true je�li b->nprzegrane > a->przegrane
*/
bool sortuj_przegrane(Osoba* , Osoba* );

/**
* Struktura pozwalaj�ca przechowa� wsp�rz�dne pola, razem z jego warto�ci�
*
*/

struct Wsp{
	int pion;
	int poziom;
	int wartosc;
};


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


/**
* Klasa przechowuj�ca informacj� o aktualnym stanie gry
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
	* Zwraca znak osoby kt�rej jest teraz kolej
	*
	* @return X jesli czyjaKolej==0, 0 w P.P
	*/
	string getZnak();
};


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


	/**
	* Klasa bazowa po kt�rej dziedzicz� klasy Osoby i Komputera
	* Jest klas� abstrakcyjn�
	*
	*/
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

	/**
	* Klasa przechowuj�ca informacj� o jednym graczu czyli id, liczb� wygranych/przegranych
	*/
class Osoba:public Gracz{
protected:
	int id;
	int wygrane;
	int przegrane;
public:
	Osoba(int ,string , int , int );


	/**
	* Metoda odpowiadaj�ca za ruch, stawia pionek w pole podane w argumentach
	* i sprawdza czy pole to nalezy do wygrywajacej piatki
	*
	* @param pn - pion
	* @param pz - poziom
	* @param true jesli pole nalezy do wygrywajacej piatki
	*/
	bool rusz(int , int );

	/**
	* Metoda pobierajaca miejsce na planszy w ktorym gracz chce postawic pionek
	*
	* @param wsp - wsp�rz�dne ruchu
	*/
	Wsp znajdz_wsp();

	/**
	* Metoda zwi�kszaj�ca wygrane o 1
	*
	*/
	void wygrany();

	/**
	* Metoda zwi�kszaj�ca przegrane o 1
	*
	*/
	void przegrany();

	/**
	* Metoda wypisujaca id i nazwe gracza
	*
	*/
	void wypisz();

	/**
	* Metoda ustawiaj�ca nazw� gracza
	*
	* @param nazwa
	*/
	void set_nazwa(string );

	/**
	* Metoda ustawiaj�ca ilo�� wygranych
	*
	* @param wygrane
	*/
	void set_wygrane(int );

	/**
	* Metoda ustawiaj�ca ilo�� przegranych
	*
	* @param przegrane
	*/
	void set_przegrane(int );

	/**
	* Metoda ustawiaj�ca id gracza
	*
	* @param id
	*/
	int get_id();

	/**
	* Metoda zwracaj�ca nazw� gracza
	*
	* @return nazwa
	*/
	string get_nazwa();

	/**
	* Metoda zwracaj�ca ilo�� wygranych gracza
	*
	* @return wygrane
	*/
	int get_wygrane();

	/**
	* Metoda zwracaj�ca ilo�� przegranych gracza
	*
	* @return przegrane
	*/
	int get_przegrane();
};



class Komputer:public Gracz{
public:
	Komputer();
	int get_id();

	/**
	* Metoda odpowiadaj�ca za ruch, stawia pionek w pole podane w argumentach
	* i sprawdza czy pole to nalezy do wygrywajacej piatki
	*
	* @param pn - pion
	* @param pz - poziom
	* @param true jesli pole nalezy do wygrywajacej piatki
	*/
	Wsp znajdz_wsp();

	void szukajDodatkowychZagrozen(Pole* );

	/**
	* Algorytm gry komputera, idea zaczerpni�ta z artyku�u 
	* http://home.mit.bme.hu/~gtakacs/download/allis1994.pdf
	* 
	* @param pn - pion
	* @param pz - poziom
	* @param true jesli pole nalezy do wygrywajacej piatki
	*/
	bool rusz(int , int );

	/**
	* Metoda kt�ra nic nie robi, gdy� dla komputera nie ma wygranych 
	*
	*/
	void wygrany();

	/**
	* Metoda kt�ra nic nie robi, gdy� dla komputera nie ma przegranych
	*
	*/
	void przegrany();

	/**
	* Metoda wypisuj�ca na ekran informacje ze to komputer
	*
	*/
	void wypisz();
};


/**
* Klasa BazaDanych
*
*/
class BazaDanych{
protected:
	deque<Osoba*> baza;
	deque<Osoba*>::iterator p;
	vector<Osoba*> gracze;
	vector<Komputer*> komp;

public:
	/**
	* Konstruktor bazy danych
	* tworzy 2 obiekty typu komputer,
	* ustawia aktualnych warto�� aktualnych graczy na NULL
	*
	*/
	BazaDanych();

	/**
	* Metoda wczytuj�ca aktualnych graczy z pliku gracze.txt
	*
	*/
	void wczytajGraczy();

	/**
	* Metoda zapisuj�ca aktualnych graczy do pliku gracze.txt
	*
	*/
	void zapiszGraczy();

	/**
	* Metoda pobieraj�ca nazw� u�ytkownika i dodaj�ca go do bazy danych
	*
	* @return false je�li wskazany u�ytkownik istnieje ju� w bazie danych
	*/
	bool dodaj();

	/**
	* Metoda wczytuj�ca ca�� baz� danych z pliku database.txt
	*
	*/
	void wczytaj();
	
	/**
	* Metoda zapisuj�ca ca�� baz� danych do pliku database.txt
	*
	*/
	void zapisz();

	/**
	* Metoda wy�wietlaj�ca ca�� baz� danych na ekranie 
	*
	*/
	void wyswietl();

	/**
	* Metoda pobieraj�ca nazw� u�ytkownika i usuwawj�ca go
	*
	* @return false je�li u�ytkownika o wskazanej nazwie nie ma w bazie danych
	*/
	bool usun();

	/**
	* Metoda sotuj�ca baz� danych wzgl�dem pewnego kryterium(id,nazwa,wygrane,przegrane)
	* Do sortowanie wykorzystuje algorytm stl sort
	*
	*/
	void sortuj();
	
	/**
	* Metoda zwraca wska�nik do gracza o zadanym indeksie
	*
	* @param nr_indeksu
	* @return wska�nik do gracza o zadanym indkesie
	*/
	Gracz* get_gracz(int );

	/**
	* Metoda zwraca wska�nik do komputera o zadanym indeksie
	*
	* @param nr_indeksu
	* @return wska�nik do komputera o zadanym indkesie
	*/
	Gracz* get_komp(int );

	/**
	* Metoda przeszukuje baz� w poszukiwaniu u�ytkownika o wskazanym id
	* je�li takiego znajdzie, ustawia go jako gracza o zadanym numerze(nr)
	*
	* @param nr - nr gracza kt�ry ma by� ustawiony(0 lub 1)
	* @param id - id gracza w bazie danych kt�ry ma by� znaleziony
	* @return true je�li si� uda�o, false je�li gracza o wskazanym id
	* nie ma w bazie danych
	*/
	bool wybierzGracza(int ,int );

	/**
	* Metoda wy�wietla na ekranie aktualnie ustawionych graczy
	*
	*/
	void pokazGraczy();

	/**
	* Metoda sprawdza czy gracz o zadanym nr jest ustawiony
	*
	* @param nr_gracz - 0 lub 1
	* @return true je�li gracz jest ustawiony
	*/
	bool czyUstawiony(int );

	/**
	* Metoda zwracaj�ca informacj� czy baza danych jest pusta
	*
	* @return true je�li pusta
	*/
	bool czyPusta();


	/**
	* Destruktor bazy danych
	* Zwalnia ca�� baz� danych i komputery
	* 
	*/
	~BazaDanych();


};


	/**
	* Klasa gry - g��wna klasa programu, zajmuje si� obs�ug� zdarze�
	* 
	*/


class Gra{
protected:
	Plansza *plansza;
	StanGry *stanGry;
	BazaDanych *bazaDanych;
	vector<Gracz*>  g;
	bool czyJestRozgrywka;
public:
	/**
	* Konstruktor nowej gry
	* Tworzy plansz�, stan gry, baz� danych
	* Wczytuje baz� danych, graczy i stan gry je�li s� ustawione
	* 
	*/
	Gra();

	/**
	* Metoda rysuj�ca plansz�
	* 
	*/
	void pokaz_plansze();

	/**
	* Metoda wczytuj�ca baz� danych
	* 
	*/
	void wczytajBaze();

	/**
	* Wyswietlaj�ca menu g��wne, pobieraj�ca od u�ytkownika polecenie co chce zrobi� 
	* i przenosz�ca do innej funkcji
	* W przypadku zako�czenia zapisuje baz� danych, graczy, stan gry
	* 
	*/
	void wyswietl_menu_glowne();

	/**
	* Metoda wy�wietla aktualnie ustawionych graczy
	* oraz pozwala na zmian�/ustawienie graczy 
	* 
	*/
	void wyswietl_opcje();

	/**
	* Metoda wy�wietla menu gry, czy ma by� to nowa gra 
	* czy kontynuacja zapisanej
	* 
	*/
	void wyswietl_menu_gry();

	/**
	* Metoda wy�wietla menu kontynuacji zapisanej gry
	* Je�li nie ma zapisanej gry, wy�wietla komunikat i
	* cofa do poprzedniego menu
	* 
	*/
	void wyswietl_menu_kontynuacji();

	/**
	* Metoda wy�wietla menu nowej gry gry, czy gracz vs gracz,
	* czy gracz vs komputer
	* 
	*/
	void wyswietl_menu_nowej_gry();


	/**
	* Metoda odpowiedzialna za przebieg gry
	* 
	*/
	void graj();

	/**
	* Metoda odpowiedzialna za zapisywanie stanu gry,
	* je�li u�ytkownik si� na to zgodzi
	* 
	*/
	void wyswietl_menu_zapisu();



	/**
	* Metoda wy�wietla zawarto�� bazy danych
	* pozwala dodawa�,usuwa�,sortowa�,filtrowa� dane
	* 
	*/
	void wyswietl_wyniki();

	~Gra();
};

#endif