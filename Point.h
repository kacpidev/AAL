/****************************************************
*	Author: Kacper Domañski
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
****************************************************/
#ifndef _POINT_
#define _POINT_

class Point
{
public:
	Point() { };
	Point(int x, int y) : x(x), y(y) {};

	/*
	Orientation of ordered triplet (p, q, r)
	Returns:
	0 - p,q,r - colinear
	1 - Clockwise
	2 - counterclockwies
	*/
	static int pointOrientation(Point p, Point q, Point r); 

	int x{ 0 };
	int y{ 0 };
};

#endif