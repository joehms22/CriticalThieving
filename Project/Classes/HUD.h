/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This layer shows the user current relevant information.

==CHANGELOG==
2013-05-31 - Initial Implementation - Joseph
**/


#include "cocos2d.h"
#include "Blackboard.h"

#ifndef HUD_H
#define HUD_H

class HUD : public cocos2d::CCLayer
{
	public:
		virtual bool init();
		void DrawHUD();
		void OnMenu(CCObject* pSender);
		void updateValues(Blackboard* bb);
		
		static HUD* getInstance();
		

		CREATE_FUNC(HUD);
	private:
		cocos2d::CCLabelTTF *scoreLabel, *moralityLabel, *hungerLabel, *timeLabel;

};

#endif
