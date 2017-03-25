#include <stdlib.h>
#include "GameUtil.h"
#include "Sheild.h"
#include "BoundingShape.h"

Sheild::Sheild(void) : GameObject("Sheild")
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


Sheild::~Sheild(void)
{
}

void Sheild::Render(void)
{
	// Scales everything by SF 0.5
	//glScalef(0.5, 0.5, 0.5);
	// Start drawing lines
	glBegin(GL_LINE_LOOP);
	// Set colour to Yello
	glColor3f(0.9, 0.9, 0.0);
	// Add vertices to draw an square
	glVertex3f(-1.5, -3.5, 0.0);
	glVertex3f(-3, 0, 0.0);
	glVertex3f(-1.5, 3.5, 0.0);
	glVertex3f(-2, 5, 0.0);
	glVertex3f(2, 3.5, 0.0);
	// Sheild point
	glVertex3f(6, 0, 0.0);
	glVertex3f(1.5, -3.5, 0.0);
	glVertex3f(-2, -5, 0.0);
	// Finish drawing lines
	glEnd();
	// Enable lighting
	glEnable(GL_LIGHTING);
}

bool Sheild::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() == GameObjectType("Asteroid") || o->GetType() == GameObjectType("Bullet") || o->GetType() == GameObjectType("PowerUp")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Sheild::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}