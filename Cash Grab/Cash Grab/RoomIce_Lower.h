#pragma once
#include "room.h"
class RoomIce_Lower :
	public Room
{
public:
	RoomIce_Lower(void);

	void Render(void) override final;

private:
	vector<pair<Position, SDL_Rect>> m_SnowPositions;
};

