#pragma once

#include "base_sceneBase.h"
#include "message.h"
#include "button.h"
#include "mousePointer.h"
#include <memory>

class SceneOpening : public SceneBase {
private:
	std::shared_ptr<Message> title;
	std::shared_ptr<Button> buttons[4];
	std::shared_ptr<MousePointer> mouse;

public:
	SceneOpening(std::function<void(SceneKind)> changer, std::function<void(void)> setQuit);
	void initialize() override;
	void update() override;
	void finalize() override;
};