#pragma once
#include "room.h"
class RoomOriginal_Lower :
	public Room
{
public:
	RoomOriginal_Lower(void);

	void Render(void) override final;
	void Update(int delta) override final;
};

