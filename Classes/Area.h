

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Area
{
private:
	TMXTiledMap* tilemap;
	TMXObjectGroup* spawnlayer;
	TMXObjectGroup* interactlayer;
	TMXLayer* meta;

public:
	Area();
	~Area();
	TMXTiledMap* loadMap(std::string filename);

	bool checkColTile(Point position);
	bool checkCollision(Point position);

	ValueMap getSpawnPoint(std::string pointName);


	Point posToTileCoord(Point position);
	Point tileToPosCoord(Point tilePos);

	Vec2 getSize();
};