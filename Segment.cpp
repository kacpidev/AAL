/****************************************************
*	Author: Kacper Domañski
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
****************************************************/
#include "Segment.h"

bool Segment::isIntersecting(Segment other)
{

	int o1 = Point::pointOrientation(startPoint, endPoint, other.startPoint);
	int o2 = Point::pointOrientation(startPoint, endPoint, other.endPoint);
	int o3 = Point::pointOrientation(other.startPoint, other.endPoint, startPoint);
	int o4 = Point::pointOrientation(other.startPoint, other.endPoint, endPoint);

	//General Case
	if (o1 != o2 && o3 != o4)
	{
		return true;
	}

	//Special cases
	if (o1 == 0 && isPointOnSegment(other.startPoint) ||
			o2 == 0 && isPointOnSegment(other.endPoint) ||
			o3 == 0 && other.isPointOnSegment(startPoint) ||
			o4 == 0 && other.isPointOnSegment(endPoint))
	{
		return true;
	}

	return false;
}

bool Segment::isInsideRect(Point leftDownCorner, Point rightTopCorner)
{
	//TODO - IMPROVE

	Point leftTopCorner = Point(leftDownCorner.x, rightTopCorner.y);
	Point rightDownCorner = Point(rightTopCorner.x, leftDownCorner.y);

	Segment leftSegment = Segment(leftDownCorner, leftTopCorner);
	Segment rightSegment = Segment(rightDownCorner, rightTopCorner);
	Segment topSegment = Segment(rightTopCorner, leftTopCorner);
	Segment downSegment = Segment(leftDownCorner, rightDownCorner);

	if (isIntersecting(leftSegment) ||
			isIntersecting(rightSegment) ||
			isIntersecting(topSegment) ||
			isIntersecting(downSegment) ||
			startPoint.x > leftDownCorner.x && startPoint.x < rightTopCorner.x && 
			startPoint.y > leftDownCorner.y && startPoint.y < rightTopCorner.y)
	{
		return true;
	}
	
	return false;
}


bool Segment::isPointOnSegment(Point other)
{
	if (other.x <= std::max(startPoint.x, endPoint.x) &&
			other.x >= std::min(startPoint.x, endPoint.x) &&
			other.y <= std::max(startPoint.y, endPoint.y) &&
			other.y >= std::min(startPoint.y, endPoint.y))
	{
		return true;
	}

	return false;
}