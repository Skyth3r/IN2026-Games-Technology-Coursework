#include "GameUtil.h"
#include "GameWorld.h"
#include "AiBullet.h"
#include "AiSpaceship.h"
#include "BoundingSphere.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
AiSpaceship::AiSpaceship(): GameObject("AiSpaceship"), mAiThrust(0)
{
	mShieldOn = true;
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
AiSpaceship::AiSpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Spaceship", p, v, a, h, r), mAiThrust(0)
{
}

/** Copy constructor. */
AiSpaceship::AiSpaceship(const AiSpaceship& s): GameObject(s), mAiThrust(0)
{
}

/** Destructor. */
AiSpaceship::~AiSpaceship(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this spaceship. */
void AiSpaceship::Update(int t)
{
	// Call parent update function
	GameObject::Update(t);
}

/** Render this spaceship. */
void AiSpaceship::Render(void)
{


	if (mAiSpaceshipShape.get() != NULL)
	{
		mAiSpaceshipShape->Render();
	}

	// If ship is thrusting
	if ((mAiThrust > 0) && (mAiThrusterShape.get() != NULL))
	{
		mAiThrusterShape->Render();
	}


	// Enable lighting
	//glEnable(GL_LIGHTING);
	GameObject::Render();

	if (mShieldOn)
	{
		glScalef(7, 6, 8);
		// Disable lighting for solid colour lines
		glDisable(GL_LIGHTING);
		// Start drawing lines
		glBegin(GL_LINE_LOOP);
		// Add vertices to draw an octagon
		glVertex3f(-7, -7, 0.0);
		glVertex3f(-10, 0, 0.0);
		glVertex3f(-7, 7, 0.0);
		glVertex3f(0, 10, 0.0);
		glVertex3f(7, 7, 0.0);
		glVertex3f(10, 0, 0.0);
		glVertex3f(7, -7, 0.0);
		glVertex3f(0, -10, 0.0);
		// Finish drawing lines
		glEnd();
		// Enable lighting
		glEnable(GL_LIGHTING);
	}
}

/** Fire the rockets. */
void AiSpaceship::Thrust(float t)
{
	mAiThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mAiThrust*cos(DEG2RAD*mAngle);
	mAcceleration.y = mAiThrust*sin(DEG2RAD*mAngle);
}

/** Set the rotation. */
void AiSpaceship::Rotate(float r)
{
	mRotation = r;
}

/** Shoot a bullet. */
void AiSpaceship::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;
	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f Enemyspaceship_heading(cos(DEG2RAD*mAngle), sin(DEG2RAD*mAngle), 0);
	Enemyspaceship_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (Enemyspaceship_heading * 4);
	// Calculate how fast the bullet should travel
	float bullet_speed = 30;
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + Enemyspaceship_heading * bullet_speed;
	// Construct a new bullet
	shared_ptr<GameObject> aibullet
	(new AiBullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
	aibullet->SetBoundingShape(make_shared<BoundingSphere>(aibullet->GetThisPtr(), 2.0f));
	aibullet->SetShape(mAiBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(aibullet);

}

bool AiSpaceship::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Asteroid") && o->GetType() != GameObjectType("SmallAsteroid") && o->GetType() != GameObjectType("Bullet") && o->GetType() != GameObjectType("EnemySpaceship")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void AiSpaceship::OnCollision(const GameObjectList &objects)
{
	if (mShieldOn == true)
	{
			mShieldOn = false;
	}
	else
	{
		mWorld->FlagForRemoval(GetThisPtr());
		mShieldOn = true;
	}
}