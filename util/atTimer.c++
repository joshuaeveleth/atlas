
#include "atTimer.h++"

#include <stdio.h>
#include <sys/time.h>


atTimer::atTimer()
{
    // Set markTime to 0.0
    markTime = 0.0;

    // Call mark() twice to initialize the mark interval time
    // and set a sane markTime
    mark();
    mark();
}


atTimer::~atTimer()
{
}


void atTimer::mark()
{
    struct timeval timeStruct;
    double newMark;

    // Get the current time from the system
    gettimeofday(&timeStruct, NULL);

    // Record the current time in seconds
    newMark = timeStruct.tv_sec + (timeStruct.tv_usec / 1000000.0);

    // Compute the new mark interval
    markInterval = newMark - markTime;

    // Save the new mark time
    markTime = newMark;
}


void atTimer::markAtInterval(double intervalTime)
{
    struct timeval timeStruct;
    double newMark;

    // Get the current time from the system
    gettimeofday(&timeStruct, NULL);

    // Record the current time in seconds
    newMark = timeStruct.tv_sec + (timeStruct.tv_usec / 1000000.0);

    // Compute the new mark interval
    markInterval = newMark - markTime;

    // See if the given interval is less than the elapsed interval
    if (markInterval > intervalTime)
    {
        // Use the given interval, and set the new mark time to the time
        // that the given interval would have expired
        markTime = newMark - (markInterval - intervalTime);
        markInterval = intervalTime;
    }
    else
    {
        // Use the actual elapsed interval and set the new mark time as if
        // mark() had been called
        markTime = newMark;
    }
}


double atTimer::getInterval()
{
    return markInterval;
}


double atTimer::getElapsed()
{
    struct timeval timeStruct;
    double currentTime;

    // Get the current time in seconds from the system
    gettimeofday(&timeStruct, NULL);
    currentTime = timeStruct.tv_sec + (timeStruct.tv_usec / 1000000.0);
    
    // Return the difference between the current time and the last mark()
    return (currentTime - markTime);
}