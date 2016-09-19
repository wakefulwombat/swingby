#pragma once

class TaskBase{
public:
	virtual ~TaskBase(){};
	virtual void initialize(){};
	virtual void update() = 0;
	virtual void draw() const = 0;
	virtual void finalize(){};
};