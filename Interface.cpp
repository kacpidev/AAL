#include "Interface.h"

Interface::Interface(int argc, char* argv[]) : _argCount(argc)
{
	configureParameters();

	for (int i = 1; i < _argCount; ++i)
	{
		std::string parameter(argv[i]);
	
		if (mapParamBools.find(parameter) != mapParamBools.end() && mapParamBools[parameter].first != true)
		{
			mapParamBools[parameter].first = mapParamBools[mapParamBools[parameter].second].first = true;
		}
		else if (mapParamStrings.find(parameter) != mapParamStrings.end() &&
						 i + 1 < _argCount &&
						 mapParamStrings[parameter].first == "")
		{
			std::string filename(argv[i + 1]);
			mapParamStrings[parameter].first = mapParamStrings[mapParamStrings[parameter].second].first = filename;
			i++; 
			continue;
		}
		else
		{
			mapParamBools["--usage"].first = true;
			mapParamBools["-u"].first = true;
			break;
		}
	}
}

void Interface::configureParameters()
{

	mapParamBools["--usage"] = std::make_pair(false, "-u");
	mapParamBools["--help"] = std::make_pair(false, "-h");
	mapParamBools["-u"] = std::make_pair(false, "--usage");
	mapParamBools["-h"] = std::make_pair(false, "--help");

	mapParamStrings["--file"] = std::make_pair("", "-f");
	mapParamStrings["--output"] = std::make_pair("", "-o");
	mapParamStrings["-f"] = std::make_pair("", "--file");
	mapParamStrings["-o"] = std::make_pair("", "--output");
	mapParamStrings["--generate-tests"] = std::make_pair("", "--generate-tests");
	mapParamStrings["--algorithm"] = std::make_pair("", "--algorithm");
	mapParamStrings["--arrangment"] = std::make_pair("", "--arrangment");
}

std::string Interface::getStringParameter(const std::string key)
{
	if (mapParamStrings.find(key) != mapParamStrings.end())
	{
		return mapParamStrings[key].first;
	}
	else
	{
		return "";
	}
}

bool Interface::getBoolParameter(const std::string key)
{
	if (mapParamBools.find(key) != mapParamBools.end())
	{
		return mapParamBools[key].first;
	}
	else
	{
		MessageHandler::printMessage("Wrong parameter requested, false returned: ", MessageHandler::WARNING);
		return false;
	}
}

void Interface::printHelp()
{

}


void Interface::printUsage()
{

}