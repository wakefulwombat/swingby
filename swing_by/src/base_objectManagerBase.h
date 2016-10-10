#ifndef _BASE_OBJECTMANAGERBASE_
#define _BASE_OBJECTMANAGERBASE_

#include "base_requiredFunc.h"
#include <vector>
#include <memory>

template <class T>
class ObjectManagerBase : public RequiredFunc{
protected:
	std::vector<std::shared_ptr<T>> obj_list;

public:
	int getVectorListSize(){ return this->obj_list.size(); }
	Point getPosition(int vectorIndex){ return this->obj_list[vectorIndex]->getPosition(); }
	Size getSize(int vectorIndex){ return this->obj_list[vectorIndex]->getSize(); }
	bool getValidation(int vectorIndex){ return this->obj_list[vectorIndex]->getValidation(); }
	double getExpansion(int vectorIndex){ return this->obj_list[vectorIndex]->getExpansion(); }
	double getImageRotationRad(int vectorIndex){ return this->obj_list[vectorIndex]->getImageRotationRad(); }

	void setInvalid(int vectorIndex){ this->obj_list[vectorIndex]->setInvalid(); }

	
	void update() override {
		if (this->obj_list.size() == 0) return;

		for (auto it = this->obj_list.begin(); it != this->obj_list.end();){
			if (!(*it)->getValidation()) {
				it = this->obj_list.erase(it);
				continue;
			}
			(*it)->update();
			++it;
		}
	}

	virtual ~ObjectManagerBase() {};
};

#endif