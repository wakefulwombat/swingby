#pragma once

#include "base_requiredFunc.h"
#include "interface_setNextScene.h"

class SceneBase : public RequiredFunc{
protected:
	ISetNextScene* sceneChanger;

public:
	SceneBase(ISetNextScene* changer){ this->sceneChanger = changer; }
	virtual ~SceneBase(){}
};
