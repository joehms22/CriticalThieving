/**
This file part of Critical Thieving

Copyright 2013 - Ali AlMarhoon | Dylan Bohlender | Joseph Lewis
**/

#include <vector>
#include <string>

#include "cocos2d.h"
#include "CharacterProperties.h"
#include "Blackboard.h"

#ifndef SPRITE_H
#define SPRITE_H

class Simulation;
class Action;

/**
 * Represents a sprite in the world.
**/
class Sprite : public CharacterProperties
{
	private:
		cocos2d::CCSprite *_sprite;
		const char* _name;
		Blackboard *_blackboard;
		Simulation *_simulation;
		cocos2d::CCPoint *_lastLocation;
		cocos2d::CCSprite *_bubble;
		int _updates_since_bubble;
	
	protected:
		// Sorts the given list of actions from most utility to least
		void sortActionsByUtility(std::vector<Action*> &actions);
		
		// moves the character to the given point.
		void moveTo(cocos2d::CCPoint& point);
		
		// Sets the action the player wants to do next and the path to get there
		// if the action is NULL, chooses the best of all possible actions
		void setDesiredAction(Action* act);
		
		/**
		Makes a move towards the next point or does the action at the end 
		of a character's path.
		
		If there is no action to take, or the move is now done, returns false,
		otherwise returns true.
		**/
		bool moveTowardsDest();
		
		// Stores the path that the character should follow along to get to 
		// their destination.
		std::list<cocos2d::CCPoint*> _path;
		
		// the action the player is going to take when they get to their 
		// destination.
		Action* _path_action;
		
		
		
	
	public:
		// Creates a new character with the given characteristics
		Sprite(char* spriteTileName, const char* name, Simulation* myWorld);
		
		// TODO add destructor so we don't leak memory
		
		// Returns the name of this character.
		const char* getName();
		
		// Called to update the given sprite, by default does nothing.
		virtual void update()=0;
		
		// Returns the sprite's blackboard
		Blackboard* getBlackboard();
		
		// Returns the simulation this sprite belongs to.
		Simulation* getSimulation();
		
		// Returns the sprite of this character.
		cocos2d::CCSprite* getSprite();
		
		inline
		const cocos2d::CCPoint& getPosition()
		{
			return _sprite->getPosition();
		};
		
		
		void setBubble(const char* bubblepath);
};

// does nothing but sit there
class NullSprite : public Sprite
{
	public:
		NullSprite(char* spriteTileName, const char* name, Simulation* global_blackboard)
		:Sprite(spriteTileName, name, global_blackboard)
		{};
		
		virtual void update();
};

// normal character behavior
class CharacterSprite : public Sprite
{
	public:
		CharacterSprite(char* spriteTileName, const char* name, Simulation* global_blackboard)
		:Sprite(spriteTileName, name, global_blackboard)
		{};
		virtual void update();
};

// player behavior
class PlayerSprite : public Sprite
{
	public:
		PlayerSprite(char* spriteTileName, const char* name, Simulation* global_blackboard)
		:Sprite(spriteTileName, name, global_blackboard)
		{};
		virtual void update();
};

#include "Simulation.h"
#include "Action.h"

#endif
