#include <stdlib.h>
#include "GameUtil.h"
#include "PowerUp.h"
#include "BoundingShape.h"

PowerUp::PowerUp(void) : GameObject("PowerUp")
{
	mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
}


PowerUp::~PowerUp(void)
{
}

void PowerUp::Render(void)
{
	// Scales everything by SF 0.5
	// glScalef(0.5, 0.5, 0.5);
	// Start drawing lines
	glBegin(GL_LINE_LOOP);
	// Set colour to white
	glColor3f(0.9, 0.9, 0.9);
	// Add vertices to draw an square
	glVertex3f(-3, -3, 0.0);
	//glVertex3f(-10, 0, 0.0);
	glVertex3f(-3, 3, 0.0);
	//glVertex3f(0, 10, 0.0);
	glVertex3f(3, 3, 0.0);
	//glVertex3f(10, 0, 0.0);
	glVertex3f(3, -3, 0.0);
	//glVertex3f(0, -10, 0.0);
	// Finish drawing lines
	glEnd();
	// Enable lighting
	glEnable(GL_LIGHTING);
}

bool PowerUp::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() == GameObjectType("Asteroid") || o->GetType() == GameObjectType("Bullet") || o->GetType() == GameObjectType("Shield") || o->GetType() == GameObjectType("AiBullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void PowerUp::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}