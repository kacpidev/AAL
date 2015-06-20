/****************************************************
*	Author: Kacper Domañski
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
****************************************************/
#ifndef _COLLECTION_
#define _COLLECTION_

#include <vector>
#include "Segment.h"
#include "CollisionDetector.h"

class Collection
{
public:
	
	typedef std::vector<Segment *> Segments;
	
	Collection(){};
	~Collection();

	void generateRandomData(unsigned long number, Point range);

	void setCollisionDetector(CollisionDetector * collisionDetector) { _collisionDetector = collisionDetector; };
	CollisionDetector * getCollisionDetector() { return _collisionDetector; };
	Segments getSegments() { return _segments; };
private:
	Segments _segments;
	CollisionDetector *_collisionDetector;
};

#endif 