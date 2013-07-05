/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This scene shows the user instructions on how to play.

==CHANGELOG==
2013-05-31 - Initial Creation: Joseph
**/

#include <vector>
#include "cocos2d.h"

#ifndef INSTRUCTIONS_SCENE_H
#define INSTRUCTIONS_SCENE_H

class InstructionsScene : public cocos2d::CCLayer
{
	public:
		CREATE_FUNC(InstructionsScene);
		virtual bool init();
		static cocos2d::CCScene* scene();
		
		void nextInstruction();
		void onEnter(); // MUST be overridden for touch events to work
		
		virtual void registerWithTouchDispatcher();
		virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent *event);
		virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent *event);
	
	private:
		std::vector<cocos2d::CCSprite*> _instruction_titles;
		int _instruction_position;
		void addInstruction(const char* tile);
};

#endif
