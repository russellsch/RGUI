#ifndef KSBASICTIMER_H
#define KSBASICTIMER_H

//TODO: * Update POSIX code to use clock_gettime instead of gettimeofday
//* Fix posix code
//* Wrap Posix and VC time calls into a single TimeInterface class to get rid of these ugly preprocessor macros
//  giving us a simple microsecond based interface


#ifdef _MSC_VER
    #include <windows.h>
#else
    #include <sys/time.h>
#endif

#include <cmath>
using namespace std;

#ifdef _MSC_VER
	//!Wraps the windows calls to QueryPerformanceCounter and QueryPerformanceFrequency
	class Win32TimeInterface {
	public:
		virtual BOOL getPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
		virtual BOOL getPerformanceFrequency(LARGE_INTEGER *lpFrequency);
	};
#else //posix
	//!Wraps the posix calls to gettimeofday
	class PosixTimeInterface {
	public:
		virtual int gettimeofday(struct timeval *tv, struct timezone *tz);
	};
#endif

//!Platform independant simple timer
/*!
Assumes _MSC_VER is defined for WIN32 platform compiling with Visual Studio
*/
class KSBasicTimer {
    public:
        KSBasicTimer();
		#ifdef _MSC_VER
			KSBasicTimer(Win32TimeInterface* alternateTimeInterface);
		#else
			KSBasicTimer(PosixTimeInterface* alternateTimeInterface);
		#endif

        ~KSBasicTimer();
        void start();
        void stop();

		bool isRunning();
		bool isStopped();

        double getTimeS();
        double getTimeUs();
        double getTimeMs();

    protected:
    private:
        #ifdef _MSC_VER
            LARGE_INTEGER frequency, startTime, endTime;
			Win32TimeInterface* win32TI;
        #else
            timeval startTime, endTime;
			PosixTimeInterface* posixTI;
        #endif

        bool stopped;
        double startTimeUs, endTimeUs;

		//was the time interface created internally? used to track if it should be deleted on destruction
		bool timeInterfaceInternal;		
};

#endif // KSBASICTIMER_H
