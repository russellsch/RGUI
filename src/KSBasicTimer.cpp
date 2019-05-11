#include "rgui/KSBasicTimer.h"
#include <stdio.h>

KSBasicTimer::KSBasicTimer() {
    stopped = true;

	#ifdef _MSC_VER
	this->win32TI = new Win32TimeInterface();
	timeInterfaceInternal = true;
	this->win32TI->getPerformanceFrequency(&frequency);

	#else	//POSIX
		//Something needed here?
	#endif
}

#ifdef _MSC_VER
KSBasicTimer::KSBasicTimer(Win32TimeInterface* alternateTimeInterface){
	stopped = true;
	timeInterfaceInternal = false;
	this->win32TI = alternateTimeInterface;
	this->win32TI->getPerformanceFrequency(&frequency);
}
#else	//POSIX

#endif

KSBasicTimer::~KSBasicTimer() {
	#ifdef _MSC_VER
	if(timeInterfaceInternal) {	//was the time interface allocated internally?
		delete this->win32TI;	//delete it
	}
	#else	//POSIX
		//Something needed here?
	#endif
}


void KSBasicTimer::start(){
    stopped = false;
    #ifdef _MSC_VER
        this->win32TI->getPerformanceCounter(&startTime);
    #else
        gettimeofday(&startTime, NULL);
    #endif
}
void KSBasicTimer::stop() {
	if(stopped == false){
		stopped = true;
		#ifdef _MSC_VER
			this->win32TI->getPerformanceCounter(&endTime);
		#else
			gettimeofday(&endTime, NULL);
		#endif
	}
}

bool KSBasicTimer::isRunning(){
	return !stopped;
}
bool KSBasicTimer::isStopped(){
	return stopped;
}


double KSBasicTimer::getTimeUs(){
    #ifdef _MSC_VER
        if(!stopped) {
            this->win32TI->getPerformanceCounter(&endTime);
        }
        startTimeUs = startTime.QuadPart * (1000000.0/frequency.QuadPart);
        endTimeUs = endTime.QuadPart * (1000000.0/frequency.QuadPart);
    #else
        if(!stopped) {
            gettimeofday(&endTime, NULL);
        }
        startTimeUs = startTime.tv_usec + (startTime.tv_sec*1000000.0);
        endTimeUs = endTime.tv_usec + (endTime.tv_sec*1000000.0);
    #endif

    return abs(endTimeUs - startTimeUs);
}
double KSBasicTimer::getTimeMs(){
    return this->getTimeUs()*.001;
}
double KSBasicTimer::getTimeS() {
    return this->getTimeUs()*.000001;
}


/*
BOOL Win32TimeInterface::getPerformanceCounter(LARGE_INTEGER *lpPerformanceCount){
	return QueryPerformanceCounter(lpPerformanceCount);
}
BOOL Win32TimeInterface::getPerformanceFrequency(LARGE_INTEGER *lpFrequency){
	return QueryPerformanceFrequency(lpFrequency);
}
*/








