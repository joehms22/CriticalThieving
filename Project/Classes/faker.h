/**
This file part of Critical Thieving,

the idea was taken from Perl's faker library.

Copyright 2013 - Ali AlMarhoon | Dylan Bohlender | Joseph Lewis
**/

#ifndef FAKER_H
#define FAKER_H

#include <string>
#include <vector>



class Faker
{
	public:
		/**
		 * Creates a random human name
		 */
		static const char* humanName();
		
		/**
		 *	Creates a randomized company name, made of last names and 
		 * 	company suffixes.
		 * 
		 * 	companyName() -> Koss LLC.
		 **/
		static const char* companyName();
		
		/**
		 * Creates a company name with the given type in it, e.g.
		 * 
		 * companyName("Trash") -> "Profound Trash Inc."
		 */
		static const char* companyName(std::string name);
		
		/**
		 * Creates a job title consisting of a job descriptor, title, and name
		 * 
		 * jobTitle() -> Corporate Integration Liason
		 **/
		static const char* jobTitle();
};
#endif
