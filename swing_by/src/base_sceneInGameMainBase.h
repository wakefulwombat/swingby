#pragma once

#include "base_requiredFunc.h"
#include "interface_setNextSceneInGameMain.h"
#include <memory>

class SceneInGameMainBase : public RequiredFunc {
protected:
	std::shared_ptr<ISetNextSceneInGameMain> sceneChanger;

public:
	SceneInGameMainBase(const std::shared_ptr<ISetNextSceneInGameMain> &changer) { this->sceneChanger = changer; }
	virtual ~SceneInGameMainBase() {}
};