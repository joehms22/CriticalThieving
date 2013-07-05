/**
This file part of Critical Thieving

Copyright 2013 - Ali AlMarhoon | Dylan Bohlender | Joseph Lewis
**/

#include "CharacterProperties.h"

void CharacterProperties::apply(CharacterProperties& other)
{
	for(int i = 0; i < NUM_TRAITS; ++i)
	{
		properties[i] += other.properties[i];
		
		if(properties[i] > MAX_TRAIT_VALUE)
		{
			properties[i] = MAX_TRAIT_VALUE;
		}
		
		if(properties[i] < MIN_TRAIT_VALUE)
		{
			properties[i] = MIN_TRAIT_VALUE;
		}	
	}
}

// calculates the utility of applying hte other properties to this one
float CharacterProperties::utility(CharacterProperties& other)
{
	float total = 0.0;
	for(int i = 0; i < NUM_TRAITS; ++i)
	{
		int value = properties[i] + other.properties[i];
		if(value > MAX_TRAIT_VALUE)
		{
			value = MAX_TRAIT_VALUE;
		}
		
		if(value < MIN_TRAIT_VALUE)
		{
			value = MIN_TRAIT_VALUE;
		}	
		
		total += value * DEFAULT_UTILITIES[i];
	}
	
	return total;
}


// for each property, add it's utility to the total and return that.
float CharacterProperties::utility()
{
	float total = 0.0;
	for(int i = 0; i < NUM_TRAITS; ++i)
	{
		total += DEFAULT_UTILITIES[i] * properties[i];
	}
	
	return total;
}

bool CharacterProperties::is(Property p)
{
	return properties[p] > CUTOFF_POINTS[p];
}

// Returns the value of the given property
// may want to use this for things like currency.
float CharacterProperties::value(Property p)
{
	return properties[p];
}

// Sets the value of the given property to a specific value, note that
// this should only be used while instantiating the CharacterProperties
// list.
void CharacterProperties::setValue(Property p, float value)
{
	properties[p] = value;
}
