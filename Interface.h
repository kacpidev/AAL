/****************************************************
*	Author: Kacper Domañski
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
****************************************************/
#ifndef _INTERFACE_
#define _INTERFACE_

#include <string>
#include <map>
#include "MessageHandler.h"

class Interface
{
public:
	Interface()
	{
	};
	~Interface()
	{
	};

	//Constructor with input params
	Interface(int argc, char *argv[]);

	void configureParameters();

	void printHelp();
	void printUsage();
	void printParams();

	std::string getStringParameter(const std::string key);
	bool getBoolParameter(const std::string key);

private:
	int _argCount{ 0 };

	std::map <std::string, std::pair<bool, std::string>> mapParamBools;
	std::map <std::string, std::pair<std::string, std::string>> mapParamStrings;

};


#endif