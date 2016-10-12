#pragma once

#include "common.h"
#include "base_objectBase.h"

class Debug_Base : public ObjectBase, public std::enable_shared_from_this<Debug_Base> {
private:
	Color col;

public:
	void initialize() override {};
	void finalize() override {}
	void addDraw() override;
};

class Debug_Square : public Debug_Base {
private:
	Color col;

public:
	Debug_Square(Point center, Size size, Color col, int z_sort = 200000);
	void update() override;
	void draw() const override;
};

class Debug_Line : public Debug_Base {
private:
	Color col;
	Point end;

public:
	Debug_Line(Point start, Point end, Color col, int z_sort = 200001);
	void update() override;
	void draw() const override;
};

class Debug_Point : public Debug_Base {
private:
	Color col;
	int r;

public:
	Debug_Point(Point pos, int r, Color col, int z_sort = 200001);
	void update() override;
	void draw() const override;
};