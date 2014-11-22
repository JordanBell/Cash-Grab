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
    InitSheet();
}

PowerupSmash::~PowerupSmash()
{
    for (int i = 0; i < 8; i++)
    {
        delete sprites[i];
    }
}

void PowerupSmash::InitSheet(void)
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