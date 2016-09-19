#pragma once

#include "base_sceneBase.h"
#include "base_sceneInGameMainBase.h"
#include "interface_setNextScene.h"
#include "scene_gameMainPause.h"

class SceneGameMain : public SceneBase , public ISetNextSceneInGameMain{
private:
	//�Q�[�����C�����ł̃V�[���`�F���W
	SceneInGameMainKind nextSceneInGameMain;
	SceneInGameMainBase* nowSceneInGameMain;

	SceneGameMainPause* pause;

public:
	SceneGameMain(ISetNextScene* isetNextScene);
	void initialize() override;
	void update() override;
	void draw() const override;
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