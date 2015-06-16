#include "Program.h"


Program::Program(int argc, char *argv[]) : _interface(argc, argv)
{
}

void Program::run()
{
	if (_interface.getBoolParameter("--usage"))
	{
		_interface.printUsage();
		return;
	}
	if (_interface.getBoolParameter("--help"))
	{
		_interface.printHelp();
		return;
	}

	if (_interface.getStringParameter("--file") != "")
	{
		if (_interface.getStringParameter("--getnerate-tests") != "")
		{
			MessageHandler::printMessage("Random generation & input file given, ignoring generation", MessageHandler::WARNING);
		}

		MessageHandler::printMessage("Loading form file", MessageHandler::INFO);
		Utilities::timeStart();
		//acquire
		MessageHandler::printMessage(std::to_string(Utilities::timeStop()), MessageHandler::TIME);
	}
	else if (_interface.getStringParameter("--generate-tests") != "")
	{
		unsigned int tests = Utilities::convertFromString<unsigned int>(_interface.getStringParameter("--generate-tests"));
		
		if (tests > 0)
		{
			MessageHandler::printMessage("Generating records", MessageHandler::INFO);
			Utilities::timeStart();
			this->_collection.generateRandomData(tests, Utilities::windowSize); //HARDCODE
			MessageHandler::printMessage(std::to_string(Utilities::timeStop()), MessageHandler::TIME);
		}
		else
		{
			MessageHandler::printMessage("Number of tests is equal or less than 0.", MessageHandler::ERR);
			return;
		}

		CollisionDetector::AlgorithmType algorithmType = CollisionDetector::DS;
		CollisionDetector::ArrangmentType arrangmentType = CollisionDetector::NO;

		std::string algorithmParameter, arrangmentParameter;
		algorithmParameter = _interface.getStringParameter("--algorithm");
		arrangmentParameter = _interface.getStringParameter("--arrangment");


		if (algorithmParameter != "")
		{
			algorithmParameter == "WS" ? algorithmType = CollisionDetector::WS : algorithmType = CollisionDetector::DS;
		}

		if (arrangmentParameter != "")
		{
			algorithmParameter == "SH" ? arrangmentType = CollisionDetector::SH : arrangmentType = CollisionDetector::NO;
		}

		_collection.setCollisionDetector(new CollisionDetector(_collection.getSegments(), algorithmType, arrangmentType));
	
		_collection.getCollisionDetector()->arrange();


	}
}