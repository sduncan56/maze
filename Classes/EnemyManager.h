
#pragma once

#include "cocos2d.h"

#include "Enemy.h"
#include "Area.h"

class EnemyManager
{
private:
	Vector<Enemy*> enemies;
	std::vector<ValueMap> *spawnPoints;

public:
	EnemyManager();
	~EnemyManager();

	void addSpawnPoint(ValueMap spawnPoint);
	Enemy* spawnAtRandPoint(Area* area);

	void decide(Vec2 playerPos, Area* area);
	void checkCollisions(Area* area, float dv);
	void moving(Area* area, float dv);

	Vector<Enemy*> getEnemies();
};