/**
This file part of Critical Thieving

Copyright 2013 - Ali AlMarhoon | Dylan Bohlender | Joseph Lewis
**/

#include "Blackboard.h"
#include "CharacterProperties.h"

#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

class Task
{
	public:
		virtual bool run(long frame_number, Blackboard* global_bb, Blackboard* player_bb, CharacterProperties* char_props); // true success, false on failure 
}

// Returns true
class Success : public Task
{
	public:
		virtual bool run(long frame_number, Blackboard* global_bb, Blackboard* player_bb, CharacterProperties* char_props) override
		{
			return true;
		}
}

// Returns false
class Failure : public Task
{
	public:
		virtual bool run(long frame_number, Blackboard* global_bb, Blackboard* player_bb, CharacterProperties* char_props) override
		{
			return false;
		}
}

class PlanPath : public Task
{
	public:
		virtual bool run(long frame_number, Blackboard* global_bb, Blackboard* player_bb, CharacterProperties* char_props) override;
}

class ContinuePath : public Task
{
	public:
		virtual bool run(long frame_number, Blackboard* global_bb, Blackboard* player_bb, CharacterProperties* char_props) override;
}

#endif
