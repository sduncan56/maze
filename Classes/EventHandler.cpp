#include "EventHandler.h"

USING_NS_CC;

EventHandler::EventHandler()
{



}


EventHandler::~EventHandler()
{
}

EventListenerKeyboard* EventHandler::initKeyboard()
{
	auto eventListener = EventListenerKeyboard::create();

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
		if (keys.find(keyCode) == keys.end()){
			keys[keyCode] = true;
		}
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
		keys.erase(keyCode);
	};

	return eventListener;

}

bool EventHandler::isKeyPressed(EventKeyboard::KeyCode code)
{
	if (keys.find(code) != keys.end())
		return true;
	return false;
}

