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
LFX2SETLIGHTACTIONCOLOR setlightActionColor;
LFX2ACTIONCOLOREX lightActionColorExFunction;
LFX2SETTIMING setTiming;
LFX2GETNUMDEVICES getNumDevicesFunction;
LFX2GETDEVDESC getDeviceDescriptionFunction;
LFX2GETNUMLIGHTS getNumLightsFunction;
LFX2SETLIGHTCOL setLightColorFunction;
LFX2GETLIGHTCOL getLightColorFunction;
LFX2GETLIGHTDESC getLightDescriptionFunction;
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
		setlightActionColor = (LFX2SETLIGHTACTIONCOLOR) GetProcAddress(hLibrary, LFX_DLL_SETLIGHTACTIONCOLOR);
		getNumDevicesFunction = (LFX2GETNUMDEVICES) GetProcAddress(hLibrary, LFX_DLL_GETNUMDEVICES);
		getDeviceDescriptionFunction = (LFX2GETDEVDESC) GetProcAddress(hLibrary, LFX_DLL_GETDEVDESC);
		getNumLightsFunction = (LFX2GETNUMLIGHTS) GetProcAddress(hLibrary, LFX_DLL_GETNUMLIGHTS);
		setLightColorFunction = (LFX2SETLIGHTCOL) GetProcAddress(hLibrary, LFX_DLL_SETLIGHTCOL);
		getLightColorFunction = (LFX2GETLIGHTCOL) GetProcAddress(hLibrary, LFX_DLL_GETLIGHTCOL);
		setTiming = (LFX2SETTIMING) GetProcAddress(hLibrary, LFX_DLL_SETTIMING);
		result = initFunction();
	}

}

bool AlienFXSDK::SetLEDs(COLORREF pixels[64][256]) { 
	if (result == LFX_SUCCESS) {
		//result = setTiming(100);
		result = resetFunction();

		unsigned int numDevs = 0;
		result = getNumDevicesFunction(&numDevs);

		for (unsigned int devIndex = 0; devIndex < numDevs; devIndex++) {
			unsigned int numLights = 0;
			result = getNumLightsFunction(devIndex, &numLights);

			//Add the number of colors you want for each LED, I am taking 2 for example
			LFX_COLOR color1, color2;

			color1.red = 255;
			color1.green = 0;
			color1.blue = 0;
			color1.brightness = 255;

			color2.red = 155;
			color2.green = 120;
			color2.blue = 255;
			color2.brightness = 255;

			//Example which sets 2 colors across all LED's for each odd and even index
			for (unsigned int lightIndex = 0; lightIndex < numLights; lightIndex++)
				setLightColorFunction(devIndex, lightIndex, (lightIndex % 2 == 0) ? &color1 : &color2);
			
		}
		result = updateFunction();

		//Use this code to release resources such as when program exits and set AlienFX to default state
		//result = releaseFunction();

		//-------------------Old code------------------

		//COLORREF single_color = pixels[ROW_IDX_SINGLE_COLOR][0];

		//Solid Colors Example on Left Keyboard Zone
		//result = lightFunction(LFX_FRONT_LOWER_LEFT, LFX_GREEN | LFX_FULL_BRIGHTNESS);

		//This is Pulse Effect example on Center Zone
		//result = lightActionColorFunction(LFX_FRONT_LOWER_CENTER, LFX_ACTION_PULSE, LFX_CYAN | LFX_FULL_BRIGHTNESS);
		//Sleep(5000);
		//This is Morph Effect (transisiton of one color to another) Example on Right Zone
		//result = lightActionColorExFunction(LFX_FRONT_LOWER_RIGHT, LFX_ACTION_MORPH, LFX_RED | LFX_FULL_BRIGHTNESS, LFX_BLUE | LFX_FULL_BRIGHTNESS);
		
		return true;
	} else {
		return false;
	}

}
