#pragma once
#include "room.h"
class RoomIce_Upper :
	public Room
{
public:
	RoomIce_Upper(void)
		: Room(-screen->w, -screen->h*2, Dimensions(screen->w, screen->h*2), ICE, LAYER_ENV_UPPER) {}

	void Render(void) override final;
};

