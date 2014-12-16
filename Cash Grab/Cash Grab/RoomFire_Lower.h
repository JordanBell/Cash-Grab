#pragma once
#include "room.h"
class RoomFire_Lower :
	public Room
{
public:
	RoomFire_Lower(void);

	void Render(void) override final;
};

