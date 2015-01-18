//
//  PowerupSmash.cpp
//  CashGrab
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "PowerupSmash.h"
#include "EffectSmash.h"

int PowerupSmash::value = 0;

PowerupSmash::PowerupSmash(int start_x, int start_y, int end_x, int end_y) : Powerup(start_x, start_y, end_x, end_y)
{
    m_Effect = new EffectSmash(this, SMASH_RADIUS);
    InitSprites();
}
PowerupSmash::PowerupSmash(int start_x, int start_y, int end_x, int end_y, int _) : Powerup(start_x, start_y, end_x, end_y)
{
    throw runtime_error("Cannot create a powerup with an element");
}

void PowerupSmash::OnCollect(void)
{
	Powerup::OnCollect();

	int randPhrase = rand()%3;

	switch (randPhrase)
	{
	case 0: g_player->Say("Smash!");
	case 1: g_player->Say("Boom!");
	case 2: g_player->Say("Closer!");
	}
}

void PowerupSmash::InitSprites(void)
{
    for (int i = 0; i < 8; i++)
    {
        SDL_Rect* clip = new SDL_Rect();
        
        clip->x = TILE_SIZE * i;
        clip->y = TILE_SIZE;
        clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
    }
}