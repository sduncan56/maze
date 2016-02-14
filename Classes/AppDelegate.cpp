

#include "AppDelegate.h"
#include "Game.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("TESTING");
		glview->setFrameSize(800, 600);
		director->setOpenGLView(glview);

	}

	auto scene = Game::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {

}

void AppDelegate::applicationWillEnterForeground() {

}