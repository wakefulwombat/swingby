#include "scene_gameMain.h"
#include "scene_gameMainEvent.h"
#include "scene_gameMainResult.h"
#include "scene_gameMainStage.h"
#include "scene_gameMainStageSelect.h"

SceneGameMain::SceneGameMain(ISetNextScene* i) : SceneBase(i){
	this->nextSceneInGameMain = SceneInGameMainKind::Stage;
	this->pause = new SceneGameMainPause(i);
}

void SceneGameMain::initialize() {

}

void SceneGameMain::update() {
	if (this->nextSceneInGameMain != SceneInGameMainKind::None) {
		if (this->nowSceneInGameMain != nullptr) {
			this->nowSceneInGameMain->finalize();
			delete(this->nowSceneInGameMain);
		}

		switch (this->nextSceneInGameMain) {
		case SceneInGameMainKind::Event:
			this->nowSceneInGameMain = new SceneGameMainEvent(this);
			break;

		case SceneInGameMainKind::Result:
			this->nowSceneInGameMain = new SceneGameMainResult(this);
			break;

		case SceneInGameMainKind::Stage:
			this->nowSceneInGameMain = new SceneGameMainStage(this);
			break;

		case SceneInGameMainKind::StageSelect:
			this->nowSceneInGameMain = new SceneGameMainStageSelect(this);
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
	delete this->nowSceneInGameMain;
	delete this->pause;
}
