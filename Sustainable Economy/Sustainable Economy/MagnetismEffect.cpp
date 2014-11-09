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
    g_player->SetMagnetic(true);
    m_IsDone = true;
}

void MagnetismEffect::OnEnd()
{
    // Left empty; nothing to do
}