#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "funkcje.h"

using namespace std;
using namespace cv;

class Nuta
{
	string name;			//nazwa nuty (np. ósemka)
	Point position;			//pozycja nuty na osi x, y
	int sound;				//pozycja nuty na piêciolinii (od 0 - najwyzsza, do 12 - najni¿sza)
	bool isfull;			//okreœla czy nuta jest zamalowana (np. æwieræ nuta) - true, czy pusta (np. pó³ nuta) - false
	bool isline;			//okreœla czy nuta posiada pionow¹ liniê (mo¿e np. to byæ ca³a nuta)
	bool isflag;			//okreœla czy nuta posiada chor¹giewkê (ósemka) - true, czy nie (np. æwieræ nuta) - false

public:

	Nuta(string = "brak", Point = Point(0, 0), int = 0, bool = true, bool = false, bool = false);		//domyslny konstruktor

	void check_sound(int);			//sprawdza dŸwiêk nuty na podstawie wysokoœci obrazu wejœciowego
	void checkLineAndFlag(Mat);		//sprawdza czy nuta posiada pionow¹ liniê i zwraca true jeœli posiada, oraz ustawia atrybut isline na true
	void viewNoteAttr(void);		//wyœwietla wszystkie atrybuty nuty	

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