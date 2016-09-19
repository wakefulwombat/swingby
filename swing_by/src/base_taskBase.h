#ifndef _BASE_TASKBASE_
#define _BASE_TASKBASE_

class TaskBase{
public:
	virtual ~TaskBase(){};
	virtual void initialize(){};
	virtual void update() = 0;
	virtual void draw() const = 0;
	virtual void finalize(){};
};

#endif