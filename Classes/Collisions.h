

#pragma once

#include "Area.h"
#include "Player.h"
#include "EnemyManager.h"

class Collisions
{
private:


public:
	Collisions();

	bool checkUnitCollisions(Area* area, Player* player, EnemyManager* enemyManager);

};