#pragma once

#include "base_requiredFunc.h"
#include <memory>
#include <functional>

enum class SceneInGameMainKind {
	None,
	StageSelect,
	Stage,
	Result,
	Event
};

class SceneInGameMainBase : public RequiredFunc {
protected:
	std::function<void(SceneInGameMainKind)> sceneChanger;

public:
	SceneInGameMainBase(std::function<void(SceneInGameMainKind)> changer) { this->sceneChanger = changer; }
	virtual ~SceneInGameMainBase() {}
};