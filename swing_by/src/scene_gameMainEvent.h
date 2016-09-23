#pragma once

#include "base_sceneInGameMainBase.h"

class SceneGameMainEvent : public SceneInGameMainBase {
private:

public:
	SceneGameMainEvent(ISetNextSceneInGameMain* isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};