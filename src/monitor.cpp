#include "monitor.h"
#include <highlevelmonitorconfigurationapi.h>
#include <iostream>

Monitor::Monitor(HANDLE handle) : mHandle(handle) {
	initialize();
}

void Monitor::initialize() {
	GetMonitorCapabilities(mHandle, &mCapabilities, &mSupportedColorTemps);
	GetMonitorBrightness(mHandle, &mMinBright, &mCurrentBright, &mMaxBright);
}

void Monitor::setBrightness(int brightness) {
	if (brightness > mMaxBright) {
		brightness = mMaxBright;
	}

	SetMonitorBrightness(mHandle, brightness);
}