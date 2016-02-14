

#pragma once

#include "cocos2d.h"

#include "Player.h"
#include "EventHandler.h"
#include "Area.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Collisions.h"

USING_NS_CC;

class Game : public cocos2d::Layer
{
private:
	Player* player;
	EventHandler* eventhandler;
	Area* area;
	Vector<Enemy*> enemies;
	EnemyManager* enemyManager;
	Collisions collisions;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float delta);
	void gameOver();

	CREATE_FUNC(Game);
};
