#!/usr/bin/env python
# coding=utf-8
'''
Generates all actions based upon the actions csv file.
'''

def toClassName(colname):
	return colname.replace(' ', '')

all_actions = []


def format_preconditions(precondition_list):
	return " && ".join(["({})".format(p) for p in precondition_list])

def format_onrun(onrunlist):
	return "\n\t\t\t\t".join(["{};".format(r) for r in onrunlist])

with open("actions.csv") as actions:

	lines = actions.read().split("\n")
	colname = lines[0].split('\t')
	coltypes = lines[1].split('\t')
	
	
	for line in lines[2:]:
		thisobj = {'name':"", 'precondition':[], 'properties':[], 'onRun':[]}
		
		for index, value in enumerate(line.split('\t')):
			field_type = coltypes[index]
			if field_type == 'name':
				thisobj[field_type] = value
			else:
				if value == "FALSE":
					value = 'false'
				if value == "TRUE":
					value = 'true'
				if value == "":
					continue
				
				try:
					thisobj[field_type].append(colname[index].format(value))
				except IndexError:
					pass # this field has no value
		
		
		thisobj['precondition'] = format_preconditions(thisobj['precondition'])
		thisobj['onRun'] = format_onrun(thisobj['onRun'])
		thisobj['properties'] = format_onrun(thisobj['properties'])
		
		if len(thisobj['precondition']) == 0:
			thisobj['precondition'] = "true"
		thisobj['classname'] = toClassName(thisobj['name'])
		all_actions.append( u"""
	class {classname} : public Action
	{{
		public:
			{classname}(Sprite* owner)
			:Action(owner, NULL, "{name}")
			{{
				_props = new CharacterProperties();
				{properties}
			}}
			
			bool canTakeAction(Sprite& actor)
			{{
				return {precondition};
			}}
			
			void act(Sprite* actor)
			{{
				actor->apply(*_props);
				{onRun}
			}}
	}};
""".format(**thisobj))

'''
	for line in lines:
		cols = line.split(',')
		
		preconditions = []
		properties = []
		post_actions = []
		
		# skip lines without a name
		if cols[0].strip() == "":
			continue
		
		for index, value in enumerate(cols):
			
			value = value.lower().strip()
			value_property = property_name[index]
			
			#ignore blank cols
			if value == "":
				continue
			
			# generate the way to determine if a character can do something
			if coltype[index] == "precondition":
				if value == "true":
					preconditions.append("s.is({})".format(value_property))
				elif value == "false":
					preconditions.append("(! s.is({}))".format(value_property))
				else:
					preconditions.append("(s.value({}) {})".format(value_property, value))
			
			elif coltype[index] == "property":
				properties.append("_props->setValue({}, {});".format(value_property, value))
					
			
		# get ready to pretty print these things
		properties = "\n\t\t\t\t".join(properties)
		
		
		action_section = ""
		if len(preconditions) > 0:
			action_section = """bool canTakeAction(Sprite& actor)
			{{
				return {preconditions};
			}}""".format(preconditions=" && ".join(preconditions))

		all_actions.append( """
	class {classname} : public Action
	{{
		public:
			{classname}(Sprite* owner)
			:Action(owner, NULL, "{human}")
			{{
				_props = new CharacterProperties();
				{props}
			}}
			
			{action}
	}};
""".format(classname=toClassName(cols[0]), human=cols[0], props = properties, action = action_section))
		
'''	
with open("../AllActions.h", 'w') as out:
	out.write(u"""
/**
This file is part of Critical Thieving. Copyright 2013 - Joseph Lewis

DO NOT EDIT THIS FILE MANUALLY, IT IS AUTO GENERATED BY generate_all_actions.py
INSTEAD, EDIT actions.csv AND RE-RUN generate_all_actions.py

**/

#ifndef ALL_ACTIONS_H
#define ALL_ACTIONS_H
#include "Action.h"
#include "CharacterProperties.h"

namespace SpriteActions
{{
{actions}
}}
#endif

""".format(actions = u"\n".join(all_actions)))
