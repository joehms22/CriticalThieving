/**
This file part of Critical Thieving

Copyright 2013 - Ali AlMarhoon | Dylan Bohlender | Joseph Lewis
**/

#ifndef CHARACTER_PROPERTIES_H
#define CHARACTER_PROPERTIES_H


const int MAX_TRAIT_VALUE = 100;
const int MIN_TRAIT_VALUE = 0;

//const int NUM_TRAITS = 8;
const int NUM_TRAITS = 3;

//we changed the number of properties to three to simplify the game, but left the other ones commented out

enum Property { 
    full = 0, // hungry->full
    rich, // poor->rich
    moral, // immoral->moral
    //safe, // unsafe->safe
    //content, // anger->content
    //charitable, // scrooge->charitable
    //awake, // sleepy->awake
    //respected // not_respected->respected
};

// The utilites of Properties is determined roughly by Maslow's heirarchy of 
// needs, so NPCs should act semi-"rationally" (for people)
// These utilities will be multiplied by the real vaue of the trait to determine
// actual utility of a state.
//const float DEFAULT_UTILITIES [] = {1.0, 0.6, 0.1, 0.4, 0.4, 0.1, 0.7, 0.6};
const float DEFAULT_UTILITIES [] = {1.0, 0.6, 0.1};

// Points over wich the character is a property, e.g. 50 for full would mean
// if the full property > 50, the character is full.
// These are total BS values, so you may want to change them later if charcters
// are seen constantly trying to fufill certain needs or are choosing the 
// wrong paths in a tree.
//const int CUTOFF_POINTS [] = {20, 70, 60, 60, 50, 20, 60, 90};
const int CUTOFF_POINTS [] = {20, 70, 60};

/**
 * Represents the properties for a character
**/
class CharacterProperties
{
	public:
		CharacterProperties()
		{
			for(int i = 0; i < NUM_TRAITS; i++)
			{
				properties[i] = 0.0;
			}
		}
	
		// Adds the given properties to this one's
		void apply(CharacterProperties& other);
		
		// Calculates the utility of the current state
		// Note that you should *not* simply calculate utilities in actions,
		// because that may not be the utilitiy that is actually recieved
		// when it is applied to a character.
		float utility(CharacterProperties& other);
		
		// Calculates the current utility of this properties.
		float utility();
		
		// Returns true if the given property is greater than the threshold
		bool is(Property p);
		
		// Returns the value of the given property
		// may want to use this for things like currency.
		float value(Property p);
		
		// Sets the value of the given property to a specific value, note that
		// this should only be used while instantiating the CharacterProperties
		// list.
		void setValue(Property p, float value);
	
	private:
		float properties[NUM_TRAITS];
};

#endif
