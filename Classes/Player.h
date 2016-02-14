#pragma once

#include "AnimSprite.h"
#include "EventHandler.h"


USING_NS_CC;


class Player:public AnimSprite
{
private:


public:
	Player(std::string filename, int X, int Y, int sqSize, Area* a);
	~Player();

	void input(EventHandler *eventhandler);
};

