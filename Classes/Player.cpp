#include "Player.h"


Player::Player(std::string filename, int X, int Y, int sqSize, Area* a) : AnimSprite(filename, X, Y, sqSize, a)
{

}

Player::~Player()
{
}



void Player::input(EventHandler *eventhandler)
{
	if (moving) return;
	if (eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_A) || eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		if (checkDirection(-1, 0)) 
			setMoveInputs(-1, 0);
		//setXVel(-getSpeed());
	}
	else if (eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_D) || eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		//setXVel(getSpeed());
		if (checkDirection(1, 0))
			setMoveInputs(1, 0);
	}
	if ((!eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_A) && !eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
		&& (!eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_D) && !eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))) {
		//setXVel(0);
	}

	if (eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_W) || eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
		//setYVel(getSpeed());
		if (checkDirection(0, 1))
			setMoveInputs(0, 1);
	}
	else if (eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_S) || eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
		//setYVel(-getSpeed());
		if (checkDirection(0, -1))
			setMoveInputs(0, -1);
	}
	if (!eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_W) && !eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) 
		&& !eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_S) && !eventhandler->isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
		//setYVel(0);
	}
}




