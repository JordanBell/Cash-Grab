//
//  PowerupSmash.cpp
//  CashGrab
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "PowerupSmash.h"
#include "EffectSmash.h"

PowerupSmash::PowerupSmash(int start_x, int start_y, int end_x, int end_y) : Powerup(start_x, start_y, end_x, end_y)
{
    m_Effect = new EffectSmash(this, SMASH_RADIUS);
}