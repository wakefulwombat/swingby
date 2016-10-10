#include "debug.h"
#include "screen.h"

Debug_Square::Debug_Square(Point center, Size size, Color color, int z_sort)
{
	this->position = center;
	this->size = size;
	this->expansion = 1.0;
	this->col = color;

	this->z_sort = z_sort;
}

void Debug_Square::update() {
	this->addDraw();
}

void Debug_Square::draw() const {
	Screen::drawSquare(this->position, this->size, this->col);
}



Debug_Line::Debug_Line(Point start, Point end, Color col, int z_sort)
{
	this->position = start;
	this->end = end;
	this->expansion = 1.0;
	this->col = col;

	this->z_sort = z_sort;
}

void Debug_Line::update() {
	this->addDraw();
}

void Debug_Line::draw() const {
	Screen::drawLine(this->position, this->end, this->col);
}



Debug_Point::Debug_Point(Point pos, int r, Color col, int z_sort)
{
	this->position = pos;
	this->r = r;
	this->expansion = 1.0;
	this->col = col;

	this->z_sort = z_sort;
}

void Debug_Point::update() {
	this->addDraw();
}

void Debug_Point::draw() const {
	Screen::drawPoint(this->position, this->r, this->col);
}