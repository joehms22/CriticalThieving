/**
This file part of Critical Thieving

Copyright 2013 - Joseph Lewis <joehms22@gmail.com>

==CHANGELOG==
2013-06-01 - Added clear and getGlobalInstance methods. Added actions.
**/

#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include <map>
#include <string>

class Action;
class Sprite;

class Blackboard
{
	public:
		// Gets a number from the blackboard.
		float getNumber(std::string key, float default_number);
		void setNumber(std::string key, float value);
	
		// Gets a string from the blackboard
		std::string getString(std::string key, std::string default_string);
		void setString(std::string key, std::string value);
		
		// Gets a boolean from the blackboard.
		bool getBool(std::string key, bool default_value);
		void setBool(std::string key, bool value);
		
		Sprite* getSprite(std::string key, Sprite* defaultValue);
		void setSprite(std::string key, Sprite* value);
		
		Action* getAction(std::string key, Action* defaultValue);
		void setAction(std::string key, Action* value);
		
		// Resets the blackboard to being new.
		void clearBlackboard();
		
		// Returns the Global Blackoard, after creating it if necessary.
		static Blackboard* getGlobalInstance();
	
	private:
		std::map<std::string, float> _numbers;
		std::map<std::string, std::string> _strings;
		std::map<std::string, bool> _booleans;
		std::map<std::string, Sprite*> _sprites;
		std::map<std::string, Action*> _actions;
};


#include "Sprite.h"
#include "Action.h"

#endif
