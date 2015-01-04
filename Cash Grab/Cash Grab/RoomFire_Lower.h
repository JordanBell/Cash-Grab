#pragma once
#include "room.h"
class RoomFire_Lower :
	public Room
{
public:
	RoomFire_Lower(void);

	void InitialiseDispenser(void);

	void Render(void) override final;

private:
	// Render the floor, outer walls, etc.
	void RenderBasic(void);

	// Render things of interest, ie inner walls etc.
	void RenderInterior(void);
};

