#pragma once

#include "base_requiredFunc.h"
#include "message.h"
#include "explosion.h"
#include <memory>
#include <functional>

class SceneGameMainStageClear : public RequiredFunc {
private:
	std::function<void(void)> sceneChanger;
	std::function<void(Point)> setExplosion;
	std::shared_ptr<Message> clear_mes;

	int count;

public:
	SceneGameMainStageClear(std::function<void(void)> sceneChanger, std::function<void(Point)> setExplosion);
	void initialize() override {};
	void update() override;
	void finalize() override {};
};