/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This scene shows the game over title.

==CHANGELOG==
2013-05-31 - Initial Creation: Joseph
**/

#include <vector>
#include "cocos2d.h"

#ifndef GAMEOVER_SCENE_H
#define GAMVOVER_SCENE_H

class GameOverScene : public cocos2d::CCLayer
{
	public:
		CREATE_FUNC(GameOverScene);
		virtual bool init();
		static cocos2d::CCScene* scene();
		
		void onEnter(); // MUST be overridden for touch events to work
		
		virtual void registerWithTouchDispatcher();
		virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent *event);
		virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent *event);
	
	private:
};

#endif
