#pragma once

#include<windows.h>

class Monitor 
{
public:
	Monitor(HANDLE handle);

	HANDLE mHandle;
	DWORD mMinBright{ 0 };
	DWORD mMaxBright{ 0 };
	DWORD mCurrentBright{ 0 };
	DWORD mCapabilities{ 0 };
	DWORD mSupportedColorTemps{ 0 };

	void setBrightness(int brightness);

private:
	void initialize();
};

