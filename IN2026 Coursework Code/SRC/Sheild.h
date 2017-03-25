#ifndef __SHEILD_H__
#define __SHEILD_H__

#include "GameObject.h"

class Sheild : public GameObject
{
public:
	Sheild(void);
	~Sheild(void);
	void Render(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
};

#endif
#pragma once
