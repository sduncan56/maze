
#pragma once

#include "AnimSprite.h"

class Enemy: public AnimSprite
{
private:
	std::vector<Point> path;
	Point targetTile;
	bool targetAcquired;

public:
	Enemy(std::string filename, int X, int Y, int sqSize, Area* a);
	~Enemy();
	void chooseAction(Point tilePos);
	bool checkIfPointReached(Point targetPoint);
	void walkPath(Area* area);
	void changeDirection();
	int checkSign(int num);
	Point chooseDirection();

	bool setTargetTile(Point mPos, Point tTile);
};