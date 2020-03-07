#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "funkcje.h"
#include "Nuta.h"

using namespace cv;
using namespace std;

vector<Nuta> nuty;

Mat scaleImage(Mat input_img, int value)
{
	//obliczanie wspó³czynnika proporcji
	float r = (float)value / input_img.cols;
	Size dim = Size(value, int(input_img.rows * r));

	//wykonanie skalowania
	Mat resized;
	resize(input_img, resized, dim, INTER_AREA);

	return resized;
}

Mat addGaussianNoise(Mat input_img)
{
	double average = 0.0;
	double standard_deviation = 30.0;

	Mat noise_img(input_img.size(), CV_16SC3);
	randn(noise_img, Scalar::all(average), Scalar::all(standard_deviation));
	Mat temp_img;
	input_img.convertTo(temp_img, CV_16SC3);
	addWeighted(temp_img, 1.0, noise_img, 1.0, 0.0, temp_img);
	temp_img.convertTo(input_img, input_img.type());

	return input_img;
}

Mat addSaltAndPepperNoise(Mat input_img)
{
	double noise_percentage = 10.0;
	int img_rows = input_img.rows;
	int img_columns = input_img.cols;
	int img_channels = input_img.channels();
	int noise_points = (int)(((double)img_rows* img_columns*img_channels)*noise_percentage / 100.0);

	for (int count = 0; count < noise_points; count++)
	{
		int row = rand() % img_rows;
		int column = rand() % img_columns;
		int channel = rand() % img_channels;
		uchar* pixel = input_img.ptr(row) + (column*img_channels) + channel;
		*pixel = (rand() % 2 == 1) ? 255 : 0;
	}

	return input_img;
}

void JpegCompression(Mat input_img, int Q, char* filename)
{
	int JPEG_QUALITY = Q;

	vector<int> params;
	params.push_back(CV_IMWRITE_JPEG_QUALITY);
	params.push_back(JPEG_QUALITY);

	imwrite(filename, input_img, params);
}

Mat customBlur(Mat input_img)
{
	Mat kern = (Mat_<float>(3, 3) << 1, 1, 1,
									 1, 0, 1,
									 1, 1, 1);
	
	int suma = sum(kern)[0];
	kern = kern / suma;

	filter2D(input_img, input_img, -1, kern);

	return input_img;
}

void testFilters(Mat img, bool img2grayscale, bool scaling)
{
	Mat blur1;

	blur(img, blur1, Size(3, 3));
	if (img2grayscale) cvtColor(blur1, blur1, CV_BGR2GRAY);
	adaptiveThreshold(blur1, blur1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 255, 20);
	if(scaling) blur1 = scaleImage(blur1, 640);
	imwrite("../../images/zapisane/blur3x3.jpg", blur1);

	blur(img, blur1, Size(5, 5));
	if (img2grayscale) cvtColor(blur1, blur1, CV_BGR2GRAY);
	adaptiveThreshold(blur1, blur1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 255, 20);
	if (scaling) blur1 = scaleImage(blur1, 640);
	imwrite("../../images/zapisane/blur5x5.jpg", blur1);

	blur(img, blur1, Size(7, 7));
	if (img2grayscale) cvtColor(blur1, blur1, CV_BGR2GRAY);
	adaptiveThreshold(blur1, blur1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 255, 20);
	if (scaling) blur1 = scaleImage(blur1, 640);
	imwrite("../../images/zapisane/blur7x7.jpg", blur1);

	GaussianBlur(img, blur1, Size(3, 3), 0.0, 0.0);
	if (img2grayscale) cvtColor(blur1, blur1, CV_BGR2GRAY);
	adaptiveThreshold(blur1, blur1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 255, 20);
	if (scaling) blur1 = scaleImage(blur1, 640);
	imwrite("../../images/zapisane/gaussianblur3x3.jpg", blur1);

	GaussianBlur(img, blur1, Size(5, 5), 0.0, 0.0);
	if (img2grayscale) cvtColor(blur1, blur1, CV_BGR2GRAY);
	adaptiveThreshold(blur1, blur1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 255, 20);
	if (scaling) blur1 = scaleImage(blur1, 640);
	imwrite("../../images/zapisane/gaussianblur5x5.jpg", blur1);

	GaussianBlur(img, blur1, Size(7, 7), 0.0, 0.0);
	if (img2grayscale) cvtColor(blur1, blur1, CV_BGR2GRAY);
	adaptiveThreshold(blur1, blur1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 255, 20);
	if (scaling) blur1 = scaleImage(blur1, 640);
	imwrite("../../images/zapisane/gaussianblur7x7.jpg", blur1);

	medianBlur(img, blur1, 3);
	if (img2grayscale) cvtColor(blur1, blur1, CV_BGR2GRAY);
	adaptiveThreshold(blur1, blur1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 255, 20);
	if (scaling) blur1 = scaleImage(blur1, 640);
	imwrite("../../images/zapisane/medianblur3x3.jpg", blur1);

	medianBlur(img, blur1, 5);
	if (img2grayscale) cvtColor(blur1, blur1, CV_BGR2GRAY);
	adaptiveThreshold(blur1, blur1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 255, 20);
	if (scaling) blur1 = scaleImage(blur1, 640);
	imwrite("../../images/zapisane/medianblur5x5.jpg", blur1);

	medianBlur(img, blur1, 7);
	if (img2grayscale) cvtColor(blur1, blur1, CV_BGR2GRAY);
	adaptiveThreshold(blur1, blur1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 255, 20);
	if (scaling) blur1 = scaleImage(blur1, 640);
	imwrite("../../images/zapisane/medianblur7x7.jpg", blur1);
}

Mat findPaperSheet(Mat img)
{
	cvtColor(img, img, CV_BGR2GRAY);

	// Utworzenie zmiennej przechowuj¹cej kopiê obrazu.
	Mat img2;

	int w = img.cols;
	int h = img.rows;

	//Stworzenie ramki, aby unikn¹æ b³êdów przy operacjach morfologicznych
	copyMakeBorder(img, img2, 5, 5, 5, 5, BORDER_CONSTANT, 0);

	// Zastosowanie morfologicznego gradientu (dylatacja - erozja) do powiêkszenia kontur i wyrównania poziomu jasnoœci.
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(img2, img2, MORPH_GRADIENT, element);

	// Usuniêcie ramki
	img2 = img2(Rect(5, 5, w, h));

	// Binaryzacja metod¹ Otsu
	Mat threshold_output;
	threshold(img2, img2, 0, 255, THRESH_OTSU);

	// Znajdowanie kontur
	vector<vector<Point>> contours;
	findContours(img2, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	// Usuniêcie ma³ych kontur z obrazu
	vector<vector<Point>>::iterator iter;
	for (iter = contours.begin(); iter != contours.end();)
	{
		int area = contourArea(*iter);
		if (area < 10000)
		{
			iter = contours.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// Jeœli nie ma du¿ej kontury zwrócenie niezmienionego obrazu.
	if (contours.empty()) return img;

	// Usuwanie najmniejszych kontur
	if (contours.size() > 1)
	{
		int max = 0;
		for (iter = contours.begin(); iter != contours.end();)
		{
			if (max > contourArea(*iter))
			{
				iter = contours.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	RotatedRect minRect = minAreaRect(Mat(contours[0]));
	Point2f rect_points[4]; 
	minRect.points(rect_points);
	vector<Point2f> minRectPoints, minRectPointsRot;
	minRectPoints.push_back(rect_points[0]);
	minRectPoints.push_back(rect_points[1]);
	minRectPoints.push_back(rect_points[2]);
	minRectPoints.push_back(rect_points[3]);

	// Rysowanie prostok¹tu
	cvtColor(img, img2, CV_GRAY2BGR);
	// draw rectangle
	for (int j = 0; j < 4; j++)
		line(img2, rect_points[j], rect_points[(j + 1) % 4], Scalar(0, 255, 0), 1, 8);

	// Obliczanie macierzy rotacji
	Mat rot_mat = getRotationMatrix2D(minRect.center, minRect.angle, 1.0);
	
	// Wykonanie rotacji obrazu i punktów
	warpAffine(img, img, rot_mat, img.size());
	transform(minRectPoints, minRectPointsRot, rot_mat);

	//Ucinainie obrazu (mo¿na uci¹æ 5% z krawêdzi znalezionego obrazu)
	w = minRectPointsRot[2].x - minRectPointsRot[1].x;
	h = minRectPointsRot[0].y - minRectPointsRot[1].y;
	int w5 = 0.05 * w;
	int h5 = 0.05 * h;
	img = img(Rect(minRectPointsRot[1].x + w5, minRectPointsRot[1].y + h5, w - 2 * w5, h - 2 * h5));

	return img;
}

struct sorting
{
	bool operator() (Point pt1, Point pt2) 
	{ 
		return (pt1.x < pt2.x); 
	}
} sortX;

vector<Vec4i> findLines(Mat img)
{
	// Zastosowanie morfologicznego gradientu
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(img, img, MORPH_GRADIENT, element);

	// Binaryzacja metod¹ Otsu
	threshold(img, img, 0, 255, THRESH_OTSU);

	// Znajdowanie linii za pomoc¹ transformacji Hough'a
	vector<Vec4i> lines;
	int thresh = 300, minLength = 100, maxGap = 20;
	HoughLinesP(img, lines, 1, CV_PI / 180, thresh, minLength, maxGap);

	// Rysowanie linii
	Mat lines_img = Mat::zeros(img.size(), CV_8U);
	for (size_t i = 0; i < lines.size(); i++)
	{
		int x1 = lines[i][0];
		int y1 = lines[i][1];
		int x2 = lines[i][2];
		int y2 = lines[i][3];

		// Rysowanie linii
		line(lines_img, Point(x1, y1), Point(x2, y2), 255, 2, 4);
	}

	//Wyg³adzenie koñców linii
	medianBlur(lines_img, lines_img, 3);

	//Znajdowanie kontur linii w obrazie
	vector<vector<Point>> contours;
	findContours(lines_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	//Sprawdzenie czy istnieje 5 obiektów (piêciolinia)
	if (contours.size() != 5)
	{
		cout << "Error detecting lines";
		getchar();
		exit(1);
	}

	/* Rysowanie kontur
	RNG rng(1234);

	Mat drawing = Mat::zeros(img.size(), CV_8UC3);
	drawing = Scalar(255, 255, 255);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, Scalar(0, 0, 0), CV_FILLED, 8);
		for (int j = 0; j < contours[i].size(); j++)
		{
			Point p = contours[i][j];
			circle(drawing, p, 3, color, CV_FILLED);
			//drawing.at<Vec3b>(p) = Vec3b(0, 0, 255); // zmiana koloru piksela
		}
	}
	*/

	// Sortowanie punktów wektora wzglêdem osi x
	for (size_t i = 0; i < contours.size(); i++)
	{
		sort(contours[i].begin(), contours[i].end(), sortX);
	}

	// Obliczanie œrodkowego punktu koñców linii
	vector<int> min_y;
	vector<int> max_y;
	for (size_t i = 0; i < contours.size(); i++)
	{
		int suma1 = 0;
		int suma2 = 0;
		int licznik1 = 0;
		int licznik2 = 0;
		int size = contours[i].size();
		int min = contours[i][0].x;
		int max = contours[i][size - 1].x;

		for (size_t j = 0; j < size; j++)
		{
			if (min == contours[i][j].x)
			{
				suma1 += contours[i][j].y;
				licznik1++;
			}
			else break;
		}
		min_y.push_back(suma1 / licznik1);

		for (size_t j = size - 1; j > 0; j--)
		{
			if (max == contours[i][j].x)
			{
				suma2 += contours[i][j].y;
				licznik2++;
			}
			else break;
		}
		max_y.push_back(suma2 / licznik2);
	}
	
	// Czyszczenie wektora
	lines.clear();

	// Zapisywanie punktów linii do wektora
	for (size_t i = 0; i < contours.size(); i++)
	{
		size_t size = contours[i].size();
		lines.push_back(0);
		lines[i][0] = contours[i][0].x;
		lines[i][1] = min_y[i];
		lines[i][2] = contours[i][size - 1].x;
		lines[i][3] = max_y[i];
	}

	return lines;
}

Mat transformImg(Mat img, vector<Vec4i> lines)
{
	// Obliczanie k¹ta linii
	int x1 = lines[2][0];
	int y1 = lines[2][1];
	int x2 = lines[2][2];
	int y2 = lines[2][3];

	float angle = atan2(y2 - y1, x2 - x1) * 180.0 / CV_PI;
	
	// Obliczanie centrum obrotu
	Point2f p1(lines[4][0], lines[4][1]);
	Point2f p2(lines[4][2], lines[4][3]);
	Point2f o1(lines[0][2], lines[0][3]);
	Point2f o2(lines[0][0], lines[0][1]);

	Point2f x = o2 - o1;
	Point2f d1 = p1 - o1;
	Point2f d2 = p2 - o2;

	float cross = d1.x * d2.y - d1.y * d2.x;
	double t1 = (x.x * d2.y - x.y * d2.x) / cross;
	Point center = o1 + d1 * t1;

	// Obliczanie macierzy rotacji
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);

	// Wykonanie rotacji
	warpAffine(img, img, rot_mat, img.size());

	// Rotacja punktów
	for (size_t i = 0; i < lines.size(); i++)
	{
		vector<Point> p_in, p_out;
		p_in.push_back(Point(lines[i][0], lines[i][1]));
		p_in.push_back(Point(lines[i][2], lines[i][3]));

		transform(p_in, p_out, rot_mat);

		lines[i][0] = p_out[0].x;
		lines[i][1] = p_out[0].y;
		lines[i][2] = p_out[1].x;
		lines[i][3] = p_out[1].y;
	}

	/*
	// Rysowanie
	cvtColor(dst, dst, CV_GRAY2BGR);
	for (size_t i = 0; i < lines.size(); i++)
	{
		int x1 = lines[i][0];
		int y1 = lines[i][1];
		int x2 = lines[i][2];
		int y2 = lines[i][3];

		line(dst, Point(x1, y1), Point(x2, y2), Scalar(0, 0, 255));
	}
	*/

	// Transformacja perspektywiczna
	p1 = Point(lines[4][0], lines[4][1]);
	p2 = Point(lines[4][2], lines[4][3]);
	o1 = Point(lines[0][0], lines[0][1]);
	o2 = Point(lines[0][2], lines[0][3]);
	
	// Obliczanie wysokoœci i szerokoœci obrazu wyjœciowego
	Point pp = Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
	Point oo = Point((o1.x + o2.x) / 2, (o1.y + o2.y) / 2);
	int H = oo.y - pp.y;

	Point op1 = Point((o1.x + p1.x) / 2, (o1.y + p1.y) / 2);
	Point op2 = Point((o2.x + p2.x) / 2, (o2.y + p2.y) / 2);
	int W = op2.x - op1.x;

	float h = (float)H / 8;
	float dh = 2.5 * h;
	H = H + 2 * dh;

	Point2f inputQuad[4];
	Point2f outputQuad[4];

	// Wybieranie 4 punktów obrazu wejœciowego i wyjœciowego
	inputQuad[0] = Point(p1.x, p1.y - int(dh));
	inputQuad[1] = Point(p2.x, p2.y - int(dh));
	inputQuad[2] = Point(o1.x, o1.y + int(dh));
	inputQuad[3] = Point(o2.x, o2.y + int(dh));

	outputQuad[0] = Point(0, 0);
	outputQuad[1] = Point(W - 1, 0);
	outputQuad[2] = Point(0, H - 1);
	outputQuad[3] = Point(W - 1, H - 1);

	// Wykonanie transformacji perspektywicznej
	Mat lambda = getPerspectiveTransform(inputQuad, outputQuad);
	warpPerspective(img, img, lambda, Size(W, H));
	//imwrite("../../images/zapisane/src_gray.jpg", img);

	// Segmentacja obrazu na 13 regionów zainteresowania
	int region = H / 13;
	int rest = H % 13;
	float wsp = (float)W / (float)H;
	int nH = H - rest;
	int nW = wsp * nH;

	resize(img, img, Size(nW, nH));

	/*
	// rysowanie roi
	cvtColor(img, img, CV_GRAY2BGR);
	for (int i = region; i < nH; i += region)
	{
		line(img, Point(0, i), Point(nW - 1, i), Scalar(0, 0, 255));
	}
	*/

	return img;
}

void detectFullNotes(Mat img)
{
	// Dodanie czarnej ramki do obrazu - wyeliminowanie b³êdu przy erozji przy krawêdzi obrazu (wolniejsza erozja)
	Mat img_border;
	int border = 10;
	copyMakeBorder(img, img, border, border, border, border, BORDER_CONSTANT);
	Mat img2 = img.clone();

	/* Wykorzystanie metody countNonZero do wyszukiwania bia³ych pikseli */
	int nonZeros = 1, i;
	Mat elem = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	
	for (i = 0; nonZeros != 0; i++)
	{
		erode(img2, img2, elem, Point(-1, -1));
		nonZeros = countNonZero(img2);
	}
	erode(img, img, elem, Point(-1, -1), i - 1);

	// usuniêcie ramki (border)
	img = img(Rect(border, border, img.cols - 2 * border, img.rows - 2 * border));

	dilate(img, img, elem, Point(-1, -1));

	vector<vector<Point>> contours;
	findContours(img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	vector<Moments> mu(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		nuty.push_back(Nuta());
		mu[i] = moments(contours[i]);
		Point pos = Point(int(mu[i].m10 / mu[i].m00), int(mu[i].m01 / mu[i].m00));
		nuty.back().set_position(pos.x, pos.y);
		nuty.back().set_isfull(true);
		nuty.back().check_sound(img.rows);
	}
}

void FloodFill(Mat img, int x, int y, int color_in, int color_out)
{
	if (x < 0 || x >= img.cols || y < 0 || y >= img.rows) return;
	if (img.at<uchar>(x, y) != color_in) return;
	img.at<uchar>(x, y) = color_out;
	FloodFill(img, x, y - 1, color_in, color_out);
	FloodFill(img, x + 1, y, color_in, color_out);
	FloodFill(img, x, y + 1, color_in, color_out);
	FloodFill(img, x - 1, y, color_in, color_out);
}

void detectNotFullNotes(Mat img)
{
	// Dodanie czarnej ramki do obrazu - wyeliminowanie b³êdu przy erozji przy krawêdzi obrazu (wolniejsza erozja)
	Mat img_border;
	int border = 10;
	copyMakeBorder(img, img, border, border, border, border, BORDER_CONSTANT);

	// Znajdowanie niezamalowanych nut
	Mat img2;
	Mat ellipse = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	//Mat horizontal = getStructuringElement(MORPH_RECT, Size(img.cols/20, 1));
	//Mat vertical = getStructuringElement(MORPH_RECT, Size(1, 3));
	//erode(img, img2, horizontal);
	//img = img - img2;
	//dilate(img, img, vertical);
	floodFill(img, Point(0, 0), 255, 0, 0, 255);
	//imwrite("../../images/zapisane/flood_fill_result.png", img);
	bitwise_not(img, img);

	// usuniêcie ramki (border)
	img = img(Rect(border, border, img.cols - 2 * border, img.rows - 2 * border));

	dilate(img, img, ellipse);

	vector<vector<Point>> contours;
	findContours(img, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	vector<Moments> mu(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		nuty.push_back(Nuta());
		mu[i] = moments(contours[i]);
		Point pos = Point(int(mu[i].m10 / mu[i].m00), int(mu[i].m01 / mu[i].m00));
		nuty.back().set_position(pos.x, pos.y);
		nuty.back().set_isfull(false);
		nuty.back().check_sound(img.rows);
	}

	/*
	sortNotes();
	for (size_t i = 0; i < nuty.size(); i++)
	{
		cout << endl;
		cout << "  Pozycja nuty: " << nuty[i].get_position() << endl;
		cout << "  Dzwiek nuty: " << nuty[i].get_sound() << endl;
		if (nuty[i].get_isfull())
			cout << "  Zamalowana: " << "tak" << endl;
		else
			cout << "  Zamalowana: " << "nie" << endl;
	}
	*/
}

void sortNotes()
{
	struct less_than_x
	{
		inline bool operator() (const Nuta& n1, const Nuta& n2)
		{
			return (n1.position.x < n2.position.x);
		}
	};

	sort(nuty.begin(), nuty.end(), less_than_x());
}

void checkNoteLines(Mat img)
{
	for (size_t i = 0; i < nuty.size(); i++)
	{
		nuty[i].checkLineAndFlag(img);
	}
}

void viewNotes()
{
	for (size_t i = 0; i < nuty.size(); i++)
	{
		nuty[i].viewNoteAttr();
	}
}