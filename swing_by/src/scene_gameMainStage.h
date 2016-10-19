#pragma once

#include "base_sceneInGameMainBase.h"
#include "base_objectBase.h"
#include "controllerFactory.h"
#include "player.h"
#include "mousePointer.h"
#include "map.h"
#include "orbit.h"
#include "explosion.h"
#include "timer.h"
#include "score.h"
#include "scene_gameMainStagePause.h"
#include "scene_gameMainStageGameOver.h"
#include "scene_gameMainStageClear.h"
#include "base_sceneBase.h"
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
	std::shared_ptr<Timer> timer;
	std::shared_ptr<ScoreManager> score;

	std::shared_ptr<SceneGameMainStageGameOver> scene_gameover;
	std::shared_ptr<SceneGameMainStagePause> scene_pause;
	std::shared_ptr<SceneGameMainStageClear> scene_clear;

	bool isPaused, isGameOverNow, isStageCleared;

	void hitCheck();

public:
	SceneGameMainStage(std::function<void(SceneInGameMainKind)> gameMainSceneChanger, std::function<void(SceneKind)> changer, int stage);
	void initialize() override;
	void update() override;
	void finalize() override;

	void enablePauseScene() override { this->isPaused = true; this->scene_pause->initialize(); }
	void enableGameOverScene() override { this->isGameOverNow = true; this->scene_gameover->initialize(); }
};