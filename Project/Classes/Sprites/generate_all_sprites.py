#!/usr/bin/env python

'''
Generates all actions based upon the actions csv file.
'''



all_sprites = []
all_classnames = []


def toClassName(colname):
	return colname.replace(' ', '')

def toSpriteClass(colname):
	'''Converts a behavior tree name we give to the name of a sprite class'''
	return "".join([c[0].upper() + c[1:] for c in colname.strip().split(' ')]) + "Sprite"
	

with open("sprites.csv") as sprites:
	
	lines = sprites.read().split("\n")
	coltype = lines[0].split(',')
	lines = lines[1:]
	

	
	for line in lines:
		cols = line.split(',')
		actions = []
		human_name = "<auto>"
		tree = ""
		classname = ""
		x = "0"
		y = "0"
		costume = "thief.png"
		
		# skip lines without a name
		if cols[0].strip() == "":
			continue
		
		for index, value in enumerate(cols):
			
			value = value.strip()
			
			
			# generate the way to determine if a character can do something
			if coltype[index] == "action":
				if len(value) != 0:
					actions.append("new SpriteActions::{}(this);".format(value))
			elif coltype[index] == "name":
				classname = toClassName(value)
			elif coltype[index] == "human name":
				if value == "<auto>":
					human_name = "Faker::humanName()"
				else:
					human_name = '"{}"'.format(value)
			
			# tells us which class we should extend.
			elif coltype[index] == "behavior tree":
				if len(value.strip()) == 0:
					value = "null"
				tree = toSpriteClass(value)
			elif coltype[index] == "x":
				x = value
			elif coltype[index] == "y":
				y = value
			elif coltype[index] == "costume":
				costume = value + ".png";
			
		# get ready to pretty print these things
		actions = "\n\t\t\t\t".join(actions)
		
		all_classnames.append(classname)
		all_sprites.append( """
	class {classname} : public {tree}
	{{
		public:
			// Creates a new character with the given characteristics
			{classname}(Simulation* world)
			:{tree}("{costume}", {human_name}, world)
			{{
				{actions}
				getSprite()->setPosition(ccp({x} * world->getWorld()->getTileSize().height, {y} * world->getWorld()->getTileSize().width));
			}}
	}};""".format(**locals()))
		

items = ["sprites.push_back(new {cls}(world));".format(cls=cls) for cls in all_classnames]
constructor = """
	/**
	 * Adds all characters in the level to the given vector after instantiating
	 * them with the given global blackboard.
	 */
	void createCharacters(std::vector<Sprite*> &sprites, Simulation* world)
	{{
		{items}
	}}
""".format(items="\n\t\t".join(items))
		
with open("../AllSprites.h", 'w') as out:
	out.write("""
/**
This file is part of Critical Thieving. Copyright 2013 - Joseph Lewis

DO NOT EDIT THIS FILE MANUALLY, IT IS AUTO GENERATED BY generate_all_sprites.py
INSTEAD, EDIT sprites.csv AND RE-RUN generate_all_sprites.py

**/

#ifndef ALL_SPRITES_H
#define ALL_SPRITES_H
#include "Sprite.h"
#include "Action.h"
#include "AllActions.h"
#include "CharacterProperties.h"
#include "faker.h"
#include "Simulation.h"

namespace Sprites
{{
const int TILE_WIDTH = 16; // tile width in points
{sprites}

{constructor}
}}
#endif

""".format(sprites = "\n".join(all_sprites), constructor=constructor))
