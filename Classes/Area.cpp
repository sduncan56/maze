
#include "Area.h"

Area::Area()
{

}

Area::~Area()
{
	delete spawnlayer;
	delete meta;
}

TMXTiledMap* Area::loadMap(std::string filename)
{
	tilemap = TMXTiledMap::create(filename);
	spawnlayer = tilemap->objectGroupNamed("spawnlayer");
	interactlayer = tilemap->objectGroupNamed("interactlayer");
	meta = tilemap->layerNamed("meta");
	meta->setVisible(false);
	return tilemap;
}

bool Area::checkColTile(Point tileCoord)
{
	int tileGid = meta->getTileGIDAt(tileCoord);
	if (tileGid) {
		Value properties = tilemap->getPropertiesForGID(tileGid);

		auto collision = properties.asValueMap()["Collidable"];
		if (collision.asString() == "True") {
			return true;
		}
	}
	return false;
}

bool Area::checkCollision(Point position)
{
	Point tileCoord = posToTileCoord(position);

	return checkColTile(tileCoord);
}

ValueMap Area::getSpawnPoint(std::string pointName)
{
	return spawnlayer->getObject(pointName);
}

Point Area::posToTileCoord(Point position)
{
	int x = position.x / tilemap->getTileSize().width;
	int y = ((tilemap->getMapSize().height*tilemap->getTileSize().height) - position.y) / tilemap->getTileSize().height;
	return Point(x, y);
}

Point Area::tileToPosCoord(Point tilePos)
{
	int x = tilePos.x*tilemap->getTileSize().width;
	int y = tilemap->getMapSize().height*tilemap->getTileSize().height - (tilePos.y*tilemap->getTileSize().height);
	return Point(x, y);
}

Vec2 Area::getSize()
{
	return tilemap->getMapSize();
}