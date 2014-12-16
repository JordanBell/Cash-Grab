#pragma once
#include "room.h"
class RoomIce_Lower :
	public Room
{
public:
	RoomIce_Lower(void);

	void Render(void) override final;

	// Get the room's friction
	virtual float GetFriction(void)
		{ return FRICTION_ICE; }

private:
	vector<pair<Position, SDL_Rect>> m_SnowPositions;
};

