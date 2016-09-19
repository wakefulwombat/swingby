#pragma once

enum class SceneKind;

class ISetNextScene{
public:
	virtual ~ISetNextScene(){}
	virtual void setNextScene(SceneKind kind) = 0;
};
