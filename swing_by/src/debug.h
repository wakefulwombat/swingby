#pragma once

#include "common.h"
#include "base_objectBase.h"

struct Color {
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

class Debug_Square : public ObjectBase {
private:
	Color col;

public:
	Debug_Square(Point center, Size size, Color col);
	void initialize() override {};
	void update() override;
	void draw() const override;
	void finalize() override {}
};

class Debug_Line : public ObjectBase {
private:
	Color col;
	Point end;

public:
	Debug_Line(Point start, Point end, Color col);
	void initialize() override {};
	void update() override;
	void draw() const override;
	void finalize() override {}
};