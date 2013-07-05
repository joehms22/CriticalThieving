/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This layer shows the user current relevant information.

==CHANGELOG==
2013-05-31 - Initial Implementation - Joseph
**/


#include "HUD.h"
#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;

bool HUD::init()
{
	if(! CCLayer::init())
	{	
		return false;
	}
	
	bool bRet = false;
	this->setTouchEnabled(true);

	scoreLabel = cocos2d::CCLabelTTF::create("  $ 000.00", "Arial", 24);
	hungerLabel = cocos2d::CCLabelTTF::create("Hunger 000%", "Arial", 24);
	moralityLabel = cocos2d::CCLabelTTF::create("Morality 000%", "Arial", 24);
	timeLabel = cocos2d::CCLabelTTF::create("Time 000", "Arial", 24);

	cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	scoreLabel->setPosition(ccp(scoreLabel->getContentSize().width / 2,
							winSize.height - scoreLabel->getContentSize().height / 2));
	hungerLabel->setPosition(ccp(hungerLabel->getContentSize().width / 2,
							winSize.height - (scoreLabel->getContentSize().height) - hungerLabel->getContentSize().height / 2));
	moralityLabel->setPosition(ccp(moralityLabel->getContentSize().width / 2,
							winSize.height - (scoreLabel->getContentSize().height * 2) - (scoreLabel->getContentSize().height / 2)));
	timeLabel->setPosition(ccp(winSize.width-scoreLabel->getContentSize().width / 2,
	winSize.height - scoreLabel->getContentSize().height / 2));

	cocos2d::CCMenuItemImage* closebtn = cocos2d::CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HUD::OnMenu));
	cocos2d::CCSize closebtnSize = closebtn->getContentSize();

	cocos2d::CCMenu* closebtnMenu = cocos2d::CCMenu::create(closebtn, NULL);
	closebtnMenu->setPosition( ccp(winSize.width/2-closebtnSize.width/2, winSize.height - closebtnSize.height/2));

	// add this to the layer
	this->addChild(scoreLabel, 1);
	this->addChild(timeLabel, 1);
	this->addChild(hungerLabel, 1);
	this->addChild(moralityLabel, 1);
	this->addChild(closebtnMenu, 2);
	
	bRet = true;
	
	this->scheduleUpdate();
	
	return bRet;
}

void HUD::OnMenu(CCObject* pSender)
{
	cocos2d::CCScene* nextScene = HelloWorld::scene();
	cocos2d::CCDirector::sharedDirector()->replaceScene(nextScene);
} 

char scoreBuffer[100];
char timeBuffer[100];
char moralityBuffer[100];
char hungerBuffer[100];

void HUD::updateValues(Blackboard* bb)
{	
	sprintf(scoreBuffer, "  $ %03.0f.00", bb->getNumber("Player Wealth", -1));
	sprintf(timeBuffer, "Time %3.0f", bb->getNumber("Time", -1));
	sprintf(hungerBuffer, "Hunger %3.0f%%", bb->getNumber("Player Hunger", -1));
	sprintf(moralityBuffer, "Morality %3.0f%%", bb->getNumber("Player Morality", -1));

	scoreLabel->setString(scoreBuffer);
	moralityLabel->setString(moralityBuffer);
	hungerLabel->setString(hungerBuffer);
	timeLabel->setString(timeBuffer);
}


HUD* HUD::getInstance()
{
	static HUD* _instance = 0;
	if(_instance == 0)
	{
		_instance = HUD::create();
	}
	return _instance;	
}
