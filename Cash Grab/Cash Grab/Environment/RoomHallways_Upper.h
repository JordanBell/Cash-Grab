#pragma once
#include "room.h"
class RoomHallways_Upper :
	public Room
{
public:
	RoomHallways_Upper(void)
		: Room(0, -2*screen->h, Dimensions(screen->w, screen->h), Element::NORMAL, LAYER_ENV_UPPER) {}

	void Render(void) override final;

private:
	void RenderLeft(void);
	void RenderRight(void);
};
