#pragma once

class RequiredFunc{
public:
	virtual ~RequiredFunc(){};
	virtual void initialize(){};
	virtual void update() = 0;
	virtual void finalize(){};
};