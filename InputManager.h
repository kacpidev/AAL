/****************************************************
*	Author: Kacper Domañski
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
****************************************************/
#ifndef _INPUT_MANAGER_
#define _INPUT_MANAGER_

#define DATA_FOLDER "./data/"
#define DEFAULT_DATA_FILE "data.txt"

#include <string>
#include <fstream>
#include "Collection.h"


class InputManager
{
public:
	InputManager() : _filename(DEFAULT_DATA_FILE) { };
	~InputManager() { };

	InputManager(const std::string filename) : _filename(filename)
	{
		isDefaultPath = false;
	};

	bool loadData(Collection::Segments & segments);
	Segment * parseDataRow(const std::string & row);
	void setFilename(const std::string filename);

private:
	std::string _filename = "";
	bool isDefaultPath = true;
};

#endif