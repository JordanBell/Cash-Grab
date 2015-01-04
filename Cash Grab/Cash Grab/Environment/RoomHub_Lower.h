#pragma once
#include "room.h"
class RoomHub_Lower :
	public Room
{
public:
	RoomHub_Lower(void);

	void Render(void) override final;
};

