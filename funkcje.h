#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;
//hog descriptor matlab

Mat scaleImage(Mat, int);		// Funkcja zmniejszaj¹ca rozmiar obrazu wejœciowego do szerokoœci podanej w drugim parametrze z zachowaniem proporcji obrazu.
Mat addGaussianNoise(Mat);		// Funkcja zaszumiaj¹ca obraz szumem typu gaussowskiego.
Mat addSaltAndPepperNoise(Mat);	// Funkcja zaszumiaj¹ca obraz szumem typu pieprz i sól.
void JpegCompression(Mat, int, char*);	// Procedura dokonuj¹ca kompresji obrazu wejœciowego z podanym parametrem kompresji Q (0-100) i zapisuj¹ca wynik w podanej œcie¿ce.
Mat customBlur(Mat);			// Funkcja dokouj¹ca filtracji uœredniaj¹cej obrazu za pomoc¹ dowolnej maski np. z centraln¹ wartoœci¹ wagi równ¹ 0.
void testFilters(Mat, bool, bool);		// Procedura sprawdzaj¹ca ka¿dy filtr z ró¿nymi maskami i zapisuj¹ca wyniki do plików jpg. Atrybuty: obraz wejœciowy, konwersja do skali szaroœci po filtracji, skalowanie po binaryzacji.

Mat morphClosing(Mat, int, Size);
Mat morphOpening(Mat, int, Size);
Mat findPaperSheet(Mat);
vector<Vec4i> findLines(Mat);	// Wykorzystanie metody Hough'a do znalezienia poziomych liñ w obrazie binarnym i ich narysowanie w celu otrzymania piêciu niezale¿nych (po³¹czonych) obiektów.
Mat transformImg(Mat, vector<Vec4i>);
void detectFullNotes(Mat);			// Wykonuje erozjê na obrazie i wykrywa zamalowane nuty.
void FloodFill(Mat, int, int, int, int);	// W³asna implementacja prostego algorytmu Flood Fill
void detectNotFullNotes(Mat);		// Wykrywa niezamalowane nuty.

void sortNotes(void);					// Sortuje nuty wg pozycji na osi x - od lewej do prawej strony.
void checkNoteLines(Mat);
void viewNotes(void);

