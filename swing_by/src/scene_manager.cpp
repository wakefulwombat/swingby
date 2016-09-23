#include "scene_manager.h"
#include "scene_gameMain.h"
#include "scene_ending.h"
#include "scene_musicRoom.h"
#include "scene_opening.h"
#include "scene_option.h"

SceneManager::SceneManager(){
	this->nextScene = SceneKind::GameMain;
}

void SceneManager::update(){
	if (this->nextScene != SceneKind::None){
		if (this->nowScene != nullptr) {
			this->nowScene->finalize();
			delete(this->nowScene);
		}

		switch (this->nextScene){
		case SceneKind::Ending:
			this->nowScene = new SceneEnding(this);
			break;

		case SceneKind::GameMain:
			this->nowScene = new SceneGameMain(this);
			break;

		case SceneKind::MusicRoom:
			this->nowScene = new SceneMusicRoom(this);
			break;

		case SceneKind::Opening:
			this->nowScene = new SceneOpening(this);
			break;

		case SceneKind::Option:
			this->nowScene = new SceneOption(this);
			break;
		}

		this->nextScene = SceneKind::None;
		this->nowScene->initialize();
	}
	else{
		this->nowScene->update();
	}
}

void SceneManager::finalize(){
	delete this->nowScene;
}