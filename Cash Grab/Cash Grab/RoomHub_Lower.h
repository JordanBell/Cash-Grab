#pragma once
#include "room.h"
class RoomHub_Lower :
	public Room
{
public:
	RoomHub_Lower(void);

	void Render(void) override final;

private:
	// Build a station object starting at a given top left position
	void CreateStationWalls(const int x, const int y);
	void RenderStationWalls(const int x, const int y);
	virtual void RenderStation(const int x, const int y);
};

