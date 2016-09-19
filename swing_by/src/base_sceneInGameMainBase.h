#pragma once

#include "base_requiredFunc.h"
#include "interface_setNextSceneInGameMain.h"

class SceneInGameMainBase : public RequiredFunc {
protected:
	ISetNextSceneInGameMain* sceneChanger;

public:
	SceneInGameMainBase(ISetNextSceneInGameMain* changer) { this->sceneChanger = changer; }
	virtual ~SceneInGameMainBase() {}
};