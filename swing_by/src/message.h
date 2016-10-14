#pragma once

#include "common.h"
#include "base_objectBase.h"
#include "image.h"
#include <memory>

class Message : public ObjectBase , public std::enable_shared_from_this<Message>{
private:
	MessageType type;

public:
	Message(Point pos, MessageType type);
	void update() override;
	void draw() const override;
	void addDraw() override;
};