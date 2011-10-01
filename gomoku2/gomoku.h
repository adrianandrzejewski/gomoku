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
* Funkcja wczytujaca liczbê od u¿ytkownika
* i sprawdzaj¹ca czy liczba jest z przedzia³u <lewy,prawy>
*
* @param lewy lewy koniec przedzialu
* @param prawy prawy koniec przedzialu 
* @return zwraca wybor uzykownika
*/
int kontrola_wprowadzania_danych(int,int);

/**
* Porownuje wartosc dwóch pól, wykorzystywana przy 
* algorytmie max_element
*
* @param a pierwsze pole
* @param b drugie pole
* @return true jeœli b->wartosc > a->wartosc
*/
bool maksymalny_ruch(Pole* , Pole* );

/**
* Porownuje nazwê 2 u¿ytkowników, wykorzystywana przy sortowaniu
*
* @param a pierwsze uzytkownik
* @param b drugie uzytkownik
* @return true jeœli b->nazwa > a->nazwa
*/
bool sortuj_nazwa(Osoba* , Osoba* );

/**
* Porownuje id 2 u¿ytkowników, wykorzystywana przy sortowaniu
*
* @param a pierwsze uzytkownik
* @param b drugie uzytkownik
* @return true jeœli b->id > a->id
*/
bool sortuj_id(Osoba* , Osoba* );

/**
* Porownuje iloœæ wygranych 2 u¿ytkowników, wykorzystywana przy sortowaniu
*
* @param a pierwsze uzytkownik
* @param b drugie uzytkownik
* @return true jeœli b->wygrane > a->wygrane
*/
bool sortuj_wygrane(Osoba* , Osoba* );

/**
* Porownuje niloœæ przegranych 2 u¿ytkowników, wykorzystywana przy sortowaniu
*
* @param a pierwsze uzytkownik
* @param b drugie uzytkownik
* @return true jeœli b->nprzegrane > a->przegrane
*/
bool sortuj_przegrane(Osoba* , Osoba* );

/**
* Struktura pozwalaj¹ca przechowaæ wspó³rzêdne pola, razem z jego wartoœci¹
*
*/

struct Wsp{
	int pion;
	int poziom;
	int wartosc;
};


/**
* Klasa rezprezentuj¹ca jedno pole, ma swój typ, pozycjê pionow¹ i poziom¹, wartoœæ
* tablica stringów t[] przechowuje informacje o s¹siednich polach  w ka¿dym z 4 kierunków
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
	* Tworzy nowe pole o zadanym typie, ustawia pozycjê pola(pion, poziom)
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
	* Zwraca pozycjê pola
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
	* Sprawdza czy pole nie jest zajête
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
	* Zwraca obecn¹ wartoœæ pola
	*
	* @return wartoœæ
	*/
	int get_wart();

	/**
	* Sprawdza czy obok pola jest jakieœ pole zajmowane przez jakiegoœ z graczy
	*
	* @return true jeœli obok jest pole niepuste
	*/
	bool czyObokNiepuste();

	friend Plansza;
};


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


/**
* Klasa odpowiedzialna na przechowywanie planszy
* Pole[17][17] - tablica dwuwymiarowa sk³adaj¹ca siê z elementów typu Pole
*
*/
class Plansza{	
protected:
	Pole *pole[17][17];
	string szablon[2];
public:
	/**
	* Tworzy pust¹ planszê, dla ka¿dego pola uaktualnia kierunki  i wstawia 2 pocz¹tkowe znaki
	*
	* @param typy - pusta plansza otoczona scianami
	*/
	Plansza(vector<vector <int>>);

	/**
	* Metoda rysujaca planszê
	*
	*/
	void rysuj_plansze();

	/**
	* Metoda uaktualniaj¹ca kierunki dla pola wskazanego w argumencie
	*
	* @param pn - pion
	* @param pz - poziom
	*/
	void uaktualnijKierunki(int , int );

	/**
	* Sprawdza czy pole wskazane z agrumencie nalezy do wygrywaj¹cej pi¹tki
	*
	* @param stanGry - do pobrania informacji czyja jest kolej
	* @param pn - pion
	* @param pz - poziom
	*/
	bool czyNalezy(StanGry*,int , int );

	/**
	* Metoda uaktualniaj¹ca kierunki po ruchu dla pola wskazanego w argumencie we wszystkich 4 kierunkach
	*
	* @param pn - pion
	* @param pz - poziom
	*/
	void uaktualnijKierunkiPoRuchu(int , int );

	/**
	* Metoda wpisuj¹ca do tablicy stringów s¹siednie pola dla wskazanego pola
	*
	* @param pn - pion
	* @param pz - poziom
	* @param kierunki - tablica stringów do której wpisujemy symbole s¹siednich pól
	*/
	void get_kierunki(int , int ,string[] );

	/**
	* Metoda sprawdza czy wszystkie pola na planszy s¹ zajête
	*
	* @return true jeœli przynajmniej jedno pole jest wolne
	*/
	bool czy_zajete();

	/**
	* Metoda czyszcz¹ca planszê, tj ustawiaj¹ce same puste pola
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
	* Klasa bazowa po której dziedzicz¹ klasy Osoby i Komputera
	* Jest klas¹ abstrakcyjn¹
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
	* Klasa przechowuj¹ca informacjê o jednym graczu czyli id, liczbê wygranych/przegranych
	*/
class Osoba:public Gracz{
protected:
	int id;
	int wygrane;
	int przegrane;
public:
	Osoba(int ,string , int , int );


	/**
	* Metoda odpowiadaj¹ca za ruch, stawia pionek w pole podane w argumentach
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
	* @param wsp - wspó³rzêdne ruchu
	*/
	Wsp znajdz_wsp();

	/**
	* Metoda zwiêkszaj¹ca wygrane o 1
	*
	*/
	void wygrany();

	/**
	* Metoda zwiêkszaj¹ca przegrane o 1
	*
	*/
	void przegrany();

	/**
	* Metoda wypisujaca id i nazwe gracza
	*
	*/
	void wypisz();

	/**
	* Metoda ustawiaj¹ca nazwê gracza
	*
	* @param nazwa
	*/
	void set_nazwa(string );

	/**
	* Metoda ustawiaj¹ca iloœæ wygranych
	*
	* @param wygrane
	*/
	void set_wygrane(int );

	/**
	* Metoda ustawiaj¹ca iloœæ przegranych
	*
	* @param przegrane
	*/
	void set_przegrane(int );

	/**
	* Metoda ustawiaj¹ca id gracza
	*
	* @param id
	*/
	int get_id();

	/**
	* Metoda zwracaj¹ca nazwê gracza
	*
	* @return nazwa
	*/
	string get_nazwa();

	/**
	* Metoda zwracaj¹ca iloœæ wygranych gracza
	*
	* @return wygrane
	*/
	int get_wygrane();

	/**
	* Metoda zwracaj¹ca iloœæ przegranych gracza
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
	* Metoda odpowiadaj¹ca za ruch, stawia pionek w pole podane w argumentach
	* i sprawdza czy pole to nalezy do wygrywajacej piatki
	*
	* @param pn - pion
	* @param pz - poziom
	* @param true jesli pole nalezy do wygrywajacej piatki
	*/
	Wsp znajdz_wsp();

	void szukajDodatkowychZagrozen(Pole* );

	/**
	* Algorytm gry komputera, idea zaczerpniêta z artyku³u 
	* http://home.mit.bme.hu/~gtakacs/download/allis1994.pdf
	* 
	* @param pn - pion
	* @param pz - poziom
	* @param true jesli pole nalezy do wygrywajacej piatki
	*/
	bool rusz(int , int );

	/**
	* Metoda która nic nie robi, gdy¿ dla komputera nie ma wygranych 
	*
	*/
	void wygrany();

	/**
	* Metoda która nic nie robi, gdy¿ dla komputera nie ma przegranych
	*
	*/
	void przegrany();

	/**
	* Metoda wypisuj¹ca na ekran informacje ze to komputer
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
	* ustawia aktualnych wartoœæ aktualnych graczy na NULL
	*
	*/
	BazaDanych();

	/**
	* Metoda wczytuj¹ca aktualnych graczy z pliku gracze.txt
	*
	*/
	void wczytajGraczy();

	/**
	* Metoda zapisuj¹ca aktualnych graczy do pliku gracze.txt
	*
	*/
	void zapiszGraczy();

	/**
	* Metoda pobieraj¹ca nazwê u¿ytkownika i dodaj¹ca go do bazy danych
	*
	* @return false jeœli wskazany u¿ytkownik istnieje ju¿ w bazie danych
	*/
	bool dodaj();

	/**
	* Metoda wczytuj¹ca ca³¹ bazê danych z pliku database.txt
	*
	*/
	void wczytaj();
	
	/**
	* Metoda zapisuj¹ca ca³¹ bazê danych do pliku database.txt
	*
	*/
	void zapisz();

	/**
	* Metoda wyœwietlaj¹ca ca³¹ bazê danych na ekranie 
	*
	*/
	void wyswietl();

	/**
	* Metoda pobieraj¹ca nazwê u¿ytkownika i usuwawj¹ca go
	*
	* @return false jeœli u¿ytkownika o wskazanej nazwie nie ma w bazie danych
	*/
	bool usun();

	/**
	* Metoda sotuj¹ca bazê danych wzglêdem pewnego kryterium(id,nazwa,wygrane,przegrane)
	* Do sortowanie wykorzystuje algorytm stl sort
	*
	*/
	void sortuj();
	
	/**
	* Metoda zwraca wskaŸnik do gracza o zadanym indeksie
	*
	* @param nr_indeksu
	* @return wskaŸnik do gracza o zadanym indkesie
	*/
	Gracz* get_gracz(int );

	/**
	* Metoda zwraca wskaŸnik do komputera o zadanym indeksie
	*
	* @param nr_indeksu
	* @return wskaŸnik do komputera o zadanym indkesie
	*/
	Gracz* get_komp(int );

	/**
	* Metoda przeszukuje bazê w poszukiwaniu u¿ytkownika o wskazanym id
	* jeœli takiego znajdzie, ustawia go jako gracza o zadanym numerze(nr)
	*
	* @param nr - nr gracza który ma byæ ustawiony(0 lub 1)
	* @param id - id gracza w bazie danych który ma byæ znaleziony
	* @return true jeœli siê uda³o, false jeœli gracza o wskazanym id
	* nie ma w bazie danych
	*/
	bool wybierzGracza(int ,int );

	/**
	* Metoda wyœwietla na ekranie aktualnie ustawionych graczy
	*
	*/
	void pokazGraczy();

	/**
	* Metoda sprawdza czy gracz o zadanym nr jest ustawiony
	*
	* @param nr_gracz - 0 lub 1
	* @return true jeœli gracz jest ustawiony
	*/
	bool czyUstawiony(int );

	/**
	* Metoda zwracaj¹ca informacjê czy baza danych jest pusta
	*
	* @return true jeœli pusta
	*/
	bool czyPusta();


	/**
	* Destruktor bazy danych
	* Zwalnia ca³¹ bazê danych i komputery
	* 
	*/
	~BazaDanych();


};


	/**
	* Klasa gry - g³ówna klasa programu, zajmuje siê obs³ug¹ zdarzeñ
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
	* Tworzy planszê, stan gry, bazê danych
	* Wczytuje bazê danych, graczy i stan gry jeœli s¹ ustawione
	* 
	*/
	Gra();

	/**
	* Metoda rysuj¹ca planszê
	* 
	*/
	void pokaz_plansze();

	/**
	* Metoda wczytuj¹ca bazê danych
	* 
	*/
	void wczytajBaze();

	/**
	* Wyswietlaj¹ca menu g³ówne, pobieraj¹ca od u¿ytkownika polecenie co chce zrobiæ 
	* i przenosz¹ca do innej funkcji
	* W przypadku zakoñczenia zapisuje bazê danych, graczy, stan gry
	* 
	*/
	void wyswietl_menu_glowne();

	/**
	* Metoda wyœwietla aktualnie ustawionych graczy
	* oraz pozwala na zmianê/ustawienie graczy 
	* 
	*/
	void wyswietl_opcje();

	/**
	* Metoda wyœwietla menu gry, czy ma byæ to nowa gra 
	* czy kontynuacja zapisanej
	* 
	*/
	void wyswietl_menu_gry();

	/**
	* Metoda wyœwietla menu kontynuacji zapisanej gry
	* Jeœli nie ma zapisanej gry, wyœwietla komunikat i
	* cofa do poprzedniego menu
	* 
	*/
	void wyswietl_menu_kontynuacji();

	/**
	* Metoda wyœwietla menu nowej gry gry, czy gracz vs gracz,
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
	* jeœli u¿ytkownik siê na to zgodzi
	* 
	*/
	void wyswietl_menu_zapisu();



	/**
	* Metoda wyœwietla zawartoœæ bazy danych
	* pozwala dodawaæ,usuwaæ,sortowaæ,filtrowaæ dane
	* 
	*/
	void wyswietl_wyniki();

	~Gra();
};

#endif