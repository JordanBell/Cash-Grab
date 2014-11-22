//
//  PowerupMagnetism.cpp
//  CashGrab
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "PowerupMagnetism.h"
#include "EffectMagnetism.h"

int PowerupMagnetism::value = 0;

PowerupMagnetism::PowerupMagnetism(int start_x, int start_y, int end_x, int end_y) : Powerup(start_x, start_y, end_x, end_y)
{
    // No effect to add, just modify current magnetism effect
    m_Effect = nullptr;
    InitSprites();
}

PowerupMagnetism::~PowerupMagnetism()
{
    for (int i = 0; i < 8; i++)
    {
        delete sprites[i];
    }
}

void PowerupMagnetism::OnCollect()
{
    EffectMagnetism::SetMagnetismDistance(MAGNETISM_DISTANCE_SHORT);
}

void PowerupMagnetism::InitSprites(void)
{
    for (int i = 0; i < 8; i++)
    {
        SDL_Rect* clip = new SDL_Rect();
        
        clip->x = TILE_SIZE * i;
        clip->y = 4 * TILE_SIZE;
        clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
    }
}