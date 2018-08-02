/*---------------------------------------------------------*\
|  Definitions for AlienFX devices      |
|                                                           |
|  Gurjot Singh (gurjotsingh1995@yahoo.com) 02/08/2018      |
\*---------------------------------------------------------*/

#ifndef ALIENFX_SDK_H
#define ALIENFX_SDK_H

#include "VisualizerDefines.h"

class AlienFXSDK
{
public:
	AlienFXSDK();
	~AlienFXSDK();

	void Initialize();
	bool SetLEDs(COLORREF pixels[64][256]);
};

#endif
#pragma once
