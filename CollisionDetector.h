#ifndef _COLLISION_DETECTOR_
#define _COLLISION_DETECTOR_

#include <vector>
#include <map>
#include "Segment.h"
#include "MessageHandler.h"
#include "Utilities.h"

class CollisionDetector
{
public:
	enum AlgorithmType
	{
		DS,		//Deep Search
		WS		//Wide Searcg
	};

	enum ArrangmentType
	{
		NO,		//QuadTree
		SH		//SpatialHash
	};

	int colorsCount{ 0 };

	typedef std::vector<Segment *> Segments;
	typedef std::vector<Segments> SegmentGroups;

	CollisionDetector() { };	
	~CollisionDetector();

	CollisionDetector(Segments segments, AlgorithmType algorithmType, ArrangmentType arrangmentType);

	void arrange();

	void drawAll();

	AlgorithmType getAlgorithmType();

	ArrangmentType getArrangmentType();

	float getTime();

	void setAlgorithmType(AlgorithmType algorithmType) { _algorithmType = algorithmType; };
	void setArrangmentType(ArrangmentType arrangmentType) { _arrangmentType = arrangmentType; };
	
private:
	void sort();
	void detectCollisions();
	void recalculateGroups();
	void checkDeep(Segment *segment, Segments segmentsGroup);
	void checkWide(Segment *segment, Segments segmentsGroup);

	float _time = 0.f;

	AlgorithmType _algorithmType;
	ArrangmentType _arrangmentType;

	Segments _segments; //all segments

	SegmentGroups _segmentGroupsTemp; //segments separated by regionsroups
	SegmentGroups _segmentGroupsFinal; //segments separated  in divided groups
	std::map<int, std::vector<int>> _matchingColors;
};

#endif