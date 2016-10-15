#pragma once

#include "base_sceneBase.h"

class SceneMusicRoom : public SceneBase {
private:

public:
	SceneMusicRoom(std::function<void(SceneKind)> changer);
	void initialize() override;
	void update() override;
	void finalize() override;
};