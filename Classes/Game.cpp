#include "Game.h"



Scene* Game::createScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();

	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	area = new Area();
	addChild(area->loadMap("map2.tmx"), 0, "cave");

	ValueMap spawnPoint = area->getSpawnPoint("PlayerSpawnPoint");


	player = new Player("player.png", spawnPoint["x"].asInt()+32, spawnPoint["y"].asInt()+32, 64, area);
	player->addPathfinding(area);
	//player->setAnchorPoint(Point(0, 0));

	this->addChild(player, 0);

	eventhandler = new EventHandler();

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventhandler->initKeyboard(), this);

	enemyManager = new EnemyManager();

	enemyManager->addSpawnPoint(area->getSpawnPoint("EnemySpawnPoint1"));
	enemyManager->addSpawnPoint(area->getSpawnPoint("EnemySpawnPoint2"));

	addChild(enemyManager->spawnAtRandPoint(area));

	Size size = Director::sharedDirector()->getVisibleSize();

	float playfield_width = area->getSize().x*64;
	float playfield_height = area->getSize().x * 64;

	this->runAction(Follow::create(player, Rect(0, 0, playfield_width, playfield_height)));

	schedule(schedule_selector(Game::update));

	collisions = Collisions();

	return true;
}


void Game::update(float delta)
{
	player->input(eventhandler);

	player->update(delta);

	/*if (!area->checkCollision(Point(player->getPositionX(), player->getPositionY()))) {
		player->move(delta);
	}
	else {
		player->moveBack();
	}*/

	enemyManager->decide(player->getPosition(), area);
	enemyManager->moving(area, delta);
	enemyManager->checkCollisions(area, delta);

	if (collisions.checkUnitCollisions(area, player, enemyManager))
	{
		gameOver();
	}

}

void Game::gameOver()
{
	auto goLabel = Label::createWithSystemFont("Game Over", "Arial", 40);
	auto winSize = Director::sharedDirector()->getWinSizeInPixels();
	goLabel->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(goLabel);
}