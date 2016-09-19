#ifndef _SCENEMANAGER_
#define _SCENEMANAGER_

#include "common.h"
#include "base_taskBase.h"
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


class SceneManager : public TaskBase, public ISetNextScene{
private:
	SceneKind nextScene;
	SceneBase* nowScene;

public:
	SceneManager();

	void update() override;
	void draw() const override;
	void finalize() override;

	void setNextScene(SceneKind nextScene) override { this->nextScene = nextScene; }
};

#endif