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
	std::cout << "~~Help~~\n";
	std::cout << std::left;
	std::cout << "AAL_Kacper_Domanski - Segment grouping\n\n";
	std::cout << "Program detecting colliding segments groups";
	std::cout << "With use of GLFW shows different groups of colliding segments in different colors\n\n";
	std::cout << "Algorithm types: \n";
	std::cout << "  - DS - Deep Search - recursive approch \n";
	std::cout << "  - WS - Wide Search - each with each check \n\n";
	std::cout << "Arrangment types: \n";
	std::cout << "  - NO - all segments in one container \n";
	std::cout << "  - SH - SpatialHash - space divided to 100 tiles segments assigned to tiles in which they belong \n\n";
	std::cout << "Use   --usage   parameter to check available options.\n";
}


void Interface::printUsage()
{
	std::cout << " >> Usage:\n";
	std::cout << std::left;
	std::cout << " -h | --help : Prints useful information about program.\n";
	std::cout << " -u | --usage : Prints message with possible input parameters.\n";
	std::cout << " -f | --file[filename] : Input file with information about segments.\n";
	std::cout << " -o | --output[filename]  : Output file to be created with program results.\n";
	std::cout << " --generate-tests [numberOfSegments] : Forces program to generate its own tests in given number.\n";
	std::cout << " --algorithm [WS | DS]" << " : Specifies which arrange algorithm to use (default WS).\n";
	std::cout << " --arrangment [NO | SH]" << " : Specifies which sorting heuristic to use (default NO).\n";
}