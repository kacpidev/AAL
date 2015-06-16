#include "MessageHandler.h"


void MessageHandler::printMessage(const std::string message, Type type)
{
	switch (type)
	{
	case ERR:
		std::cout << "\n[ ! ERROR ! ] : " << message << "\n";
		break;
	case WARNING:
		std::cout << "\n|| WARNING || : " << message << "\n";
		break;
	case INFO:
		std::cout << "\n  > > " << message << "\n";
		break;
	case TIME:
		std::cout << "\n~~~~TIME ELAPSED : " << message << "\n";
		break;
	default:
		break;
	}
}

void MessageHandler::printDebugSection(const std::string title, bool isBegin)
{
	if (isBegin)
	{
		std::cout << " ##################### Debug section: " << title << " ########## \n";
	}
	else
	{
		std::cout << " ##################### End of section ########## \n\n";
	}
}