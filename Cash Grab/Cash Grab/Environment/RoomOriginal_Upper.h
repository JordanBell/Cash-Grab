#pragma once
#include "room.h"
class RoomOriginal_Upper :
	public Room
{
public:
	RoomOriginal_Upper(void)
		: Room(0, 0, Dimensions(screen->w, screen->h), Element::NORMAL, LAYER_ENV_UPPER) {}

	void Render(void) override final;
};

