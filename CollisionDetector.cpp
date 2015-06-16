#include "CollisionDetector.h"

CollisionDetector::CollisionDetector(Segments segments, AlgorithmType algorithmType, ArrangmentType arrangmentType) :
_segments(segments), _algorithmType(algorithmType), _arrangmentType(arrangmentType) { };

void CollisionDetector::arrange()
{
	MessageHandler::printMessage("Sorting segments", MessageHandler::INFO);
	Utilities::timeStart();

	sort();
	MessageHandler::printMessage(std::to_string(Utilities::timeStop()), MessageHandler::TIME);

	MessageHandler::printMessage("Finding colliding segments", MessageHandler::INFO);
	Utilities::timeStart();

	detectCollisions();
	
	MessageHandler::printMessage(std::to_string(Utilities::timeStop()), MessageHandler::TIME);

	//MessageHandler::printMessage("Creating groups", MessageHandler::INFO);
	//Utilities::timeStart();

	//createGroups();
	//
	//MessageHandler::printMessage(std::to_string(Utilities::timeStop()), MessageHandler::TIME);

	MessageHandler::printMessage("Created " + std::to_string(colorsCount) + " groups", MessageHandler::INFO);

	_time = Utilities::timeStop();

}

CollisionDetector::~CollisionDetector()
{
	for each(auto segment in _segments)
	{
		delete(segment);
	}
}

void CollisionDetector::sort()
{
	Point cellSize(Utilities::windowSize.x / 10, Utilities::windowSize.y / 10);
	
	// WORKAROUND

	if (_arrangmentType == ArrangmentType::NO)
	{
		for each (auto segment in _segments)
		{		
			_segmentGroupsTemp.push_back(std::vector<Segment*>());
			_segmentGroupsTemp[0].push_back(segment);
		}
	}
	else // SH
	{
		Point cellsCount(Utilities::windowSize.x / cellSize.x, Utilities::windowSize.y / cellSize.y);

		if (Utilities::windowSize.x % cellSize.x != 0)
		{
			cellsCount.x += 1;
		}

		if (Utilities::windowSize.y % cellSize.y != 0)
		{
			cellsCount.y += 1;
		}

		for (int i = 0; i < cellsCount.x; ++i)
		{
			for (int j = 0; j < cellsCount.y; ++j)
			{
				_segmentGroupsTemp.push_back(std::vector<Segment*>());
				
				for each (auto segment in _segments)
				{
					if (segment->isIntersecting(Point(i*cellSize.x, j* cellSize.y), Point((i + 1)*cellSize.x, (j + 1)*cellSize.y)))
					{
						_segmentGroupsTemp[i*cellsCount.y + j].push_back(segment);
					}
				}
			}
		}
	}
}

void CollisionDetector::detectCollisions()
{
	for each (auto segmentGroup in _segmentGroupsTemp)
	{
		for each (auto segment in segmentGroup)
		{
			if (segment->color == 0)
			{
				segment->color = ++colorsCount;
			}

			if (_algorithmType == AlgorithmType::DS)
			{
				this->checkDeep(segment, segmentGroup);
			}
			else //WS
			{
				this->checkWide(segment, segmentGroup);
			}
		}
	}
}

void CollisionDetector::checkDeep(Segment* segment, Segments segmentGroup)
{

	for each (auto other in segmentGroup)
	{
		if (other->color != segment->color)
		{
			if (segment->isIntersecting(*other))
			{
				if (other->color == 0)
				{
					other->color = segment->color;
					if (other != nullptr)
					{
						this->checkDeep(other, segmentGroup);
					}
				}
				else
				{
					if (_matchingColors.find(other->color) != _matchingColors.end())
					{
						bool alreadyMatched = false;
						for each(auto i in _matchingColors[other->color])
						{
							if (i == segment->color)
							{
								alreadyMatched = true;
								_matchingColors[other->color].push_back(segment->color);
								break;
							}
						}
					}
					else if (_matchingColors.find(segment->color) != _matchingColors.end())
					{
						bool alreadyMatched = false;
						for each(auto i in _matchingColors[segment->color])
						{
							if (i == other->color)
							{
								alreadyMatched = true;
								_matchingColors[segment->color].push_back(other->color);
								break;
							}
						}
					}
					else
					{
						_matchingColors[segment->color].push_back(other->color);
					}
				}
			}
		}
	}
}

void CollisionDetector::checkWide(Segment* segment, Segments segmentGroup)
{
	for each (auto other in segmentGroup)
	{
		if (other->color != segment->color)
		{
			if (segment->isIntersecting(*other))
			{
				if (other->color == 0)
				{
					other->color = segment->color;
				}
				else
				{
					if (_matchingColors.find(other->color) != _matchingColors.end())
					{
						bool alreadyMatched = false;
						for each(auto i in _matchingColors[other->color])
						{
							if (i == segment->color)
							{
								alreadyMatched = true;
								_matchingColors[other->color].push_back(segment->color);
								break;
							}
						}
					}
					else if (_matchingColors.find(segment->color) != _matchingColors.end())
					{
						bool alreadyMatched = false;
						for each(auto i in _matchingColors[segment->color])
						{
							if (i == other->color)
							{
								alreadyMatched = true;
								_matchingColors[segment->color].push_back(other->color);
								break;
							}
						}
					}
					else
					{
						_matchingColors[segment->color].push_back(other->color);
					}
				}
			}
		}
	}
}

void CollisionDetector::recalculateGroups()
{
	int deletedGroups{ 0 };

	for each(auto segment in _segments)
	{
		for each(auto colorGroup in _matchingColors)
		{

		}
	}
	colorsCount -= deletedGroups;
}