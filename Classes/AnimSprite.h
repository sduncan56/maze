
#pragma once

#include "cocos2d.h"

#include "Pathfinding.h"
#include "Area.h"
#include <math.h>

USING_NS_CC;


class AnimSprite : public cocos2d::Sprite
{
protected:
	int velX, velY;
	int speed;

	float dist;
	bool moving;
	int xDir, yDir;
	int goalX, goalY;

	Point prevPosition;

	Pathfinding* pathfinding;

	int squareSize;

	Area* area;


public:
	AnimSprite(std::string filename, int X, int Y, int sqSize, Area* a);
	~AnimSprite();

	//pixel-based movement - don't use.
	void move(float dt);
	void moveBack();

	//tile based movement
	float updateDist(int dir, float dist, float pos, float oldPos);
	void gridMove(float dt);
	void setMoveInputs(int xDir, int yDir);
	bool checkDirection(int dX, int dY);

	Point convertToTileCoords(Point mapCoords);

	void addPathfinding(Area *area);
	bool lineOfSight(Point target);

	void update(float dt);

	void setXVel(int vel);
	void setYVel(int vel);

	int getSpeed();
};