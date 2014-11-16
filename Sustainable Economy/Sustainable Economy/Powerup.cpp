//
//  Powerup.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Powerup.h"
#include "Resources.h"

Powerup::Powerup(int start_x, int start_y, int end_x, int end_y) : Throwable(start_x, start_y, end_x, end_y)
{    
    sprite_sheet = g_resources->GetPowerupSheet();
    m_HitBox->w = 16;
    m_HitBox->h = 16;
    
    InitSheet();
}

void Powerup::OnCollect(void)
{
    g_game->AddEffect(m_Effect);
}

void Powerup::update(int delta)
{
    Throwable::update(delta);
    
    IncCycle();
}