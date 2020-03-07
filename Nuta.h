#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "funkcje.h"

using namespace std;
using namespace cv;

class Nuta
{
	string name;			//nazwa nuty (np. �semka)
	Point position;			//pozycja nuty na osi x, y
	int sound;				//pozycja nuty na pi�ciolinii (od 0 - najwyzsza, do 12 - najni�sza)
	bool isfull;			//okre�la czy nuta jest zamalowana (np. �wier� nuta) - true, czy pusta (np. p� nuta) - false
	bool isline;			//okre�la czy nuta posiada pionow� lini� (mo�e np. to by� ca�a nuta)
	bool isflag;			//okre�la czy nuta posiada chor�giewk� (�semka) - true, czy nie (np. �wier� nuta) - false

public:

	Nuta(string = "brak", Point = Point(0, 0), int = 0, bool = true, bool = false, bool = false);		//domyslny konstruktor

	void check_sound(int);			//sprawdza d�wi�k nuty na podstawie wysoko�ci obrazu wej�ciowego
	void checkLineAndFlag(Mat);		//sprawdza czy nuta posiada pionow� lini� i zwraca true je�li posiada, oraz ustawia atrybut isline na true
	void viewNoteAttr(void);		//wy�wietla wszystkie atrybuty nuty	

	void set_position(int, int);	//ustawia atrybut pozycja
	void set_isfull(bool);			//ustawia atrybut isfull
	void set_isline(bool);			//ustawia atrybut isline
	void set_isflag(bool);			//ustawia atrybut isflag

	string get_name();				//zwraca atrybu nazwa
	Point get_position();			//zwraca atrybut poz_x
	int get_sound();				//zwraca atrybut dzwiek
	bool get_isfull();				//zwraca atrybut isfull
	bool get_isline();				//zwraca atrybut isline
	bool get_isflag();				//zwraca atrybut isflag

	friend void sortNotes();		//deklaracja funkcji przyjaciela
};