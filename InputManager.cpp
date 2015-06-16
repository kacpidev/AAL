#include "InputManager.h"


bool InputManager::loadData(Collection::Segments & segments)
{
	std::ifstream inputFile;
	std::string content{ "" };
	std::stringstream ss;

	if (isDefaultPath)
	{
		_filename = DATA_FOLDER + _filename;
	}
	
	inputFile.open(_filename, std::ios::in);

	if (!inputFile.is_open())
	{
		MessageHandler::printMessage("Cannot open file: " + _filename, MessageHandler::ERR);
		return false;
	}

	while (std::getline(inputFile, content))
	{
		if (content[0] != '#')
		{
			Segment * segment = parseDataRow(content);
			if (segment != nullptr)
			{
				segments.push_back(segment);
			}
			else
			{
				MessageHandler::printMessage("Parsing row of data failed: nullptr returned", MessageHandler::ERR);
				return false;
			}
		}
		else
		{
			//LINE WITH COMMENT
		}
	}

	inputFile.close();
	
	return true;
}

Segment * InputManager::parseDataRow(const std::string & row)
{
	std::stringstream ss;
	ss.str(row);
	int x1, y1, x2, y2;
	Segment * segment = nullptr;

	try
	{
		ss >> x1 >> y1 >> x2 >> y2;
		segment = new Segment(Point(x1, y1), Point(x2, y2));
		return segment;
	}
	catch (...)
	{
		if (segment != nullptr)
		{
			delete segment;
		}
		return nullptr;
	}
	return nullptr;
}

void InputManager::setFilename(const std::string filename)
{
	_filename = filename;
	isDefaultPath = false;
}