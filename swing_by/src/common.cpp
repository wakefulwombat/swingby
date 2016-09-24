#include "common.h"
#include "DxLib.h"
#include <math.h>

Size::Size(int width, int height){
	this->width = width;
	this->height = height;
}

Size Size::operator/(const int& i){
	Size tmp;
	tmp.width = this->width / i;
	tmp.height = this->height / i;

	return tmp;
}

Size Size::operator*(const double& d){
	Size tmp;
	tmp.width = (int)(d*this->width);
	tmp.height = (int)(d*this->height);

	return tmp;
}

Size Size::operator+(const Size& obj){
	Size tmp;
	tmp.width = this->width + obj.width;
	tmp.height = this->height + obj.height;

	return tmp;
}

Point::Point(){
	this->x = 0.000000;
	this->y = 0.000000;
}

Point::Point(double x, double y){
	this->x = x;
	this->y = y;
}

Point Point::operator+(const Point& obj){
	Point tmp;
	tmp.x = this->x + obj.x;
	tmp.y = this->y + obj.y;

	return tmp;
}

Point Point::operator-(const Point& obj) {
	Point tmp;
	tmp.x = this->x - obj.x;
	tmp.y = this->y - obj.y;

	return tmp;
}

Point Point::operator+(const Size& obj){
	Point tmp;
	tmp.x = this->x + (double)obj.width;
	tmp.y = this->y + (double)obj.height;

	return tmp;
}

Point &Point::operator+=(const Point& obj){
	this->x += obj.x;
	this->y += obj.y;
	return *this;
}

Point Point::operator*(const double& d){
	Point tmp;
	tmp.x = d*this->x;
	tmp.y = d*this->y;

	return tmp;
}

Point Point::operator/(const double& d){
	Point tmp;
	tmp.x = this->x / d;
	tmp.y = this->y / d;

	return tmp;
}

double Point::getDistance(Point p2) {
	return sqrt(((this->x - p2.x)*(this->x - p2.x) + (this->y - p2.y)*(this->y - p2.y)));
}

Point Point::getRandomPoint(Point leftup, Point rightdown) {
	Point tmp;
	tmp.x = leftup.x + GetRand((int)(rightdown.x - leftup.x));
	tmp.y = leftup.y + GetRand((int)(rightdown.y - leftup.y));
	return tmp;
}

Point Point::getCircleRandomPoint(Point center, double r, Point leftup, Point rightdown) {
	double ang;
	while (true) {
		ang = M_PI*GetRand(3600) / 1800;
		if ((center.x + r*cos(ang) > leftup.x) && (center.x + r*cos(ang) < rightdown.x) && (center.y + r*sin(ang) > leftup.y) && (center.y + r*sin(ang) < rightdown.y)) {
			break;
		}
	}
	return Point(center.x + r*cos(ang), center.y + r*sin(ang));
}

int Round(double x){
	return (int)(x < 0.0 ? x - 0.4999 : x + 0.4999);
}

bool fileExistT(char* filepath) {
	FILE* fp;
	if ((fopen_s(&fp, filepath, "r")) != 0) {
		return false;
	}
	fclose(fp);
	return true;
}

bool fileExistB(char* filepath) {
	FILE* fp;
	if ((fopen_s(&fp, filepath, "rb")) != 0) {
		return false;
	}
	fclose(fp);
	return true;
}