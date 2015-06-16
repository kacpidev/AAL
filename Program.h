#ifndef _PROGRAM_
#define _PROGRAM_

#include <iostream>
#include "Interface.h"
#include "Collection.h"
#include "Utilities.h"
#include "CollisionDetector.h"
#include <GL/glut.h>

/*
	Main project class, i/o managment and collision detection
*/

class Program
{
public:
	Program()
	{
	};
	~Program()
	{
	};

	//Contructs program with inputs parameters
	Program(int argc, char *argv[]);
	
	Collection getCollection() { return _collection; };

	//Program operations
	void run();
private:
	Interface _interface;
	Collection _collection;
	CollisionDetector _collisionDetector;
};

#endif