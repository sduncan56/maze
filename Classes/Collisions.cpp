
#include "Collisions.h"

Collisions::Collisions()
{

}

bool Collisions::checkUnitCollisions(Area* area, Player* player, EnemyManager* enemyManager)
{
	Vector<Enemy*> enemies = enemyManager->getEnemies();


	for (auto enemy : enemies)
	{
		if (area->posToTileCoord(player->getPosition()) == area->posToTileCoord(enemy->getPosition()))
		{
			return true;
		}
	}

	return false;
}

