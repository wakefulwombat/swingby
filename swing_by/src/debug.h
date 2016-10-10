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

class Debug_Base : public ObjectBase, public std::enable_shared_from_this<Debug_Base> {
private:
	Color col;
};

class Debug_Square : public Debug_Base {
private:
	Color col;

public:
	Debug_Square(Point center, Size size, Color col, int z_sort = 200000);
	void initialize() override {};
	void update() override;
	void draw() const override;
	void finalize() override {}
};

class Debug_Line : public Debug_Base {
private:
	Color col;
	Point end;

public:
	Debug_Line(Point start, Point end, Color col, int z_sort = 200001);
	void initialize() override {};
	void update() override;
	void draw() const override;
	void finalize() override {}
};

class Debug_Point : public Debug_Base {
private:
	Color col;
	int r;

public:
	Debug_Point(Point pos, int r, Color col, int z_sort = 200001);
	void initialize() override {};
	void update() override;
	void draw() const override;
	void finalize() override {}
};