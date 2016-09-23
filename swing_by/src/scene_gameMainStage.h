#pragma once

#include "base_sceneInGameMainBase.h"
#include "base_objectBase.h"
#include "controllerFactory.h"
#include "player.h"
#include <vector>
#include <memory>

class SceneGameMainStage : public SceneInGameMainBase {
private:
	ControllerFactory* control_factory;
	std::unique_ptr<Player> player;

public:
	SceneGameMainStage(ISetNextSceneInGameMain* isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};