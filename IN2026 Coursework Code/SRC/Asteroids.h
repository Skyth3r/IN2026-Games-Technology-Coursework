#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include "GameUtil.h"
#include "GameSession.h"
#include "IKeyboardListener.h"
#include "IGameWorldListener.h"
#include "IScoreListener.h" 
#include "ScoreKeeper.h"
#include "Player.h"
#include "IPlayerListener.h"

class GameObject;
class Spaceship;
class AiSpaceship;
class GUILabel;
class PowerUp;

class Asteroids : public GameSession, public IKeyboardListener, public IGameWorldListener, public IScoreListener, public IPlayerListener
{
public:
	Asteroids(int argc, char *argv[]);
	virtual ~Asteroids(void);

	virtual void Start(void);
	virtual void Stop(void);

	// Declaration of IKeyboardListener interface ////////////////////////////////

	void OnKeyPressed(uchar key, int x, int y);
	void OnKeyReleased(uchar key, int x, int y);
	void OnSpecialKeyPressed(int key, int x, int y);
	void OnSpecialKeyReleased(int key, int x, int y);

	// Declaration of IScoreListener interface //////////////////////////////////

	void OnScoreChanged(int score);

	// Declaration of the IPlayerLister interface //////////////////////////////

	void OnPlayerKilled(int lives_left);

	// Declaration of IGameWorldListener interface //////////////////////////////

	void OnWorldUpdated(GameWorld* world) {}
	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {}
	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object);
	// void OnObjectRemoved(GameWorld* world, shared_ptr<PowerUp> object);

	// Override the default implementation of ITimerListener ////////////////////
	void OnTimer(int value);

	shared_ptr<Spaceship> mSpaceship;

private:
	//shared_ptr<Spaceship> mSpaceship;
	shared_ptr<AiSpaceship> mAiSpaceship;
	shared_ptr<PowerUp> mPowerUp;
	shared_ptr<Shield> mShield;
	shared_ptr<GUILabel> mScoreLabel;
	shared_ptr<GUILabel> mLivesLabel;
	// Start Screen Label
	shared_ptr<GUILabel> mStartLabel;
	shared_ptr<GUILabel> mGameOverLabel;
	shared_ptr<GUILabel> mHighScoreLabel;
	shared_ptr<GUILabel> mHighScoreNumLabel;

	uint mLevel;
	uint mAsteroidCount;

	void ResetSpaceship();
	shared_ptr<GameObject> CreateSpaceship();
	shared_ptr<GameObject>CreateAiSpaceship();
	void CreateGUI();
	void CreatePowerUp();
	void CreateShield();
	void CreateAsteroids(const uint num_asteroids);
	shared_ptr<GameObject> CreateExplosion();
	
	const static uint SHOW_GAME_OVER = 0;
	const static uint START_NEXT_LEVEL = 1;
	const static uint CREATE_NEW_PLAYER = 2;

	const static uint SHOW_GAME_START = 3;
	const static uint CREATE_POWERUP = 4;
	const static uint CREATE_SHIELD = 5;
	const static uint AI_SHOOT = 6;
	ScoreKeeper mScoreKeeper;
	Player mPlayer;
	bool mGameStarted;
};

#endif