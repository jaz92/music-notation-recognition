#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;
//hog descriptor matlab

Mat scaleImage(Mat, int);		// Funkcja zmniejszaj�ca rozmiar obrazu wej�ciowego do szeroko�ci podanej w drugim parametrze z zachowaniem proporcji obrazu.
Mat addGaussianNoise(Mat);		// Funkcja zaszumiaj�ca obraz szumem typu gaussowskiego.
Mat addSaltAndPepperNoise(Mat);	// Funkcja zaszumiaj�ca obraz szumem typu pieprz i s�l.
void JpegCompression(Mat, int, char*);	// Procedura dokonuj�ca kompresji obrazu wej�ciowego z podanym parametrem kompresji Q (0-100) i zapisuj�ca wynik w podanej �cie�ce.
Mat customBlur(Mat);			// Funkcja dokouj�ca filtracji u�redniaj�cej obrazu za pomoc� dowolnej maski np. z centraln� warto�ci� wagi r�wn� 0.
void testFilters(Mat, bool, bool);		// Procedura sprawdzaj�ca ka�dy filtr z r�nymi maskami i zapisuj�ca wyniki do plik�w jpg. Atrybuty: obraz wej�ciowy, konwersja do skali szaro�ci po filtracji, skalowanie po binaryzacji.

Mat morphClosing(Mat, int, Size);
Mat morphOpening(Mat, int, Size);
Mat findPaperSheet(Mat);
vector<Vec4i> findLines(Mat);	// Wykorzystanie metody Hough'a do znalezienia poziomych li� w obrazie binarnym i ich narysowanie w celu otrzymania pi�ciu niezale�nych (po��czonych) obiekt�w.
Mat transformImg(Mat, vector<Vec4i>);
void detectFullNotes(Mat);			// Wykonuje erozj� na obrazie i wykrywa zamalowane nuty.
void FloodFill(Mat, int, int, int, int);	// W�asna implementacja prostego algorytmu Flood Fill
void detectNotFullNotes(Mat);		// Wykrywa niezamalowane nuty.

void sortNotes(void);					// Sortuje nuty wg pozycji na osi x - od lewej do prawej strony.
void checkNoteLines(Mat);
void viewNotes(void);

