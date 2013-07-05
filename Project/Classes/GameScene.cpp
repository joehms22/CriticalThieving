#include "GameScene.h"
#include "AllSprites.h"
#include "HUD.h"
#include "GameWinScene.h"
#include "GameOverScene.h"
#include "ActionMenu.h"
#include <cmath>

#include "SimpleAudioEngine.h"
USING_NS_CC;


CCScene* GameScene::scene()
{
	CCScene *scene = CCScene::create();
	
	GameScene *layer = GameScene::create();
	scene->addChild(layer, 1);
	
	HUD* _hud = HUD::getInstance();
	scene->addChild(_hud, 5);
	
	ActionMenu* _am = ActionMenu::getInstance();
	scene->addChild(_am, 10);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	_tileMap = CCTMXTiledMap::tiledMapWithTMXFile("world.tmx");
	_tileMap->retain();
	
	this->addChild(_tileMap);
	
	// start us updating
	this->scheduleUpdate();
	
	// Create global gamestate here
	_global_blackboard = Blackboard::getGlobalInstance();
	
	// Set up all sprites here
	Sprites::createCharacters(sprites, this);
	
	for(unsigned int i = 0; i < sprites.size(); i++)
	{
		this->addChild(sprites[i]->getSprite());
	}
    
    registerWithTouchDispatcher();
	
	_universalTurnProperties = new CharacterProperties();
	_universalTurnProperties->setValue(full, -.1);

	_global_blackboard->setNumber("Time", 300);
	_global_blackboard->setNumber("Score", 0);
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backgroundloop.mp3", true);    
	
	return true;
}

void GameScene::onEnter()
{
	CCNode::onEnter();
}


// Is it me or does this seem like a God method? 
// It should probably be broken up.
int frame = 0;
void GameScene::update(float dt)
{
	frame++;
	// limit our computation
	if(frame % 5 != 0)
	{
		return;
	}
	
	float time = _global_blackboard->getNumber("Time", 0);
	float score = _global_blackboard->getNumber("Player Wealth", 0);
	
	// check for endgames
	if (score >= 100)
	{
		cocos2d::CCScene* nextScene = GameWinScene::scene();
		cocos2d::CCDirector::sharedDirector()->replaceScene(nextScene);
		return;
	
	}
	if (time <= 0)
	{
		cocos2d::CCScene* nextScene = GameOverScene::scene();
		cocos2d::CCDirector::sharedDirector()->replaceScene(nextScene);
		return;
	}
	
	// update all sprites in the game
	for(unsigned int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->apply(*_universalTurnProperties);
		sprites[i]->update();
	}
	
	HUD::getInstance()->updateValues(_global_blackboard);
	
	// set the viewport to scroll to the player
	Sprite* p = _global_blackboard->getSprite("PLAYER", NULL);
	if(p != NULL)
	{
		setViewpointCenter(p->getSprite()->getPosition());
	}
	
	_global_blackboard->setNumber("Time", time - .5);
}

// Taken from:
// https://github.com/clawoo/TileBasedGameCocos2D-x/blob/master/Classes/HelloWorldScene.cpp
void GameScene::setViewpointCenter(CCPoint position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width/2);
	x = MIN(x, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);

	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);

	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);

	this->setPosition(viewPoint);
}

// Methods from Simulation.h
Blackboard* GameScene::getGlobalBlackboard()
{
	return _global_blackboard;
}

void GameScene::getAllSprites(std::vector<Sprite*>& toPopulate)
{
	for(int i = 0; i < sprites.size(); ++i)
	{
		toPopulate.push_back(sprites[i]);
	}
}

CCTMXTiledMap* GameScene::getWorld()
{
	return _tileMap;	
}



CCPoint GameScene::tileCoordForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return CCPoint(x, y);
}

#pragma mark - handle touches
void GameScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameScene::ccTouchBegan(CCTouch* touch, CCEvent *event)
{
    return true;
}

void GameScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{	
    CCPoint touchLocation = touch->locationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation = convertToNodeSpace(touchLocation);
    
    _global_blackboard->setNumber("Player Seek X", touchLocation.x);
	_global_blackboard->setNumber("Player Seek Y", touchLocation.y);
}

