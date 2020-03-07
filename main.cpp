#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <iostream>
#include "funkcje.h"

using namespace cv;
using namespace std;

int main()
{
	//Wczytanie obrazu
	Mat img = imread("../../images/perspective_dist.jpg");

	//Zapisanie obrazu
	//imwrite("../../images/zapisane/img.jpg", img);

	//Sprawdzenie czy zdj�cie zosta�o poprawnie wczytane
	if (!img.data)
	{
		cout << "Error: image does not exist";
		getchar();
		return -1;
	}

	//Sprawdzenie czy zdj�cie jest poziome
	if (img.cols < img.rows)
	{
		cout << "Error: image must have horizonstal orientation";
		getchar();
		return -1;
	}

	//Wy�wietlenie zdj�cia wej�ciowego
	//imshow("src img", img);

	//Startowanie zegara mierz�cego czas programu
	double t = (double)getTickCount();

	//Zaszumienie obrazu szumem typu gaussowskiego
	//addGaussianNoise(img);

	//Zaszumienie obrazu szumem typu pieprz i s�l
	//addSaltAndPepperNoise(img);

	//Kompresja JPEG
	//JpegCompression(img, 100, "../../images/zapisane/nuty_kompresja100.jpg");

	//Skalowanie obrazu je�li jego szeroko�� jest wi�ksza ni� 640 pikseli lub zako�czenie programu, gdy jest mniejsza.
	if (img.cols > 640)
	{
		medianBlur(img, img, 3);
		img = scaleImage(img, 640);
	}
	else if (img.cols < 640)
	{
		cout << "Error: image to small";
		getchar();
		return -1;
	}
	else medianBlur(img, img, 3);

	Mat gray;
	//Konwersja obrazu kolorowego do skali skali szaro�ci
	cvtColor(img, gray, CV_BGR2GRAY);

	//Znajdowanie du�ej kontury mog�cej by� kartk� papieru i przyci�cie obrazu.
	//gray = findPaperSheet(gray);

	Mat gray2 = gray.clone();

	// Wykrywanie pi�ciolinii
	vector<Vec4i> lines = findLines(gray);

	// Rotacja/transformacja obrazu
	img = transformImg(gray2, lines);

	// Rozmycie i binaryzacja obrazu
	blur(img, img, Size(3, 3));
	adaptiveThreshold(img, img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 255, 20);
	//imwrite("../../images/zapisane/save.bmp", ~img);

	// Wykrywanie zamalowanych nut
	detectFullNotes(img);
	detectNotFullNotes(img);

	//Znajdowanie pionowych li� i chor�giewek nut
	checkNoteLines(img);

	//Sortowanie wg pozycji na osi x
	sortNotes();

	//Wy�wietlanie nut
	viewNotes();
	
	t = ((double)getTickCount() - t) / getTickFrequency();

	//cout << "Execution time: " << t << "s" << endl;
	imshow("img", img);

	waitKey(0);

	return 0;
}