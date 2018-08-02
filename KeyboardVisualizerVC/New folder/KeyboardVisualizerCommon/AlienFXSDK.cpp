/*---------------------------------------------------------*\
|  Definitions for AlienFX devices      |
|                                                           |
|  Gurjot Singh (gurjotsingh1995@yahoo.com) 02/08/2018      |
\*---------------------------------------------------------*/

#include "AlienFXSDK.h"
#include <windows.h>
#include "LFX2.h"
#include <iostream>
#include <iomanip>

AlienFXSDK::AlienFXSDK() {
}


AlienFXSDK::~AlienFXSDK() {
}



bool initialized(false);
LFX2INITIALIZE initFunction;
LFX2RELEASE releaseFunction;
LFX2RESET resetFunction;
LFX2UPDATE updateFunction;
LFX2LIGHT lightFunction;
LFX2ACTIONCOLOR lightActionColorFunction;
LFX2ACTIONCOLOREX lightActionColorExFunction;
LFX2SETTIMING setTiming;
//LFX_RESULT LFX_GetTiming(const int x);
LFX_RESULT result;

void AlienFXSDK::Initialize() {
	
	HINSTANCE hLibrary = LoadLibrary(TEXT((LFX_DLL_NAME)));
	if (hLibrary) {
		initFunction = (LFX2INITIALIZE) GetProcAddress(hLibrary, LFX_DLL_INITIALIZE);
		releaseFunction = (LFX2RELEASE) GetProcAddress(hLibrary, LFX_DLL_RELEASE);
		resetFunction = (LFX2RESET) GetProcAddress(hLibrary, LFX_DLL_RESET);
		updateFunction = (LFX2UPDATE) GetProcAddress(hLibrary, LFX_DLL_UPDATE);
		lightFunction = (LFX2LIGHT) GetProcAddress(hLibrary, LFX_DLL_LIGHT);
		lightActionColorFunction = (LFX2ACTIONCOLOR) GetProcAddress(hLibrary, LFX_DLL_ACTIONCOLOR);
		lightActionColorFunction = (LFX2ACTIONCOLOR) GetProcAddress(hLibrary, LFX_DLL_ACTIONCOLOR);
		lightActionColorExFunction = (LFX2ACTIONCOLOREX) GetProcAddress(hLibrary, LFX_DLL_ACTIONCOLOREX);
		setTiming = (LFX2SETTIMING) GetProcAddress(hLibrary, LFX_DLL_SETTIMING);
		result = initFunction();
	}

}

bool AlienFXSDK::SetLEDs(COLORREF pixels[64][256]) {
	if (result == LFX_SUCCESS) {
		result = setTiming(100);
		result = resetFunction();
		COLORREF single_color = pixels[ROW_IDX_SINGLE_COLOR][0];
		//Keyboard Left
		result = lightFunction(LFX_FRONT_LOWER_LEFT, 0x00DD0EAA | LFX_FULL_BRIGHTNESS);
		
		//Keyboard Right
		result = lightFunction(LFX_FRONT_LOWER_RIGHT, LFX_YELLOW | LFX_FULL_BRIGHTNESS);

		//Keyboard Center
		result = lightFunction(LFX_FRONT_LOWER_CENTER, 0x000EDDAA | LFX_FULL_BRIGHTNESS);
		result = updateFunction();
		return true;
	} else {
		return false;
	}

}
