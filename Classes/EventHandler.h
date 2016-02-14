#pragma once

#include "cocos2d.h"
#include <map>

class EventHandler
{
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

public:
	EventHandler();
	cocos2d::EventListenerKeyboard* initKeyboard();
	~EventHandler();

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

};

