#pragma once

#include "base_sceneInGameMainBase.h"

class SceneGameMainEvent : public SceneInGameMainBase {
private:

public:
	SceneGameMainEvent(std::function<void(SceneInGameMainKind)> sceneChanger);
	void initialize() override;
	void update() override;
	void finalize() override;
};