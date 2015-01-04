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
	SDL_Surface* m_IceWall;

	void CreateIceWalls(void);

	vector<pair<Position, SDL_Rect>> m_SnowPositions;
	vector<pair<Position, int>> m_SnowPositions_Piles;
};

