/****************************************************
*	Author: Kacper Domañski
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
****************************************************/
#include "Collection.h"

Collection::~Collection()
{
	delete(_collisionDetector);
}

void Collection::generateRandomData(unsigned long number, Point range)
{

	for (unsigned long i = 0; i < number; ++i)
	{
		int randomValueX = range.x;
		int randomValueY = range.y;

		Point startPoint, endPoint;

		startPoint.x = rand() % randomValueX;
		startPoint.y = rand() % randomValueY;
		endPoint.x = rand() % randomValueX;
		endPoint.y = rand() % randomValueY;

		_segments.push_back(new Segment(startPoint, endPoint));
	}
}
