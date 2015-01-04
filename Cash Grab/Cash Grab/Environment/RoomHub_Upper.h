#pragma once
#include "room.h"
class RoomHub_Upper :
	public Room
{
public:
	RoomHub_Upper(void)
		: Room(0, -screen->h, Dimensions(screen->w, screen->h), Element::NORMAL, LAYER_ENV_UPPER) {}

	void Render(void) override final;
};

