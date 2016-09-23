#pragma once

#include "common.h"
#include "base_requiredFunc.h"
#include "base_externalObjectControllerBase.h"
#include "base_internalObjectControllerBase.h"
#include <memory>

enum class ControlStatus{
	Movable,//�����ړ��\
	InternalControled,//�����ړ��s�A������������(���������͏����ɂ�萧��\)
	ExternalControled//�����ړ��s�A�O������(���������͊O�����s��)
};

//�ړ�����
class MoveObjectProperty{
protected:
	//for moving
	double trans_vel, trans_acc, trans_rad, trans_omega;//���i�^��
	double rotate_vel, rotate_acc, rotate_rad, rotate_omega;//��]�^��
	double gravity_move;//�d�͂ɂ�闎���ړ���

public:
	virtual ~MoveObjectProperty(){}
};

//�A�j���[�V��������
class AnimationObjectProperty{
protected:
	int chip_switch_time;//�L�����`�b�v�̃A�j���[�V�������ԊԊu
	int chip_count;//�L�����`�b�v�p�J�E���^
	bool repeat;//�A�j���[�V�������J��Ԃ���
	int chipSize;//�A�j���[�V�����`�b�v�̌�

public:
	virtual ~AnimationObjectProperty(){}
};

class ObjectBase : public RequiredFunc, public ExternalObjectControllerBase{
protected:
	Point position;
	Size size;
	bool validation;
	int count;
	
	ControlStatus control_status;//���䌠
	std::unique_ptr<InternalObjectController> internalController;//��������p

	//for image
	double expansion;//�摜�g�嗦
	double img_rotation;//�摜��]�p�x

	unsigned int z_sort;//z�\�[�g

public:
	virtual ~ObjectBase(){};

	Point getPosition(){ return this->position; };
	Size getSize(){ return this->size; };
	bool getValidation(){ return this->validation; };
	double getExpansion(){ return this->expansion; }
	double getImageRotationRad(){ return this->img_rotation; }

	//�O������p
	void setInvalid() override final { this->validation = false; }
	void setControlRights(ControlStatus status) override final { this->control_status = status; }

	bool operator<(const ObjectBase* obj){ return this->z_sort < obj->z_sort; }

	virtual void draw() const = 0;
};
