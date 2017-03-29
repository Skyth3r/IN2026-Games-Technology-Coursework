#ifndef __AISPACESHIP_H__
#define __AISPACESHIP_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class AiSpaceship : public GameObject
{
public:
	AiSpaceship();
	AiSpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	AiSpaceship(const AiSpaceship& s);
	virtual ~AiSpaceship(void);

	virtual void Update(int t);
	virtual void Render(void);

	virtual void Thrust(float t);
	virtual void Rotate(float r);
	virtual void Shoot(void);

	void SetAiSpaceshipShape(shared_ptr<Shape> spaceship_shape) { mAiSpaceshipShape = spaceship_shape; }
	void SetAiThrusterShape(shared_ptr<Shape> thruster_shape) { mAiThrusterShape = thruster_shape; }
	void SetAiBulletShape(shared_ptr<Shape> bullet_shape) { mAiBulletShape = bullet_shape; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList &objects);

	bool mAiShieldOn;


private:
	float mAiThrust;

	shared_ptr<Shape> mAiSpaceshipShape;
	shared_ptr<Shape> mAiThrusterShape;
	shared_ptr<Shape> mAiBulletShape;
};

#endif
