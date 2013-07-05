/**
This file part of Critical Thieving

Copyright 2013 - Ali AlMarhoon | Dylan Bohlender | Joseph Lewis
**/

#include <map>
#include <vector>
#include "Sprite.h"
#include "CharacterProperties.h"

#ifndef ACTION_H
#define ACTION_H

class Action
{
	public:
		Action(Sprite* o, CharacterProperties* properties, char* name);
		
		// Returns a human-readable name for the action
		char* getName();
		
		// Completes the action for the given sprite and applies these 
		// properties to it.
		virtual void act(Sprite* s)=0;
		
		// Returns the effect of this action
		CharacterProperties* getProperties();
		
		// Returns true if the given sprite can perform this action
		virtual bool canTakeAction(Sprite& s)=0;
		
		// Returns a list of sprites associated with the given owner.
		static void getActions(Sprite* owner, Sprite* actor, std::vector<Action*>& actions);

		// Gets the location of the owner (the thing you can do this action to).
		inline
		const cocos2d::CCPoint& getPosition()
		{
			return _owner->getPosition();
		};
		

	
	protected:
		Sprite* _owner;
		CharacterProperties* _props;
		char* _name;
		void play_sound(const char* soundfile_name);
		void display_bubble(Sprite*, const char* bubble_filename);
};

#endif
