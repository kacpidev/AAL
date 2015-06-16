#ifndef _MESSAGE_HANDLER_
#define _MESSAGE_HANDLER_

#include <string>
#include <iostream>
/*
	Pure static for displaying formatted messages. 
	Provides 4 types of messages - errors, warnings, and info
*/

class MessageHandler
{
public:
	//Message type
	enum Type
	{
		ERR,
		WARNING,
		INFO,
		UNKNOWN,
		TIME
	};

	//Prints message
	static void printMessage(const std::string message, Type type = Type::UNKNOWN);
	
	//Prints section indicator
	static void printDebugSection(const std::string title, bool isBegin);
};

#endif