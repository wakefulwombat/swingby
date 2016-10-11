#pragma once

#include "common.h"
#include "base_objectBase.h"
#include <memory>
#include <string>

class TextBox : public ObjectBase, public std::enable_shared_from_this<TextBox> {
private:
	std::string name;
	std::string text;
	Size chip_size;
	
	bool visible;
	bool isAppearing, isHiding;

public:
	TextBox(Point center, Size chip_size);
	void initialize() override {}
	void update() override;
	void draw() const override;
	void addDraw() override;
	void finalize() override {}

	void resetCenterPosition(Point pos){ this->position = pos; }
	void resetChipSize(Size size){ this->chip_size = size; }
	void resetName(std::string name){ this->name = name; }
	void resetText(std::string text){ this->text = text; }

	void hide();
	void show();
	bool isChangable() {return ((!this->isAppearing) && (!this->isHiding));}
};