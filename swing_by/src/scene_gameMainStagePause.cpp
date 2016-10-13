#include "scene_gameMainStagePause.h"
#include "input.h"

SceneGameMainStagePause::SceneGameMainStagePause(std::function<void(void)> de_pause) {
	this->de_pause = de_pause;
	this->btn_mgr = std::make_shared<ButtonManager>();
	this->btn_mgr->setNewButton(Point(150, 300), Size(80, 30), "–ß‚ê", 18,  []() {});
	this->btn_mgr->setNewButton(Point(500, 300), Size(80, 30), "‚ä‚ÁI", 18, []() {});
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