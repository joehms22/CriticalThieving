/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This scene shows the game win title.

==CHANGELOG==
2013-05-31 - Initial Creation: Joseph
**/

#include "GameWinScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

CCScene* GameWinScene::scene()
{
	// Scene and layer are part of the GC system, no need to delete them later
    CCScene *scene = CCScene::create();
    
    GameWinScene *layer = GameWinScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameWinScene::init()
{
	// Init super first.
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
   
   	// Create + add the global instructions background 
   	CCSprite* instructionCard = CCSprite::create("win_game2.png");
	instructionCard->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(instructionCard, 0);
    
    registerWithTouchDispatcher(); // enable touches
    
    return true;
}

void GameWinScene::onEnter()
{
	CCNode::onEnter();
}

void GameWinScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameWinScene::ccTouchBegan(CCTouch* touch, CCEvent *event)
{
    return true;
}

void GameWinScene::ccTouchEnded(CCTouch* touch, CCEvent *event)
{
	// move back to the game scene
	CCScene* game = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, game));
}
