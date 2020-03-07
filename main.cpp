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

	//Sprawdzenie czy zdjêcie zosta³o poprawnie wczytane
	if (!img.data)
	{
		cout << "Error: image does not exist";
		getchar();
		return -1;
	}

	//Sprawdzenie czy zdjêcie jest poziome
	if (img.cols < img.rows)
	{
		cout << "Error: image must have horizonstal orientation";
		getchar();
		return -1;
	}

	//Wyœwietlenie zdjêcia wejœciowego
	//imshow("src img", img);

	//Startowanie zegara mierz¹cego czas programu
	double t = (double)getTickCount();

	//Zaszumienie obrazu szumem typu gaussowskiego
	//addGaussianNoise(img);

	//Zaszumienie obrazu szumem typu pieprz i sól
	//addSaltAndPepperNoise(img);

	//Kompresja JPEG
	//JpegCompression(img, 100, "../../images/zapisane/nuty_kompresja100.jpg");

	//Skalowanie obrazu jeœli jego szerokoœæ jest wiêksza ni¿ 640 pikseli lub zakoñczenie programu, gdy jest mniejsza.
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
	//Konwersja obrazu kolorowego do skali skali szaroœci
	cvtColor(img, gray, CV_BGR2GRAY);

	//Znajdowanie du¿ej kontury mog¹cej byæ kartk¹ papieru i przyciêcie obrazu.
	//gray = findPaperSheet(gray);

	Mat gray2 = gray.clone();

	// Wykrywanie piêciolinii
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

	//Znajdowanie pionowych liñ i chor¹giewek nut
	checkNoteLines(img);

	//Sortowanie wg pozycji na osi x
	sortNotes();

	//Wyœwietlanie nut
	viewNotes();
	
	t = ((double)getTickCount() - t) / getTickFrequency();

	//cout << "Execution time: " << t << "s" << endl;
	imshow("img", img);

	waitKey(0);

	return 0;
}