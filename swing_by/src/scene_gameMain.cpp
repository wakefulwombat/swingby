#include "scene_gameMain.h"
#include "scene_gameMainEvent.h"
#include "scene_gameMainResult.h"
#include "scene_gameMainStage.h"
#include "scene_gameMainStageSelect.h"

SceneGameMain::SceneGameMain(const std::shared_ptr<ISetNextScene> &i) : SceneBase(i){
	this->nextSceneInGameMain = SceneInGameMainKind::Stage;
	this->pause = std::make_shared<SceneGameMainPause>(i);
}

void SceneGameMain::initialize() {

}

void SceneGameMain::update() {
	if (this->nextSceneInGameMain != SceneInGameMainKind::None) {
		if (this->nowSceneInGameMain != nullptr) {
			this->nowSceneInGameMain->finalize();
		}

		switch (this->nextSceneInGameMain) {
		case SceneInGameMainKind::Event:
			this->nowSceneInGameMain = std::make_shared<SceneGameMainEvent>(this->shared_from_this());
			break;

		case SceneInGameMainKind::Result:
			this->nowSceneInGameMain = std::make_shared<SceneGameMainResult>(this->shared_from_this());
			break;

		case SceneInGameMainKind::Stage:
			this->nowSceneInGameMain = std::make_shared<SceneGameMainStage>(this->shared_from_this());
			break;

		case SceneInGameMainKind::StageSelect:
			this->nowSceneInGameMain = std::make_shared<SceneGameMainStageSelect>(this->shared_from_this());
			break;
		}

		this->nextSceneInGameMain = SceneInGameMainKind::None;
		this->nowSceneInGameMain->initialize();
	}
	else {
		this->nowSceneInGameMain->update();
	}
}

void SceneGameMain::finalize() {

}
