//
//  EffectMagnetism.cpp
//  CashGrab
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "EffectMagnetism.h"
#include "Coin.h"

using namespace std;

int EffectMagnetism::s_MagnetismDistance = MAGNETISM_DISTANCE_DEFAULT;
int EffectMagnetism::s_MagnetismSpeed = MAGNETISM_SPEED_DEFAULT;

void EffectMagnetism::OnStart()
{
    m_Duration = -1;
}

void EffectMagnetism::OnUpdate(int delta)
{
    if (s_MagnetismDistance != MAGNETISM_DISTANCE_DEFAULT) {
        // Only increase elapsed time when we're under the influence of a powerup
        Effect::OnUpdate(delta);
        
        // Reset to default distance/speed on powerup timeout
        if (m_ElapsedTime >= k_PowerupTimeout) {
            s_MagnetismDistance = MAGNETISM_DISTANCE_DEFAULT;
            s_MagnetismSpeed = MAGNETISM_SPEED_DEFAULT;
            
            m_ElapsedTime = 0;
        }
    }
    
    list<Coin*> closeCoins = Coin::CoinsAroundPlayer(s_MagnetismDistance);
    
    // Magnetise the coins
    for (Coin* c : closeCoins)
        c->SetHoming(s_MagnetismDistance, s_MagnetismSpeed);
}

void EffectMagnetism::OnEnd()
{
    
}