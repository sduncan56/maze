

#include "Enemy.h"

Enemy::Enemy(std::string filename, int X, int Y, int sqSize, Area* a) : AnimSprite(filename, X, Y, sqSize, a)
{
	targetAcquired = false;
}

Enemy::~Enemy()
{
	
}

void Enemy::chooseAction(Point tilePos)
{
	if (targetAcquired)
	{
		path = pathfinding->search(tilePos, targetTile);
	}
	else {
		path = pathfinding->search(tilePos, pathfinding->findRandWalkableNode());
	}
}

bool Enemy::checkIfPointReached(Point targetPoint)
{
	if (getPositionX() > targetPoint.x - 10 && getPositionX() < targetPoint.x + 10)
	{
		if (getPositionY() > targetPoint.y - 10 && getPositionY() < targetPoint.y + 10)
		{
			path.pop_back();
			return true;
		}
	}
	return false;
}


void Enemy::walkPath(Area* area)
{
	if (moving) return;
	if (path.size() == 0)
	{
		velX = 0;
		velY = 0;
		targetAcquired = false;
		chooseAction(area->posToTileCoord(Point(getPositionX(), getPositionY())));
		return;
	}
	
	targetTile = path.back();
	Point tilePos = area->posToTileCoord(getPosition());
	
	/*Point targetPoint = area->tileToPosCoord(targetTile);

	if (checkIfPointReached(targetPoint))
	{
		walkPath(area);
		return;
	}*/

	if (targetTile == tilePos)
	{
		path.pop_back();
		walkPath(area);
		return;
	}


	if (tilePos.x > targetTile.x)
	{
		setMoveInputs(-1, 0);
		//velX = speed;
	}
	else if (tilePos.x < targetTile.x)
	{
		setMoveInputs(1, 0);
		//velX = -speed;
	}
	if (tilePos.y > targetTile.y)
	{
		setMoveInputs(0, 1);
		//velY = speed;
	}
	else if (tilePos.y < targetTile.y)
	{
		setMoveInputs(0, -1);
		//velY = -speed;
	}

	
}

void Enemy::changeDirection()
{
	setXVel(speed);
	setYVel(speed);

	Point dir = chooseDirection();

	velX *= dir.x;
	velY *= dir.y;
}

int Enemy::checkSign(int num)
{
	if (num < 0) return -1;
	if (num > 0) return 1;
	return 0;
}

Point Enemy::chooseDirection()
{
	int dir = rand() % 2;

	Point direction = Point();
	if (dir == 0)
	{
		int sign = checkSign(velX);
		sign *= -1;
		direction.x = sign;
		direction.y = checkSign(velY);
	}
	else if (dir == 1)
	{
		int sign = checkSign(velY);
		sign *= 1;
		direction.y = sign;
		direction.x = checkSign(velX);
	}

	return direction;


	//return rand() % 4 + (-1);
}

bool Enemy::setTargetTile(Point mPos, Point tTile)
{
	if (pathfinding->checkWalkable(area->posToTileCoord(mPos)))
	{
		targetTile = tTile;
		targetAcquired = true;
		return true;
	}
	return false;
}
