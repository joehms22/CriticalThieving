#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include <vector>
#include "cocos2d.h"
#include "Sprite.h"
#include "Simulation.h"
#include "CharacterProperties.h"
#include "HUD.h"

class GameScene : public cocos2d::CCLayer, public Simulation
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    void onEnter();
    
    void setViewpointCenter(cocos2d::CCPoint point);
    virtual void update(float dt);
    
    virtual cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    
    CC_SYNTHESIZE(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _background, Background);
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _meta, Meta);
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _foreground, Foreground);

	
	
	// Must be implemented from Simulation.h
	Blackboard* getGlobalBlackboard();	
	void getAllSprites(std::vector<Sprite*>& toPopulate);
	cocos2d::CCTMXTiledMap* getWorld();
	

    CC_SYNTHESIZE(int, _numCollected, numCollected);

private:
	std::vector<Sprite*> sprites;
	Blackboard* _global_blackboard;
	CharacterProperties* _universalTurnProperties;
};

#endif
