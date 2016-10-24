#include "scene_gameMainStageSelect.h"
#include "screen.h"
#include "input.h"

SceneGameMainStageSelect::SceneGameMainStageSelect(std::function<void(SceneInGameMainKind)> sceneChanger, std::function<void(SceneKind)> backToTitle, std::function<void(int)> setSelectStage) : SceneInGameMainBase(sceneChanger) {
	this->setSelectStage = setSelectStage;
	this->backToTitle = backToTitle;

	for (int i = 0; i < 20; ++i) {
		int x = i % 4;
		int y = (i - x) / 4;
		this->buttons.push_back(std::make_shared<ButtonMove>(Point(90 + x * 150, 300 + y * 110), Size(140, 100), "", 20, [setSelectStage, i, this]() {offButtonInsteadOfIndex(i);  setSelectStage(i); }));
	}
	this->buttons[0]->clicked();
	this->button_go = std::make_shared<Button>(Point(800, 450), Size(180, 80), "スタート", 20, [sceneChanger]() {sceneChanger(SceneInGameMainKind::Stage); });

	this->mouse_pointer = std::make_shared<MousePointer>();

	Screen::initTargetPositionDeltaCenter(Point());
	Screen::setTargetWorldPosition(Point(Screen::getWindowSize().width / 2, Screen::getWindowSize().height / 2), 1);
	Screen::setStageSize(Size(960, 1050));
	Screen::setZoomOut(1);
}

void SceneGameMainStageSelect::initialize() {

}

void SceneGameMainStageSelect::update() {
	this->mouse_pointer->update();
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) (*it)->update();
	this->button_go->update();

	if (Input::getMouseWheelRotation() != 0)Screen::addTargetWorldPositionDelta(Point(0, -100)*Input::getMouseWheelRotation(), 10);
	if (Input::getKeyCodeDownOnce(KeyType::Game_VectorTrans_CANCEL)) this->backToTitle(SceneKind::Opening);
}

void SceneGameMainStageSelect::finalize() {

}

void SceneGameMainStageSelect::offButtonInsteadOfIndex(int index) {
	for (unsigned int i = 0; i < this->buttons.size(); ++i) {
		if (i == index) continue;
		this->buttons[i]->off();
	}
}