/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This scene shows the game over title.

==CHANGELOG==
2013-05-31 - Initial Creation: Joseph
**/

#include "GameOverScene.h"
#include "GameScene.h"
USING_NS_CC;

CCScene* GameOverScene::scene()
{
	// Scene and layer are part of the GC system, no need to delete them later
    CCScene *scene = CCScene::create();
    
    GameOverScene *layer = GameOverScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameOverScene::init()
{
	// Init super first.
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
   
   	// Create + add the global instructions background 
   	CCSprite* instructionCard = CCSprite::create("game_over3.png");
	instructionCard->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(instructionCard, 0);
    
    registerWithTouchDispatcher(); // enable touches
    
    return true;
}

void GameOverScene::onEnter()
{
	CCNode::onEnter();
}

void GameOverScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameOverScene::ccTouchBegan(CCTouch* touch, CCEvent *event)
{
    return true;
}

void GameOverScene::ccTouchEnded(CCTouch* touch, CCEvent *event)
{
	// move back to the game scene
	CCScene* game = GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, game));
}
