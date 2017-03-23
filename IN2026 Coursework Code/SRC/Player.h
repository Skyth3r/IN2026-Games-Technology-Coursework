#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameUtil.h"

#include "GameObject.h"
#include "GameObjectType.h"
#include "IPlayerListener.h"
#include "IGameWorldListener.h"
// Added this
#include "PowerUp.h"

class Player : public IGameWorldListener
{
public:
	Player() { mLives = 3; }
	virtual ~Player() {}

	void OnWorldUpdated(GameWorld* world) {}

	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {
	}

	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object)
	{
		// Asteroid collides with Spaceship then a life is lost
		if (object->GetType() == GameObjectType("Spaceship")) {
			mLives -= 1;
			FirePlayerKilled();
		} 
	}

	// POWERUP
	void OnObjectRemoved(GameWorld* world, shared_ptr<PowerUp> object)
	{
		// PowerUp collides with Spaceship then a life is gained
		if (object->GetType() == GameObjectType("Spaceship")) {
			mLives =+ 1;
			//FirePlayerKilled();
		}
	}

	void AddListener(shared_ptr<IPlayerListener> listener)
	{
		mListeners.push_back(listener);
	}

	void FirePlayerKilled()
	{
		// Send message to all listeners
		for (PlayerListenerList::iterator lit = mListeners.begin();
			lit != mListeners.end(); ++lit) {
			(*lit)->OnPlayerKilled(mLives);
		}
	}

	int mLives;

private:
	

	typedef std::list< shared_ptr<IPlayerListener> > PlayerListenerList;

	PlayerListenerList mListeners;
};

#endif
