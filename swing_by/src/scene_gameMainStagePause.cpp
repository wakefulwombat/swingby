#include "scene_gameMainStagePause.h"
#include "input.h"

SceneGameMainStagePause::SceneGameMainStagePause(std::function<void(void)> de_pause, std::function<void(void)> retry, std::function<void(void)> title) {
	this->de_pause = de_pause;
	this->btn_mgr = std::make_shared<ButtonManager>();
	this->btn_mgr->setNewButton(Point(150, 300), Size(120, 40), "–ß‚é", 18, de_pause);
	this->btn_mgr->setNewButton(Point(400, 300), Size(120, 40), "‚â‚è’¼‚·", 18, retry);
	this->btn_mgr->setNewButton(Point(650, 300), Size(120, 40), "ƒ^ƒCƒgƒ‹‚Ö", 18, title);
}

void SceneGameMainStagePause::initialize() {

}

void SceneGameMainStagePause::update() {
	this->btn_mgr->update();

	if (Input::getKeyCodeDownOnce(KeyType::Common_Pause)) {
		this->de_pause();
	}
}

void SceneGameMainStagePause::finalize() {

}