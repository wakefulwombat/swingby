#pragma once

#include "common.h"
#include "base_requiredFunc.h"
#include "base_sceneBase.h"
#include <memory>


class Selection{
private:
	Point start, end;
	int count;

public:
	void setPosition(Point start, Point end);
	void setNextAndRun(Point end);
	void reRun();
};


class SceneManager : public RequiredFunc, public std::enable_shared_from_this<SceneManager> {
private:
	SceneKind nextScene;
	std::shared_ptr<SceneBase> nowScene;
	bool quit;

public:
	SceneManager();

	void update() override;
	void finalize() override;

	bool isQuit() { return this->quit; }
};
