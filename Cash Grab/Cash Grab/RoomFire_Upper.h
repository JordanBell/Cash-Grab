#pragma once
#include "room.h"
#include "Sinkhole_Bottom.h"
class RoomFire_Upper :
	public Room
{
public:
	RoomFire_Upper(void)
		: Room(screen->w, -screen->h*2, Dimensions(screen->w, screen->h*2), FIRE, LAYER_ENV_UPPER) 
	{ g_game->addGameObject( new Sinkhole_Bottom() ); }

	void Render(void) override final;
	void Update(int delta) override final;
};

