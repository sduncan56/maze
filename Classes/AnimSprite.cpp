

#include "AnimSprite.h"

AnimSprite::AnimSprite(std::string filename, int X, int Y, int sqSize, Area* a)
{
	velX = 0;
	velY = 0;

	speed = 80;

	initWithFile(filename);
	setPosition(X, Y);

	prevPosition = Point(X, Y);

	pathfinding = NULL;
	moving = false;

	dist = 0;
	xDir = yDir = 0;
	goalX = goalY = 0;

	squareSize = sqSize;
	area = a;
}

AnimSprite::~AnimSprite()
{
	delete pathfinding;
}

void AnimSprite::move(float dt)
{
	Vec2 pos = getPosition();

	prevPosition.set(pos.x, pos.y);

	pos.x += velX*dt;
	pos.y += velY*dt;

	setPosition(pos.x, pos.y);
}

void AnimSprite::moveBack()
{
	setPosition(prevPosition.x, prevPosition.y);
}

float AnimSprite::updateDist(int dir, float dist, float pos, float oldPos)
{
	if (dir > 0)
	{
		return dist -= (pos - oldPos);
	}
	else if (dir < 0)
	{
		return dist += (pos - oldPos);
	}

	return 0;
}

void AnimSprite::gridMove(float dt)
{
	Vec2 pos = getPosition();

	if (xDir != 0)
	{
		float oldX = getPositionX();
		
		pos.x += xDir * speed * dt;
		dist = updateDist(xDir, dist, pos.x, oldX);
	}
	if (yDir != 0)
	{
		float oldY = pos.y;
		pos.y += yDir * speed * dt;
		dist = updateDist(yDir, dist, pos.y, oldY);
	}

	if (dist <= 0)
	{
		dist = 0;
		moving = false;

		pos.x = goalX * squareSize + (squareSize/2); //last bit compensates for origin being in the middle
		pos.y = goalY * squareSize + (squareSize/2);
	}

	setPosition(pos);
}

void AnimSprite::setMoveInputs(int xD, int yD)
{
	int tX = floor(getPositionX() / squareSize);
	int tY = floor(getPositionY() / squareSize);

	xDir = xD;
	yDir = yD;

	goalX = tX + xDir;
	goalY = tY + yDir;

	dist = squareSize;

	moving = true;
}

bool AnimSprite::checkDirection(int dX, int dY)
{
	Point tileCoords = area->posToTileCoord(getPosition());
	return pathfinding->checkWalkable(Point(tileCoords.x + dX, tileCoords.y - dY));
	//return pathfinding->checkWalkable(Point(getPositionX() + dX*squareSize, getPositionY() + dY*squareSize));
}

void AnimSprite::addPathfinding(Area* area)
{
	pathfinding = new Pathfinding();
	pathfinding->initSSpace(area);
}


bool AnimSprite::lineOfSight(Point target)
{
	Vec2 pos = getPosition();

	Point tCoords = area->posToTileCoord(getPosition());
	Point targetTCoords = area->posToTileCoord(target);

	while (tCoords != targetTCoords)
	{
		if (targetTCoords.x > tCoords.x)
		{
			tCoords.x += 1;
		}
		else if (targetTCoords.x < tCoords.x)
		{
			tCoords.x -= 1;
		}
		if (targetTCoords.y > tCoords.y)
		{
			tCoords.y += 1;
		}
		else if (targetTCoords.y < tCoords.y)
		{
			tCoords.y -= 1;
		}

		if (!pathfinding->checkWalkable(tCoords))
		{
			return false;
		}
	}


	return true;
}

void AnimSprite::update(float dt)
{
	Point f = getPosition();
	if (moving)
	{
		gridMove(dt);
	}
}

void AnimSprite::setXVel(int vel)
{
	velX = vel;
}

void AnimSprite::setYVel(int vel)
{
	velY = vel;
}

int AnimSprite::getSpeed()
{
	return speed;
}