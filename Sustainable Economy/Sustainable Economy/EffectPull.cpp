//
//  EffectPull.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "EffectPull.h"
#include "Coin.h"
#include "Player.h"

void EffectPull::OnStart()
{
    int suppression = 0;
    
    for (Coin* c : g_coins)
    {
        if (!c->IsAirborne()) {
//            SDL_Rect center = m_Parent->GetCenter();
            c->LaunchTo(m_Parent->x, m_Parent->y, suppression);
        }
    }
}