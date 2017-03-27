#ifndef __SHEILD_H__
#define __SHEILD_H__

#include "GameObject.h"

class Shield : public GameObject
{
public:
	Shield(void);
	~Shield(void);
	void Render(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
};

#endif
#pragma once
