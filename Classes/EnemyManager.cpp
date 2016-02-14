

#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	srand(time(0));
	//enemies = new Vector<Enemy*>();
	spawnPoints = new std::vector<ValueMap>();
}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies.at(i);
	}
}

void EnemyManager::addSpawnPoint(ValueMap spawnPoint)
{
	spawnPoints->push_back(spawnPoint);

}

Enemy* EnemyManager::spawnAtRandPoint(Area* area)
{
	ValueMap spawnPoint = spawnPoints->at(rand() % spawnPoints->size());

	Enemy* enemy = new Enemy("enemy.png", spawnPoint["x"].asInt()+32, spawnPoint["y"].asInt()+32, 64, area);

	enemy->addPathfinding(area);


	enemy->chooseAction(area->posToTileCoord(Point(enemy->getPositionX(), enemy->getPositionY())));

	enemies.pushBack(enemy);

	return enemy;
}

void EnemyManager::decide(Vec2 playerPos, Area* area)
{
	for (auto &enemy : enemies)
	{
		if (enemy->lineOfSight(playerPos))
		{
			enemy->setTargetTile(playerPos, area->posToTileCoord(playerPos));
			enemy->chooseAction(area->posToTileCoord(enemy->getPosition()));
			
		}

	}
}

void EnemyManager::checkCollisions(Area* area, float dv)
{
	/*for (int i = 0; i < enemies.size(); i++)
	{
		if (!area->checkCollision(Point(enemies.at(i)->getPositionX(), enemies.at(i)->getPositionX())))
		{
			enemies.at(i)->move(dv);
		}
		else {
			enemies.at(i)->changeDirection();
			enemies.at(i)->move(dv);
		}
	}*/
}

void EnemyManager::moving(Area* area, float dv)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->walkPath(area);
		enemies.at(i)->gridMove(dv);
		//enemies.at(i)->move(dv);
	}
}

Vector<Enemy*> EnemyManager::getEnemies()
{
	return enemies;
}