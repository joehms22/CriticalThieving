/**
This file part of Critical Thieving

Copyright 2013 - Joseph Lewis
**/

#include <map>
#include <string>

#include "Action.h"
#include "SimpleAudioEngine.h"


static std::map<Sprite*, std::vector<Action*> > _sprites;

Action::Action(Sprite* owner, CharacterProperties* properties, char* name)
:_owner(owner), _props(properties), _name(name)
{
	_sprites[owner].push_back(this);
	
	printf("Adding action to owner\n");
}

// Returns a human-readable name for the action
char* Action::getName()
{
	std::string n = _owner->getName();
	n += ": ";
	n +=  _name;
	return (char*)n.c_str();

}

// Completes the action for the given sprite.
void Action::act(Sprite* s)
{
	s->apply(*_props);
}

// Returns the effect of this action
CharacterProperties* Action::getProperties()
{
	return _props;
}


void Action::getActions(Sprite* owner, Sprite* actor, std::vector<Action*>& actions)
{
	if(owner == actor)
	{
		return;
	}
	
	std::vector<Action*> these = _sprites[owner];
	
	//printf("actions from %s on %s are %ld\n", actor->getName(), owner->getName(), these.size());
	
	for(int i = 0; i < these.size(); i++)
	{
		if(these[i]->canTakeAction(*actor))
		{
			actions.push_back(these[i]);
		}
	}
}


void Action::play_sound(const char* soundfile_name)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundfile_name);    
}


void Action::display_bubble(Sprite* actor, const char* bubble_filename)
{
	actor->setBubble(bubble_filename);
}
