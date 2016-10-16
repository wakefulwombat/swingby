#pragma once

#include "base_requiredFunc.h"
#include "message.h"
#include "explosion.h"
#include <memory>
#include <functional>

class SceneGameMainStageClear : public RequiredFunc {
private:
	std::shared_ptr<ExplosionManager> explosion;
	std::function<void(void)> result;
	std::shared_ptr<Message> clear_mes;

	int count;

public:
	SceneGameMainStageClear(std::function<void(void)> result);
	void initialize() override {};
	void update() override;
	void finalize() override {};
};