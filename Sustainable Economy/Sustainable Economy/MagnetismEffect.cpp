//
//  MagnetismEffect.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "MagnetismEffect.h"

void MagnetismEffect::OnStart()
{
    m_Duration = 5000;
    
    if (!g_player->IsMagnetic())
        g_player->SetMagnetic(true);
}

void MagnetismEffect::OnEnd()
{
    g_player->SetMagnetic(false);
}