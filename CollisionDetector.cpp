/****************************************************
*	Author: Kacper Domañski
*	Contact: kacper.domanski@kacpidev.pl
*	Web: blog.kacpidev.pl
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
****************************************************/
#include "CollisionDetector.h"

CollisionDetector::CollisionDetector(Segments segments, AlgorithmType algorithmType, ArrangmentType arrangmentType) :
_segments(segments), _algorithmType(algorithmType), _arrangmentType(arrangmentType)
{
};

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

	MessageHandler::printMessage("Creating groups", MessageHandler::INFO);
	Utilities::timeStart();

	recalculateGroups();
	
	MessageHandler::printMessage(std::to_string(Utilities::timeStop()), MessageHandler::TIME);

	MessageHandler::printMessage("Created " + std::to_string(colorsCount) + " groups", MessageHandler::INFO);

	_time = Utilities::timeStop();

}

CollisionDetector::~CollisionDetector()
{
	for(auto segment : _segments)
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
		_segmentGroupsTemp.push_back(std::vector<Segment*>());

		for (auto segment : _segments)
		{
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

				for (auto segment : _segments)
				{
					if (segment->isInsideRect(Point(i*cellSize.x, j* cellSize.y), Point((i + 1)*cellSize.x, (j + 1)*cellSize.y)))
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
	for (auto segmentGroup : _segmentGroupsTemp)
	{
		for (auto segment : segmentGroup)
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
	for (auto other : segmentGroup)
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
					int lowerValue = std::min(segment->color, other->color);
					int higherValue = std::max(segment->color, other->color);
					std::pair<int, int> tempMatch = std::make_pair(lowerValue, higherValue);
					
					if (std::find(_matchingColorsTemp.begin(), _matchingColorsTemp.end(), tempMatch) == _matchingColorsTemp.end())
					{
						_matchingColorsTemp.push_back(tempMatch);
					}
				}
			}
		}
	}
}

void CollisionDetector::checkWide(Segment* segment, Segments segmentGroup)
{
	for (auto other : segmentGroup)
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
					int lowerValue = std::min(segment->color, other->color);
					int higherValue = std::max(segment->color, other->color);
					std::pair<int, int> tempMatch = std::make_pair(lowerValue, higherValue);

					if (std::find(_matchingColorsTemp.begin(), _matchingColorsTemp.end(), tempMatch) == _matchingColorsTemp.end())
					{
						_matchingColorsTemp.push_back(tempMatch);
					}
				}
			}
		}
	}
}

void CollisionDetector::recalculateGroups()
{
	int deletedGroups{ 0 };
	bool listUpdated = true;

	std::sort(_matchingColorsTemp.begin(), _matchingColorsTemp.end(), [](const std::pair<int, int> &left, const std::pair<int, int> &right)
	{
		return left < right;
	});

	while (_matchingColorsTemp.size() > 0)
	{
		std::vector<int> tempVec = std::vector<int>();

		tempVec.push_back(_matchingColorsTemp[0].first);
		tempVec.push_back(_matchingColorsTemp[0].second);
		deletedGroups++; 
		_matchingColorsTemp.erase(std::find(_matchingColorsTemp.begin(), _matchingColorsTemp.end(), _matchingColorsTemp[0]));

		while (listUpdated)
		{
			listUpdated = false;

			std::vector<std::pair<int, int>> tempMatchingColors = _matchingColorsTemp;
			
			for(auto tempMatch : tempMatchingColors)
			{
				if (tempVec.empty() != true)
				{
					if (std::find(tempVec.begin(), tempVec.end(), tempMatch.first) != tempVec.end())
					{
						if (std::find(tempVec.begin(), tempVec.end(), tempMatch.second) != tempVec.end())
						{
							_matchingColorsTemp.erase(std::find(_matchingColorsTemp.begin(), _matchingColorsTemp.end(), tempMatch));
						}
						else
						{
							tempVec.push_back(tempMatch.second);
							_matchingColorsTemp.erase(std::find(_matchingColorsTemp.begin(), _matchingColorsTemp.end(), tempMatch));
							deletedGroups++;
							listUpdated = true;
						}
					}
					else if (std::find(tempVec.begin(), tempVec.end(), tempMatch.second) != tempVec.end())
					{
						if (std::find(tempVec.begin(), tempVec.end(), tempMatch.first) != tempVec.end())
						{
							_matchingColorsTemp.erase(std::find(_matchingColorsTemp.begin(), _matchingColorsTemp.end(), tempMatch));
						}
						else
						{
							tempVec.push_back(tempMatch.first);
							_matchingColorsTemp.erase(std::find(_matchingColorsTemp.begin(), _matchingColorsTemp.end(), tempMatch));
							deletedGroups++;
							listUpdated = true;
						}
					}
				}
			}
			_matchingColors.back();
		}
		_matchingColors.push_back(tempVec);
	}

	for(auto segment : _segments)
	{
		for(auto colorGroup : _matchingColors)
		{
			if (std::find(colorGroup.begin(), colorGroup.end(), segment->color) != colorGroup.end())
			{
				segment->color = colorGroup[0];
				break;
			}
		}
	}
	colorsCount -= deletedGroups;
}

void CollisionDetector::drawAll()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 110, -10, 110, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for(auto segment : _segments)
	{
		double x1 = (double) segment->startPoint.x;
		double y1 = (double) segment->startPoint.y;
		double x2 = (double) segment->endPoint.x;
		double y2 = (double) segment->endPoint.y;

		glColor3ub((220 * segment->color) % 256, (300 * segment->color) % 256, (400 * segment->color) % 256);

		glBegin(GL_LINE_STRIP);
		glVertex3f(x1, y1, 0.0);
		glVertex3f(x2, y2, 0.0);
		glEnd();
	}

	glFinish();
	glutSwapBuffers();
}
