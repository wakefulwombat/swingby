#pragma once

#include "base_sceneBase.h"

class SceneOpening : public SceneBase {
private:

public:
	SceneOpening(std::shared_ptr<ISetNextScene> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};