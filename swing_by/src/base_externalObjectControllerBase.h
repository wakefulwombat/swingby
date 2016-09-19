#ifndef _BASE_EXTERNALOBJECTCONTROLLERBASE_
#define _BASE_EXTERNALOBJECTCONTROLLERBASE_

#include "common.h"

enum class ControlStatus;

class ExternalObjectControllerBase{
protected:

public:
	virtual ~ExternalObjectControllerBase(){}
	virtual void setInvalid() = 0;
	virtual void setControlRights(ControlStatus status) = 0;
};

class ExternalMoveObjectControllerBase: public ExternalObjectControllerBase{
protected:

public:
	virtual ~ExternalMoveObjectControllerBase(){}
	virtual void setNextPosition(Point position) = 0;
};

class ExternalAnimationObjectControllerBase : public ExternalObjectControllerBase{
protected:

public:
	virtual ~ExternalAnimationObjectControllerBase(){}
	virtual void setNextAnimation() = 0;
};

class ExternalMoveAnimationObjectControllerBase : public ExternalObjectControllerBase{
protected:

public:
	virtual ~ExternalMoveAnimationObjectControllerBase(){}
	virtual void setNextPosition(Point position) = 0;
	virtual void setNextAnimation() = 0;
};

class ExternalCharactorDirectionObjectControllerBase : public ExternalMoveObjectControllerBase, public ExternalAnimationObjectControllerBase{
protected:

public:
	virtual ~ExternalCharactorDirectionObjectControllerBase(){}
	virtual void setNextDirection() = 0;
};

class ExternalCharactorActionObjectControllerBase : public ExternalMoveObjectControllerBase, public ExternalAnimationObjectControllerBase{
protected:

public:
	virtual ~ExternalCharactorActionObjectControllerBase(){}
	virtual void setNextAction() = 0;
};
#endif