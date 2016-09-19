#ifndef _BASE_OBJECTMANAGERBASE_
#define _BASE_OBJECTMANAGERBASE_

#include "base_objectBase.h"
#include <vector>
#include <memory>

template <class T>
class ObjectManagerBase : public TaskBase{
private:
	std::vector<std::unique_ptr<T>> obj_list;

public:
	int getVectorListSize(){ return this->obj_list.size(); }
	Point getPosition(int vectorIndex){ return this->obj_list[vectorIndex]->getPosition(); }
	Size getSize(int vectorIndex){ return this->obj_list[vectorIndex]->getSize(); }
	bool getValidation(int vectorIndex){ return this->obj_list[vectorIndex]->getValidation(); }
	double getExpansion(int vectorIndex){ return this->obj_list[vectorIndex]->getExpansion(); }
	double getImageRotationRad(int vectorIndex){ return this->obj_list[vectorIndex]->getImageRotationRad(); }

	void setInvalid(int vectorIndex){ this->obj_list[vectorIndex]->setInvalid(); }

	
	void update() override {
		for (auto it = this->obj_list.begin(); it != this->obj_list; ++it){
			if ((*it)->getValidation()) (*it)->update();
		}
	}

	void draw() override { for (auto it = this->obj_list.begin(); it != this->obj_list; ++it) if ((*it)->getValidation()) (*it)->draw(); }

	void finalize() override {
		for (auto it = this->obj_list.begin(); it != this->obj_list; ++it) (*it)->finalize();
		for (auto it = this->obj_list.begin(); it != this->obj_list; ++it) delete(*it);
	}

	virtual ~ObjectManagerBase() {};
};

#endif