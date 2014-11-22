//
//  PowerupPull.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "PowerupPull.h"
#include "EffectPull.h"
#include "EffectMagnetism.h"

int PowerupPull::value = 0;

PowerupPull::PowerupPull(int start_x, int start_y, int end_x, int end_y) : Powerup(start_x, start_y, end_x, end_y)
{
    m_Effect = new EffectPull(this);
    InitSheet();
}

PowerupPull::~PowerupPull()
{
    for (int i = 0; i < 8; i++)
    {
        delete sprites[i];
    }
}

void PowerupPull::InitSheet(void)
{
    for (int i = 0; i < 8; i++)
    {
        SDL_Rect* clip = new SDL_Rect();
        
        clip->x = TILE_SIZE * i;
        clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
    }
}