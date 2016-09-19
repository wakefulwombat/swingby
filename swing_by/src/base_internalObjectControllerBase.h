#ifndef _BASE_INTERNALOBJECTCONTROLLERBASE_
#define _BASE_INTERNALOBJECTCONTROLLERBASE_

#include "common.h"

enum class ControlStatus;
enum class ChipActionKind;
enum class ChipDirection;

class InternalObjectControllerBase{
protected:
	
public:
	virtual ~InternalObjectControllerBase(){}
	
	virtual ControlStatus getControlStatus() = 0;
	virtual bool getValidation() = 0;
};

class InternalMoveObjectControllerBase : public InternalObjectControllerBase{
protected:

public:
	virtual ~InternalMoveObjectControllerBase(){}

	virtual Point getNextPosition() = 0;
};


class InternalAnimationObjectControllerBase : public InternalObjectControllerBase{
protected:

public:
	virtual ~InternalAnimationObjectControllerBase(){}
	virtual int getNextAnimation() = 0;
};

class InternalMoveAnimationObjectControllerBase : public InternalObjectControllerBase{
protected:

public:
	virtual ~InternalMoveAnimationObjectControllerBase(){}
	virtual Point getNextPosition() = 0;
	virtual int getNextAnimation() = 0;
};

class InternalCharactorDirectionObjectControllerBase : public InternalMoveObjectControllerBase, public InternalAnimationObjectControllerBase{
protected:

public:
	virtual ~InternalCharactorDirectionObjectControllerBase(){}
	virtual ChipDirection getNextDirection() = 0;
};

class InternalCharactorActionObjectControllerBase : public InternalMoveObjectControllerBase, public InternalAnimationObjectControllerBase{
protected:

public:
	virtual ~InternalCharactorActionObjectControllerBase(){}
	virtual ChipActionKind getNextAction() = 0;
};

#endif