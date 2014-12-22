#pragma once
#include "room.h"
using namespace std;

class RoomHallways_Lower :
	public Room
{
public:
	RoomHallways_Lower(void);

	void Render(void) override final;

	// Get the room's friction
	virtual float GetFriction(void)
		{ return (g_player->x < x+8*TILE_SIZE) ? FRICTION_ICE : FRICTION_DEFAULT; }

private:
	void BuildWallsLeft(void);
	void BuildWallsRight(void);

	void RenderLeft(void);
	void RenderRight(void);

	vector<pair<Position, SDL_Rect>> m_SnowPositions;
};

