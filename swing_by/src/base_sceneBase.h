#pragma once

#include "base_requiredFunc.h"
#include "interface_setNextScene.h"
#include <memory>

class SceneBase : public RequiredFunc{
protected:
	std::shared_ptr<ISetNextScene> sceneChanger;

public:
	SceneBase(std::shared_ptr<ISetNextScene> &changer){ this->sceneChanger = changer; }
	virtual ~SceneBase(){}
};
