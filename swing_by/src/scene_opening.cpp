#include "scene_opening.h"
#include "screen.h"

SceneOpening::SceneOpening(std::function<void(SceneKind)> changer, std::function<void(void)> setQuit) : SceneBase(changer){
	this->title = std::make_shared<Message>(Point(Screen::getWindowSize().width / 2, 180), MessageType::TITLE);

	/*this->buttons[0] = std::make_shared<Button>(Point(150,400), Size(200, 100), "�X�^�[�g", 16, [changer]() {changer(SceneKind::GameMain); });
	this->buttons[1] = std::make_shared<Button>(Point(370,400), Size(200, 100), "����", 16, []() {});
	this->buttons[2] = std::make_shared<Button>(Point(590,400), Size(200, 100), "���y", 16, [changer]() {changer(SceneKind::MusicRoom); });
	this->buttons[3] = std::make_shared<Button>(Point(810, 400), Size(200, 100), "�Q�[���I��", 16, [setQuit]() {setQuit(); });*/
	this->buttons[0] = std::make_shared<Button>(Point(340, 400), Size(200, 100), "�X�^�[�g", 16, [changer]() {changer(SceneKind::GameMain); });
	this->buttons[1] = std::make_shared<Button>(Point(620, 400), Size(200, 100), "�Q�[���I��", 16, [setQuit]() {setQuit(); });


	this->mouse = std::make_shared<MousePointer>();

	Screen::initTargetPositionDeltaCenter(Point());
	Screen::setTargetWorldPosition(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height / 2), 1);
	Screen::setStageSize(Size(960, 1050));
	Screen::setZoomOut(1);
}

void SceneOpening::initialize() {

}

void SceneOpening::update() {
	this->title->update();
	this->mouse->update();

	for (int i = 0; i < 2; ++i) this->buttons[i]->update();
}

void SceneOpening::finalize() {

}