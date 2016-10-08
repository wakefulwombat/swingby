#pragma once

#include "common.h"
#include "base_requiredFunc.h"
#include "base_externalObjectControllerBase.h"
#include "base_internalObjectControllerBase.h"
#include <memory>

enum class ControlStatus{
	None,//����Ȃ�
	Movable,//�����ړ��\
	InternalControlled,//�����ړ��s�A������������(���������͏����ɂ�萧��\)
	ExternalControlled//�����ړ��s�A�O������(���������͊O�����s��)
};

//�ړ�����
class MoveObjectProperty{
protected:
	//for moving
	double trans_vel, trans_acc, trans_rad, trans_omega;//���i�^��
	double rotate_vel, rotate_acc, rotate_rad, rotate_omega;//��]�^��

public:
	virtual ~MoveObjectProperty(){}
	double getTransVelNorm() { return this->trans_vel; }
	Point getTransVelVec() { return Point(this->trans_vel*cos(this->trans_rad), this->trans_vel*sin(this->trans_rad)); }
	double getTransRad() { return this->trans_rad; }
	double getRotateVel() { return this->rotate_vel; }
	double getRotateRad() { return this->rotate_rad; }
};

//�A�j���[�V��������
class AnimationObjectProperty{
protected:
	int chip_switch_time;//�L�����`�b�v�̃A�j���[�V�������ԊԊu
	int chip_count;//�L�����`�b�v�p�J�E���^
	int show_chip_index;//�\������L�����`�b�v�ԍ�
	bool repeat;//�A�j���[�V�������J��Ԃ���
	int chipSize;//�A�j���[�V�����`�b�v�̌�

public:
	virtual ~AnimationObjectProperty(){}

	bool isChipSwitchTime() { return (this->chip_count%this->chip_switch_time == 0); }
	bool isRepeatable() { return this->repeat; }
};

class ObjectBase : public RequiredFunc, public ExternalObjectControllerBase, public std::enable_shared_from_this<ObjectBase> {
protected:
	Point position;
	Size size;
	bool validation;
	int count;
	
	ControlStatus control_status;//���䌠
	std::shared_ptr<InternalObjectController> internalController;//��������p

	//for image
	double expansion;//�摜�g�嗦
	double img_rotation;//�摜��]�p�x
	double img_opacity;//�摜�����x(0.0~1.0)

	unsigned int z_sort;//z�\�[�g

public:
	ObjectBase();
	ObjectBase(Point pos, Size size);
	virtual ~ObjectBase(){}

	Point getPosition(){ return this->position; }
	Size getSize() { return this->size*this->expansion; }
	bool getValidation(){ return this->validation; }
	double getExpansion(){ return this->expansion; }
	double getImageRotationRad(){ return this->img_rotation; }

	unsigned int getZSort() { return this->z_sort; }

	//�O������p
	void setInvalid() override final { this->validation = false; }
	void setControlRights(ControlStatus status) override final { this->control_status = status; }
	void setPosition(Point pos) { this->position = pos; }
	void setImageRotationRad(double rad) { this->img_rotation = rad; }
	void setImageOpacity(double opacity) { this->img_opacity = opacity; }//0.0~1.0

	virtual void draw() const = 0;
};
