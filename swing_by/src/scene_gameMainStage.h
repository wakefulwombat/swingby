#pragma once

#include "base_sceneInGameMainBase.h"
#include "base_objectBase.h"
#include "controllerFactory.h"
#include "player.h"
#include "mousePointer.h"
#include "map.h"
#include "orbit.h"
#include <vector>

class SceneGameMainStage : public SceneInGameMainBase {
private:
	std::shared_ptr<ControllerFactory> control_factory;
	std::shared_ptr<Player> player;
	std::shared_ptr<MousePointer> mouse_pointer;
	std::shared_ptr<Map> map;
	std::shared_ptr<OrbitManager> orbit_manager;

public:
	SceneGameMainStage(const std::shared_ptr<ISetNextSceneInGameMain> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};