/****************************************************
*	Author: Kacper Domañski
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
****************************************************/
#ifndef _LINE_
#define _LINE_

#include "Point.h"
#include <algorithm>

class Segment
{
public:
	Segment(Point startPoint, Point endPoint) : startPoint(startPoint), endPoint(endPoint) { };
	
	bool isIntersecting(Segment other);
	bool isInsideRect(Point leftDownCorner, Point rightTopCorner);
	bool isPointOnSegment(Point other);
	//void draw();

	Point startPoint;
	Point endPoint;
	int color{ 0 };

};

#endif