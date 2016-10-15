#pragma once

#include "common.h"

class InternalObjectController{
public:
	virtual ~InternalObjectController(){}
	virtual void update() = 0;
	virtual bool isEnd() { return true; }
};
