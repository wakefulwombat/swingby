#pragma once

#include "base_taskBase.h"
#include "interface_setNextSceneInGameMain.h"

class SceneInGameMainBase : public TaskBase {
protected:
	ISetNextSceneInGameMain* sceneChanger;

public:
	SceneInGameMainBase(ISetNextSceneInGameMain* changer) { this->sceneChanger = changer; }
	virtual ~SceneInGameMainBase() {}
};