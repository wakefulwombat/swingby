#include "scene_gameMain.h"
#include "scene_gameMainEvent.h"
#include "scene_gameMainResult.h"
#include "scene_gameMainStage.h"
#include "scene_gameMainStageSelect.h"

SceneGameMain::SceneGameMain(std::function<void(SceneKind)> changer) : SceneBase(changer){
	this->nextSceneInGameMain = SceneInGameMainKind::Stage;
	this->sceneChanger = changer;
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
			this->nowSceneInGameMain = std::make_shared<SceneGameMainEvent>([this](SceneInGameMainKind scene) {nextSceneInGameMain = scene; });
			break;

		case SceneInGameMainKind::Result:
			this->nowSceneInGameMain = std::make_shared<SceneGameMainResult>([this](SceneInGameMainKind scene) {nextSceneInGameMain = scene; });
			break;

		case SceneInGameMainKind::Stage:
			this->nowSceneInGameMain = std::make_shared<SceneGameMainStage>([this](SceneInGameMainKind scene) {nextSceneInGameMain = scene; }, this->sceneChanger);
			break;

		case SceneInGameMainKind::StageSelect:
			this->nowSceneInGameMain = std::make_shared<SceneGameMainStageSelect>([this](SceneInGameMainKind scene) {nextSceneInGameMain = scene; });
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
