#include "Simulation.h"


const char* GROUND_LAYER_NAME = "Meta";
const char* COLLIDE_PROPERTY_NAME = "Collidable";
const char* COLLIDE_PROPERTY_VALUE = "True";



void Simulation::getTouchingSprite(Sprite* me, std::vector<Sprite*> &toPopulate)
{
	cocos2d::CCSprite* toTest = me->getSprite();
	std::vector<Sprite*> nearbySprites;
	getNearSprites(me, nearbySprites);
	
	cocos2d::CCRect characterRect(
        toTest->getPosition().x - (toTest->getContentSize().width/2),
        toTest->getPosition().y - (toTest->getContentSize().height/2),
        toTest->getContentSize().width,
        toTest->getContentSize().height);
	
	// for each sprite, build a rectangle, and check if it intersects
	// with the original
	for(int i = 0; i < nearbySprites.size(); ++i)
	{
		toTest = nearbySprites[i]->getSprite();
		cocos2d::CCRect nearbyRect(
		    toTest->getPosition().x - (toTest->getContentSize().width/2),
		    toTest->getPosition().y - (toTest->getContentSize().height/2),
		    toTest->getContentSize().width,
		    toTest->getContentSize().height);
		
		if (characterRect.intersectsRect(nearbyRect))
		{
			toPopulate.push_back(nearbySprites[i]);
		}
	}
}


void Simulation::getNearSprites(Sprite* me, std::vector<Sprite*>& toPopulate)
{
	std::vector<Sprite*> sprites;
	getAllSprites(sprites);
	
	float myX = me->getSprite()->getPositionX();
	float myY = me->getSprite()->getPositionY();
	
	for(int i = 0; i < sprites.size(); ++i)
	{
		if(sprites[i] == me)
		{
			continue;
		}
		
		float otherX = sprites[i]->getSprite()->getPositionX();
		float otherY = sprites[i]->getSprite()->getPositionY();
		float distance = sqrt((myX - otherX) * (myX - otherX) + (myY - otherY) * (myY - otherY));
		
		//printf("Distance from: %s to %s is %f\n", me->getName(), sprites[i]->getName(), distance);
		toPopulate.push_back(sprites[i]);
	}
}

void Simulation::getAvailableActions(Sprite* me, std::vector<Action*>& toPopulate)
{
	std::vector<Sprite*> nearbyActors;
	getNearSprites(me, nearbyActors);
	getAvailableActions(me, nearbyActors, toPopulate);
}

void Simulation::getAvailableActions(Sprite* me, std::vector<Sprite*>& other, std::vector<Action*>& toPopulate)
{
	for(int i = 0; i < other.size(); i++)
	{
		Action::getActions(other[i], me, toPopulate);
	}
}


void Simulation::getPath(cocos2d::CCPoint from, cocos2d::CCPoint to, std::list<cocos2d::CCPoint*> &waypoints)
{
	AStar as(getWorld(), GROUND_LAYER_NAME, COLLIDE_PROPERTY_NAME, COLLIDE_PROPERTY_VALUE);
	as.getPath(from, to, waypoints);
}
