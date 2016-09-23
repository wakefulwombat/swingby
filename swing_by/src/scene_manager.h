#pragma once

#include "common.h"
#include "base_requiredFunc.h"
#include "base_sceneBase.h"
#include "interface_setNextScene.h"

enum class SceneKind{
	Opening,
	Ending,
	GameMain,
	MusicRoom,
	Option,
	None
};

class Selection{
private:
	Point start, end;
	int count;

public:
	void setPosition(Point start, Point end);
	void setNextAndRun(Point end);
	void reRun();
};


class SceneManager : public RequiredFunc, public ISetNextScene{
private:
	SceneKind nextScene;
	SceneBase* nowScene;

public:
	SceneManager();

	void update() override;
	void finalize() override;

	void setNextScene(SceneKind nextScene) override { this->nextScene = nextScene; }
};
