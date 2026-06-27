#include "EngineTime.h"
EngineTime* EngineTime::sharedInstance = nullptr;

void EngineTime::initialize()
{
	sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	/*sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsed_seconds.count();*/
	//std::cout << "Frame upade finished in "  << sharedInstance->deltaTime << "\n";

    
        sharedInstance->end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed = sharedInstance->end - sharedInstance->start;

        const double targetFrame = 1.0 / 60.0;

        if (elapsed.count() < targetFrame)
        {
            Sleep((DWORD)((targetFrame - elapsed.count()) * 1000.0));
        }

        sharedInstance->end = std::chrono::system_clock::now();

        elapsed = sharedInstance->end - sharedInstance->start;

        sharedInstance->deltaTime = elapsed.count();
    
}
