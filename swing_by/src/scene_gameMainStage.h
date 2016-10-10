#pragma once

#include "base_sceneInGameMainBase.h"
#include "base_objectBase.h"
#include "controllerFactory.h"
#include "player.h"
#include "mousePointer.h"
#include "map.h"
#include "orbit.h"
#include "explosion.h"
#include "scene_gameMainStagePause.h"
#include "scene_gameMainStageGameOver.h"
#include "interface_setSceneGameMainStageStatus.h"
#include <vector>

class SceneGameMainStage : public SceneInGameMainBase, public ISetSceneGameMainStageStatus {
private:
	std::shared_ptr<ControllerFactory> control_factory;
	std::shared_ptr<Player> player;
	std::shared_ptr<MousePointer> mouse_pointer;
	std::shared_ptr<Map> map;
	std::shared_ptr<OrbitManager> orbit_manager;
	std::shared_ptr<ExplosionManager> explosion_manager;

	std::shared_ptr<SceneGameMainStageGameOver> scene_gameover;
	std::shared_ptr<SceneGameMainStagePause> scene_pause;

	bool isPaused, isGameOverNow;

	void hitCheck();

public:
	SceneGameMainStage(const std::shared_ptr<ISetNextSceneInGameMain> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;

	void enablePauseScene() override { this->isPaused = true; }
	void enableGameOverScene() override { this->isGameOverNow = true; }
};