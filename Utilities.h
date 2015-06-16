#ifndef UTILITIES
#define UTILITIES

#include <sstream>
#include <string>
#include <ctime>
#include <iostream>
#include "MessageHandler.h"
#include "Point.h"

class Utilities
{
public:
	static clock_t begin, end;

	static void timeStart();
	static float timeStop();

	static Point windowSize;

	// Converts given argument from std::string to Type
	template <typename Type>
	static Type convertFromString(const std::string value);
	
	/*
		Replace file keyword with proper data
		keyword - Keyword in file to be found and replaced.
		value - String to be inserted instead of the given keyword.
		text - Reference to text, in which the replacement is done.
	*/
	static void replaceKeyword(const std::string keyword, std::string value, std::string & text);
};


template <typename Type>
inline Type Utilities::convertFromString(const std::string value)
{
	std::stringstream ss;
	ss.str(value);
	Type conversion;
	ss >> conversion;
	return conversion;
}

#endif