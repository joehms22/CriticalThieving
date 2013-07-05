/**
This file part of "Critical Thieving"
Copyright 2013 - Ali AlMarhoon, Dylan Bohlender, Joseph Lewis


This scene shows the user instructions on how to play.

==CHANGELOG==
2013-05-31 - Initial Creation: Joseph
**/

#include "InstructionsScene.h"
#include "GameScene.h"
USING_NS_CC;

CCScene* InstructionsScene::scene()
{
	// Scene and layer are part of the GC system, no need to delete them later
    CCScene *scene = CCScene::create();
    
    InstructionsScene *layer = InstructionsScene::create();
    scene->addChild(layer);

    return scene;
}

bool InstructionsScene::init()
{
	// Init super first.
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // move us to the first slide.
    _instruction_position = -1;
    
    // create all of our slides.
    
    addInstruction("instructions1.png");
    addInstruction("instructions2.png");
    addInstruction("instructions3.png");
    addInstruction("instructions4.png");
    addInstruction("instructions5.png");
	addInstruction("instructions6.png");
    addInstruction("instructions7.png");
    addInstruction("instructions8.png");
    

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
   
   	// Create + add the global instructions background 
   	CCSprite* instructionCard = CCSprite::create("instructions_bg.png");
	instructionCard->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(instructionCard, 0);
    
    nextInstruction();
    registerWithTouchDispatcher(); // enable touches
    
    return true;
}


// Shows an instruction.
void InstructionsScene::nextInstruction()
{
	
	_instruction_position++;
	
	// Clean up the last instruction
    if(_instruction_position >= 1)
    {
    	this->removeChild(_instruction_titles[_instruction_position - 1], true);
    }

	if(_instruction_position >= _instruction_titles.size())
	{
		// move on to the next scene
		CCScene* game = GameScene::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, game));
		
		return;
	}
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	// show the next instruction
	CCSprite* instructionCard = _instruction_titles[_instruction_position];
	
	instructionCard->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	
	
    // add the sprite as a child to this layer
    this->addChild(instructionCard);
}

void InstructionsScene::addInstruction(const char* tile)
{
	CCSprite* sprite = CCSprite::create(tile);
	sprite->retain(); // Don't kill this!
	_instruction_titles.push_back(sprite);
}

void InstructionsScene::onEnter()
{
	CCNode::onEnter();
}

void InstructionsScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool InstructionsScene::ccTouchBegan(CCTouch* touch, CCEvent *event)
{
    return true;
}

void InstructionsScene::ccTouchEnded(CCTouch* touch, CCEvent *event)
{
	nextInstruction();
}
