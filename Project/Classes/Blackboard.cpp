/**
This file part of Critical Thieving

Copyright 2013 - Joseph Lewis <joehms22@gmail.com>
**/
#include "Blackboard.h"
#include <stdexcept>

float Blackboard::getNumber(std::string key, float default_number)
{
	try
	{
		return _numbers.at(key);
	}
	catch (const std::out_of_range& oor) 
	{
	}
	
	return default_number;
}

void Blackboard::setNumber(std::string key, float value)
{
	_numbers[key] = value;
}


std::string Blackboard::getString(std::string key, std::string default_string)
{
	try
	{
		return _strings.at(key);
	}
	catch (const std::out_of_range& oor) 
	{
	}
	
	return default_string;
}

void Blackboard::setString(std::string key, std::string value)
{
	_strings[key] = value;
}

bool Blackboard::getBool(std::string key, bool default_value)
{
	try
	{
		return _booleans.at(key);
	}
	catch (const std::out_of_range& oor) 
	{
	}
	
	return default_value;
}

void Blackboard::setBool(std::string key, bool value)
{
	_booleans[key] = value;
}

Sprite* Blackboard::getSprite(std::string key, Sprite* default_value)
{
	try
	{
		return _sprites.at(key);
	}
	catch (const std::out_of_range& oor) 
	{
	}
	
	return default_value;
}
void Blackboard::setSprite(std::string key, Sprite* value)
{
	_sprites[key] = value;
}

Action* Blackboard::getAction(std::string key, Action* default_value)
{
	try
	{
		return _actions.at(key);
	}
	catch (const std::out_of_range& oor) 
	{
	}
	
	return default_value;
}
void Blackboard::setAction(std::string key, Action* value)
{
	_actions[key] = value;
}


// Resets the blackboard to being new.
void Blackboard::clearBlackboard()
{
	_numbers.clear();
	_strings.clear();
	_booleans.clear();
	_sprites.clear();
	_actions.clear();
}

// Returns the Global Blackoard, after creating it if necessary.
Blackboard* Blackboard::getGlobalInstance()
{
	static Blackboard* bb = NULL;
	if(bb == NULL)
	{
		bb = new Blackboard();
	}
	return bb;
}
