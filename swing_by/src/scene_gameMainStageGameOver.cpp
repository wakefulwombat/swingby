#include "scene_gameMainStageGameOver.h"
#include "screen.h"

SceneGameMainStageGameOver::SceneGameMainStageGameOver(std::function<void(void)> retry, std::function<void(void)> title) {
	this->btn_mgr = std::make_shared<ButtonManager>();
	this->btn_mgr->setNewButton(Point(280, 400), Size(200, 80), "リトライ", 18, [retry]() {retry(); });
	this->btn_mgr->setNewButton(Point(680, 400), Size(200, 80), "タイトルへ", 18, [title]() {title(); });
	this->gameover_msg = std::make_shared<Message>(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height / 3), MessageType::GAMEOVER);
}

void SceneGameMainStageGameOver::initialize() {

}

void SceneGameMainStageGameOver::update() {
	this->btn_mgr->update();
	this->gameover_msg->update();
}

void SceneGameMainStageGameOver::finalize() {

}