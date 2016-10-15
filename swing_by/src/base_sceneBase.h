#pragma once

#include "base_requiredFunc.h"
#include <memory>
#include <functional>

enum class SceneKind {
	Opening,
	Ending,
	GameMain,
	MusicRoom,
	Option,
	None
};

class SceneBase : public RequiredFunc{
protected:
	std::function<void(SceneKind)> sceneChanger;

public:
	SceneBase(std::function<void(SceneKind)> changer){ this->sceneChanger = changer; }
	virtual ~SceneBase(){}
};
