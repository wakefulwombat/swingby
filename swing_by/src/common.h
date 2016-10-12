#pragma once
#define _USE_MATH_DEFINES

class Size{
public:
	int width, height;
	Size(){};
	Size(int width, int height);
	Size operator/(const int& i);
	Size operator*(const double& d);
	Size operator+(const Size& obj);
};

class Point{
public:
	double x, y;
	Point();
	Point(double x, double y);
	Point operator+(const Point& obj);
	Point operator-(const Point& obj);
	Point& operator+=(const Point& obj);
	Point operator+(const Size& obj);
	Point operator-(const Size& obj);
	Point operator*(const double& d);
	Point operator/(const double& d);

	double getDistance(Point p2);
	static Point getRandomPoint(Point leftup, Point rightdown);
	static Point getCircleRandomPoint(Point center, double r, Point leftup, Point rightdown);
};

class Color {
public:
	int r, g, b;

	Color() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}

	Color(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

int Round(double x);
bool fileExistT(char* filepath);//テキスト
bool fileExistB(char* filepath);//バイナリ