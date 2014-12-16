#pragma once
#include "room.h"
class RoomFire_Upper :
	public Room
{
public:
	RoomFire_Upper(void)
		: Room(screen->w, -screen->h*2, Dimensions(screen->w, screen->h*2), FIRE, LAYER_ENV_UPPER) {}

	void Render(void) override final;
};

