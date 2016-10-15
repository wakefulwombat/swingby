#pragma once

#include "base_sceneInGameMainBase.h"

class SceneGameMainResult : public SceneInGameMainBase {
private:

public:
	SceneGameMainResult(std::function<void(SceneInGameMainKind)> sceneChanger);
	void initialize() override;
	void update() override;
	void finalize() override;
};