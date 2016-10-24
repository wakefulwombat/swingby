#include "scene_manager.h"
#include "scene_gameMain.h"
#include "scene_ending.h"
#include "scene_musicRoom.h"
#include "scene_opening.h"
#include "scene_option.h"

SceneManager::SceneManager(){
	this->nextScene = SceneKind::Opening;
	this->quit = false;
}

void SceneManager::update(){
	if (this->nextScene != SceneKind::None){
		if (this->nowScene != nullptr) {
			this->nowScene->finalize();
		}

		switch (this->nextScene){
		case SceneKind::Ending:
			this->nowScene = std::make_shared<SceneEnding>([this](SceneKind kind) {nextScene = kind; });
			break;

		case SceneKind::GameMain:
			this->nowScene = std::make_shared<SceneGameMain>([this](SceneKind kind) {nextScene = kind; });
			break;

		case SceneKind::MusicRoom:
			this->nowScene = std::make_shared<SceneMusicRoom>([this](SceneKind kind) {nextScene = kind; });
			break;

		case SceneKind::Opening:
			this->nowScene = std::make_shared<SceneOpening>([this](SceneKind kind) {nextScene = kind; }, [this]() {quit = true; });
			break;

		case SceneKind::Option:
			this->nowScene = std::make_shared<SceneOption>([this](SceneKind kind) {nextScene = kind; });
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
	
}