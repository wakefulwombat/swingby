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
	Point& operator+=(const Point& obj);
	Point operator+(const Size& obj);
	Point operator*(const double& d);
	Point operator/(const double& d);

	static Point getRandomPoint(Point leftup, Point rightdown);
	static Point getCircleRandomPoint(Point center, double r, Point leftup, Point rightdown);
};

int Round(double x);
bool fileExistT(char* filepath);//テキスト
bool fileExistB(char* filepath);//バイナリ