#pragma once

#include "base_sceneBase.h"

class SceneMusicRoom : public SceneBase {
private:

public:
	SceneMusicRoom(const std::shared_ptr<ISetNextScene> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};