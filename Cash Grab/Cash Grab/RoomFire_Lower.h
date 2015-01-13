#pragma once
#include "room.h"
class RoomFire_Lower :
	public Room
{
public:
	RoomFire_Lower(void);

	void InitialiseDispenser(void);

	void Render(void) override final;

	const Position& GetRandPitPos(const string pitSelection = "any") const;

private:
	list<const Position> m_PitPositions;

	// Render the floor, outer walls, etc.
	void RenderBasic(void);

	// Render things of interest, ie inner walls etc.
	void RenderInterior(void);
};

