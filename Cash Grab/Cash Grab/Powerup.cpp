//
//  Powerup.cpp
//  CashGrab
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Powerup.h"
#include "Resources.h"

Powerup::Powerup(int start_x, int start_y, int end_x, int end_y) : Throwable(start_x, start_y, end_x, end_y)
{    
    m_imageSurface = g_resources->GetPowerupSheet();
    m_HitBox->w = 16;
    m_HitBox->h = 16;

    m_numSprites = 8;
	SetAnimationSpeed(7);
}

void Powerup::OnCollect(void)
{
    g_game->AddEffect(m_Effect);
}

void Powerup::Update(int delta)
{
    Throwable::Update(delta);
    
   // IncCycle();
}