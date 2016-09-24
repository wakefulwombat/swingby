#include "base_objectBase.h"

ObjectBase::ObjectBase() {
	this->expansion = 1.0;
	this->img_opacity = 1.0;
	this->img_rotation = 0.0;

	this->count = 0;
	this->validation = true;
	this->z_sort = 0;

	this->position = Point(0, 0);
	this->size = Size(32, 32);
	this->control_status = ControlStatus::None;
	this->internalController = nullptr;
}

ObjectBase::ObjectBase(Point pos, Size size) {
	this->expansion = 1.0;
	this->img_opacity = 1.0;
	this->img_rotation = 0.0;

	this->count = 0;
	this->validation = true;
	this->z_sort = 0;

	this->position = pos;
	this->size = size;
	this->control_status = ControlStatus::None;
	this->internalController = nullptr;
}