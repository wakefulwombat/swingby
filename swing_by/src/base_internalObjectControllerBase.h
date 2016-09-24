#pragma once

#include "common.h"

class InternalObjectController{
public:
	virtual ~InternalObjectController(){}
	virtual void update() = 0;
	virtual void end() = 0;
};
