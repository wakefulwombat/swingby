#include "scene_gameMainStagePause.h"
#include "input.h"
#include "screen.h"

SceneGameMainStagePause::SceneGameMainStagePause(std::function<void(void)> de_pause, std::function<void(void)> retry, std::function<void(void)> title) {
	this->de_pause = de_pause;
	this->btn_mgr = std::make_shared<ButtonManager>();
	this->btn_mgr->setNewButton(Point(230, 400), Size(200, 80), "–ß‚é", 18, de_pause);
	this->btn_mgr->setNewButton(Point(480, 400), Size(200, 80), "‚â‚è’¼‚·", 18, retry);
	this->btn_mgr->setNewButton(Point(730, 400), Size(200, 80), "ƒ^ƒCƒgƒ‹‚Ö", 18, title);

	this->pause_mes = std::make_shared<Message>(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height / 3), MessageType::PAUSE);
}

void SceneGameMainStagePause::initialize() {

}

void SceneGameMainStagePause::update() {
	this->btn_mgr->update();
	this->pause_mes->update();

	if (Input::getKeyCodeDownOnce(KeyType::Common_Pause)) {
		this->de_pause();
	}
}

void SceneGameMainStagePause::finalize() {

}