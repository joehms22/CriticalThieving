/**
This file part of Critical Thieving

Copyright 2013 - Ali AlMarhoon | Dylan Bohlender | Joseph Lewis
**/

#include "Blackboard.h"
#include "Sprite.h"
#include "Action.h"
#include "cocos2d.h"
#include <vector>
#include <list>
#include "AStar.h"

#ifndef SIMULATION_H
#define SIMULATION_H


class Simulation
{
	public:
		// Returns a pointer to the global blackboard for the current simualtion
		virtual Blackboard* getGlobalBlackboard() = 0;
		
		// Populates the given vector with all sprites on the map.
		virtual void getAllSprites(std::vector<Sprite*>& toPopulate) = 0;
		
		// Populates the given vector with all sprites that are "near" to the
		// given one.
		void getNearSprites(Sprite* me, std::vector<Sprite*>& toPopulate);
		
		// Gets all possible actions for the given sprite.
		void getAvailableActions(Sprite* me, std::vector<Action*>& toPopulate);
		
		// Gets all possible actions that you can do to the given sprites
		void getAvailableActions(Sprite* me, std::vector<Sprite*>& other, std::vector<Action*>& toPopulate);
		
		// Returns the world variable.
		virtual cocos2d::CCTMXTiledMap* getWorld() = 0;
		
		// Fills the supplied vector with any sprites that are touching the given one
		void getTouchingSprite(Sprite* me, std::vector<Sprite*> &toPopulate);
		
		// Returns a path from the given point to the second one, if this is not 
		// possible, nothing will be appended to waypoints.
		void getPath(cocos2d::CCPoint from, cocos2d::CCPoint to, std::list<cocos2d::CCPoint*> &waypoints);
};

#endif
