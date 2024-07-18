#include "monitor.h"
#include <highlevelmonitorconfigurationapi.h>

Monitor::Monitor(HANDLE handle) : mHandle(handle) {
	initialize();
}

void Monitor::initialize() {
	GetMonitorCapabilities(mHandle, &mCapabilities, &mSupportedColorTemps);
	GetMonitorBrightness(mHandle, &mMinBright, &mCurrentBright, &mMaxBright);
}