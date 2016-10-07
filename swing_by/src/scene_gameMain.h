#pragma once

#include "base_sceneBase.h"
#include "base_sceneInGameMainBase.h"
#include "interface_setNextScene.h"
#include "scene_gameMainPause.h"
#include <memory>

class SceneGameMain : public SceneBase , public ISetNextSceneInGameMain, public std::enable_shared_from_this<SceneGameMain>{
private:
	//ゲームメイン内でのシーンチェンジ
	SceneInGameMainKind nextSceneInGameMain;
	std::shared_ptr<SceneInGameMainBase> nowSceneInGameMain;

	std::shared_ptr<SceneGameMainPause> pause;

public:
	SceneGameMain(std::shared_ptr<ISetNextScene> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;

	void setNextSceneInGameMain(SceneInGameMainKind nextScene) override { this->nextSceneInGameMain = nextScene; }
};

enum class SceneInGameMainKind {
	None,
	StageSelect,
	Stage,
	Result,
	Event
};