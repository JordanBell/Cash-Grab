//
//  PowerupPull.cpp
//  CashGrab
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "PowerupPull.h"
#include "EffectPull.h"
#include "EffectMagnetism.h"

int PowerupPull::value = 0;

PowerupPull::PowerupPull(int start_x, int start_y, int end_x, int end_y, int _) : Powerup(start_x, start_y, end_x, end_y)
{
    m_Effect = new EffectPull(this);
    InitSprites();
}

void PowerupPull::OnCollect(void)
{
	Powerup::OnCollect();

	int randPhrase = rand()%3;

	switch (randPhrase)
	{
	case 0: g_player->Say("Come to me!");
	case 1: g_player->Say("All mine!");
	case 2: g_player->Say("Hahaaaaa...!");
	}
}


void PowerupPull::InitSprites(void)
{
    for (int i = 0; i < 8; i++)
    {
        SDL_Rect* clip = new SDL_Rect();
        
        clip->x = TILE_SIZE * i;
        clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
    }
}