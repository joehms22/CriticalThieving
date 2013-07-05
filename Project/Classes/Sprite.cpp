/**
This file part of Critical Thieving

Copyright 2013 - Ali AlMarhoon | Dylan Bohlender | Joseph Lewis
**/

#include <cstdio>
#include <algorithm>    // std::sort

#include "cocos2d.h"
#include "Sprite.h"
#include "AStar.h"
#include "Action.h"
#include "ActionMenu.h"

//#define DEBUGGING

Sprite::Sprite(char* spriteTileName, const char* name, Simulation* myWorld)
:_name(name), _simulation(myWorld)
{
	_sprite = cocos2d::CCSprite::create(spriteTileName);
	_blackboard = new Blackboard();
	printf("Sprite: Created sprite with name: %s\n", name);
	_path_action = NULL;
	setValue(full, 100);
    setValue(rich, 20);
    setValue(moral, 40);
	
	_lastLocation = new cocos2d::CCPoint(_sprite->getPosition());
}

// Returns the name of this character.
const char* Sprite::getName()
{
	return _name;
}

void Sprite::setBubble(const char* bubblepath)
{
	printf("showing bubble\n");
	if(_bubble != NULL)
	{
		_sprite->removeChild(_bubble, true);
	}
	
	_updates_since_bubble = 0;
	_bubble = cocos2d::CCSprite::create(bubblepath);
	_bubble->setPosition(ccp(128, 128));
	_sprite->addChild(_bubble);
}

// Returns the sprite's blackboard
Blackboard* Sprite::getBlackboard()
{
	return _blackboard;
}


Simulation* Sprite::getSimulation()
{
	return _simulation;
}

cocos2d::CCSprite* Sprite::getSprite()
{
	return _sprite;
}

class ActionSort
{
	public:
		Sprite* sp;
		bool operator()(Action* const &a, Action* const &b) { 
			return sp->utility(*(a->getProperties())) > sp->utility(*(b->getProperties()));
		}
};

void Sprite::sortActionsByUtility(std::vector<Action*> &actions)
{
	ActionSort as;
	as.sp = this;
	
	std::sort(actions.begin(), actions.end(), as);
}

void Sprite::moveTo(cocos2d::CCPoint& point)
{
 	_lastLocation->x = _sprite->getPosition().x;
 	_lastLocation->y = _sprite->getPosition().y;
	_sprite->setPosition(point);
	_sprite->setDirty(true);
}

bool Sprite::moveTowardsDest()
{
	if(_path_action == NULL && _path.size() == 0)
	{
		return false; // we aren't headed anywhere.
	}

	if(_path.size() == 0) // do the action
	{
		printf("Acting\n");
		_path_action->act(this);
		_path_action = NULL;
	}
	else // follow the path
	{
		moveTo(*_path.front());
		
		_path.pop_front();
	}
	
	return true;
}

void Sprite::setDesiredAction(Action* act)
{
	if(act == NULL)
	{
		std::vector<Action*> myPossibleActions;
		getSimulation()->getAvailableActions(this, myPossibleActions);
	
		sortActionsByUtility(myPossibleActions);
		_path_action = myPossibleActions[0];
		
#ifdef DEBUGGING
		for(int i = 0; i < myPossibleActions.size(); ++i)
		{
			float util = utility(*(myPossibleActions[i]->getProperties()));
			printf("%s with utility %f\n", myPossibleActions[i]->getName(),util); 
		}
#endif
		

	}
	else
	{	
		_path_action = act;
	}
	
	getSimulation()->getPath(this->getPosition(), _path_action->getPosition(), _path);
	//printf("%s planning action %s\n", getName(), _path_action->getName());
	
}

////////////////////////////////////////////////////////////////////////////////
// Extra sprite classes can go here to provide common behaviors to them.
////////////////////////////////////////////////////////////////////////////////

void NullSprite::update()
{
	// do nothing
}



void CharacterSprite::update()
{
	
	if(_path.size() != 0 && rand() % 30 == 0)
	{	
		for(int i = 0; i < 25; i++)
		{
			cocos2d::CCPoint* point = new cocos2d::CCPoint(getPosition().x, getPosition().y);
			_path.push_front(point);
		}
	}
	
	// if we are moving towards our destination
	if(moveTowardsDest())
		return;
		
	setDesiredAction(NULL); // find the best possible action for us and do it
}

void PlayerSprite::update()
{
	static bool hasMoved = false;
	// tell the world which sprite we are.
	getSimulation()->getGlobalBlackboard()->setSprite("PLAYER", this);

	getSimulation()->getGlobalBlackboard()->setNumber("Player Hunger", value(full));
	getSimulation()->getGlobalBlackboard()->setNumber("Player Morality", value(moral));
	getSimulation()->getGlobalBlackboard()->setNumber("Player Wealth", value(rich));
	
	Action* desiredAction = getSimulation()->getGlobalBlackboard()->getAction("PLAYER_DESIRED_ACTION", NULL);
	if(desiredAction != NULL)
	{
		desiredAction->act(this);
		getSimulation()->getGlobalBlackboard()->setAction("PLAYER_DESIRED_ACTION", NULL);
	}

	// Check to see if there has been a new request for moving
	float seekX = getSimulation()->getGlobalBlackboard()->getNumber("Player Seek X", -1);
	float seekY = getSimulation()->getGlobalBlackboard()->getNumber("Player Seek Y", -1);
	if(seekX != -1 && seekY != -1)
	{
		// clear the preexisting list
		_path.clear();
	
		cocos2d::CCPoint point(seekX, seekY);
		
		_path_action = NULL;
		getSimulation()->getPath(this->getPosition(), point, _path);
		
		// set back to global number
		getSimulation()->getGlobalBlackboard()->setNumber("Player Seek X", -1);
		getSimulation()->getGlobalBlackboard()->setNumber("Player Seek Y", -1);
	}
	
	// Move towards the desired location
	if(moveTowardsDest())
	{
		hasMoved = true;
		return;
	}
	
	
	if(hasMoved)
	{
		hasMoved = false;
	
	
		// ask player for action if we are in the same space as a character.
		std::vector<Sprite*> touchingSprites;
		getSimulation()->getTouchingSprite(this, touchingSprites);
	
		if(touchingSprites.size() > 0)
		{
			std::vector<Action*> myPossibleActions;

			getSimulation()->getAvailableActions(this, touchingSprites, myPossibleActions);
		
			ActionMenu::getInstance()->requestAction(myPossibleActions, "PLAYER_DESIRED_ACTION");
		}
	}
}		
