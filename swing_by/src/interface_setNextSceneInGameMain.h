#pragma once

enum class SceneInGameMainKind;

class ISetNextSceneInGameMain {
public:
	virtual ~ISetNextSceneInGameMain() {}
	virtual void setNextSceneInGameMain(SceneInGameMainKind kind) = 0;
};