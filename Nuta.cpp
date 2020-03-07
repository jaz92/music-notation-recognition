#include <iostream>
#include "Nuta.h"

using namespace std;
using namespace cv;

Nuta::Nuta(string name, Point position, int sound, bool isfull, bool isline, bool isflag)
{
	this->name = name;
	this->position = position;
	this->sound = sound;
	this->isfull = isfull;
	this->isline = isline;
	this->isflag = isflag;
}

void Nuta::check_sound(int h)
{
	int region = h / 13;
	sound = position.y / region;
}

void Nuta::checkLineAndFlag(Mat img)
{
	Mat roi, roi_out, veritcal;

	int region = img.rows / 13;
	int h = 6 * region;
	int w = 20;
	vector <Point> non_zeros;

	// wyszukiwanie linii górnej
	if (sound > 6)
	{
		roi = img(Rect(position.x, position.y - h, w, h - region));

		veritcal = getStructuringElement(MORPH_RECT, Size(1, h / 2));
		erode(roi, roi_out, veritcal, Point(-1, -1));

		if (countNonZero(roi_out) > 0)
		{
			isline = true;
			if (!isfull) return;	//wyjœcie jeœli nuta niezamalowana

			// wyszukiwanie maksymalnego punktu linii
			findNonZero(roi_out, non_zeros);
			auto max = max_element(non_zeros.begin(), non_zeros.end(), [](const Point &a, const Point &b)
			{
				return a.x < b.x;
			});
			int max_x = max->x;				//najbardziej odsuniety punkt na prawo

			// przesuniecie roi w prawo do znalezienia choragiewki
			roi.adjustROI(0, 0, -max_x - 2, max_x + 2);
			veritcal = getStructuringElement(MORPH_RECT, Size(1, region));
			erode(roi, roi_out, veritcal, Point(-1, -1));
			if (countNonZero(roi_out) > 0)
			{
				isflag = true;
			}		
		}
	}
	// wyszukiwanie linii dolnej
	else if (sound < 6)
	{
		roi = img(Rect(position.x - w, position.y + region, w, h - region));
		veritcal = getStructuringElement(MORPH_RECT, Size(1, h / 2));
		erode(roi, roi_out, veritcal, Point(-1, -1));
		
		if (countNonZero(roi_out) > 0)
		{
			isline = true;
			if (!isfull) return;	//wyjœcie jeœli nuta niezamalowana

			// wyszukiwanie minimalnego punktu linii
			findNonZero(roi_out, non_zeros);
			auto min = min_element(non_zeros.begin(), non_zeros.end(), [](const Point &a, const Point &b)
			{
				return a.x < b.x;
			});
			int min_x = min->x;

			// przesuniêcie w lewo
			roi.adjustROI(0, 0, min_x + 1, -min_x - 1);
			veritcal = getStructuringElement(MORPH_RECT, Size(1, region));
			erode(roi, roi_out, veritcal, Point(-1, -1));
			//imwrite("../../images/zapisane/flag_roi_erode.jpg", ~roi_out);
			
			if (countNonZero(roi_out) > 0)
			{
				isflag = true;
			}
		}
	}
	// sprawdzenie nuty na œrodkowej linii (mo¿e byæ w górê lub w dó³)
	else
	{
		roi = img(Rect(position.x, position.y - h, w, h - region));

		veritcal = getStructuringElement(MORPH_RECT, Size(1, h / 2));
		erode(roi, roi_out, veritcal, Point(-1, -1));

		if (countNonZero(roi_out) > 0)
		{
			isline = true;
			if (!isfull) return;	//wyjœcie jeœli nuta niezamalowana

			// wyszukiwanie maksymalnego punktu linii wysuniêtego w prawo
			findNonZero(roi_out, non_zeros);
			auto max = max_element(non_zeros.begin(), non_zeros.end(), [](const Point &a, const Point &b)
			{
				return a.x < b.x;
			});
			int max_x = max->x;				//najbardziej odsuniety punkt na prawo

			// przesuniecie roi w prawo do znalezienia choragiewki
			roi.adjustROI(0, 0, -max_x - 2, max_x + 2);
			veritcal = getStructuringElement(MORPH_RECT, Size(1, region));
			erode(roi, roi_out, veritcal, Point(-1, -1));
			if (countNonZero(roi_out) > 0)
			{
				isflag = true;
			}
		}

		// sprawdzenie czy linia jest od nuty w dó³, jeœli jest od nuty w górê pominiêcie obliczeñ
		if (!isline)
		{
			roi = img(Rect(position.x - w, position.y + region, w, h - region));

			veritcal = getStructuringElement(MORPH_RECT, Size(1, h / 2));
			erode(roi, roi_out, veritcal, Point(-1, -1));

			if (countNonZero(roi_out) > 0)
			{
				isline = true;
				if (!isfull) return;	//wyjœcie jeœli nuta niezamalowana

				findNonZero(roi_out, non_zeros);
				auto min = min_element(non_zeros.begin(), non_zeros.end(), [](const Point &a, const Point &b)
				{
					return a.x < b.x;
				});
				int min_x = min->x;

				// przesuniêcie w lewo
				roi.adjustROI(0, 0, min_x + 1, -min_x - 1);
				veritcal = getStructuringElement(MORPH_RECT, Size(1, region));
				erode(roi, roi_out, veritcal, Point(-1, -1));
				if (countNonZero(roi_out) > 0)
				{
					isflag = true;
				}
			}
		}
	}
}

void Nuta::viewNoteAttr()
{
	if (isfull && isline && !isflag) name = "cwiercnuta";
	else if (isfull && isflag) name = "osemka";
	else if (!isfull && isline) name = "polnuta";
	else if (!isfull && !isline) name = "cala nuta";
	else name = '0';

	cout << endl;
	cout << "	nazwa nuty: " << name << endl;
	cout << "	pozycja [x, y]: " << position << endl;
	//cout << "dzwiek: " << sound << endl;
	//cout << "zamalowana: ";
	//if (isfull) cout << "tak" << endl;
	//else cout << "nie" << endl;
	//cout << "linia: ";
	//if (isline) cout << "tak" << endl;
	//else cout << "nie" << endl;
	//cout << "choragiewka: ";
	//if (isflag) cout << "tak" << endl;
	//else cout << "nie" << endl;
}

//sety
void Nuta::set_position(int x, int y)
{
	position.x = x;
	position.y = y;
}

void Nuta::set_isfull(bool b)
{
	isfull = b;
}

void Nuta::set_isflag(bool b)
{
	isflag = b;
}

//gety
string Nuta::get_name()
{
	return name;
}

Point Nuta::get_position()
{
	return position;
}

int Nuta::get_sound()
{
	return sound;
}

bool Nuta::get_isfull()
{
	return isfull;
}

bool Nuta::get_isline()
{
	return isline;
}

bool Nuta::get_isflag()
{
	return isflag;
}