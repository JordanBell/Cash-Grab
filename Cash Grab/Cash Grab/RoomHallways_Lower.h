#pragma once
#include "room.h"
using namespace std;

class RoomHallways_Lower :
	public Room
{
public:
	RoomHallways_Lower(void);

	void Render(void) override final;

private:
	void BuildWallsLeft(void);
	void BuildWallsRight(void);

	void RenderLeft(void);
	void RenderRight(void);

	vector<pair<Position, SDL_Rect>> m_SnowPositions;
};

