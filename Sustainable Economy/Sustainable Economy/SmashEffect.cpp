//
//  SmashEffect.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "SmashEffect.h"

SmashEffect::SmashEffect(int smashRadius) : m_SmashRadius(smashRadius)
{   }

void SmashEffect::OnStart()
{
    g_player->Smash(m_SmashRadius);
    m_IsDone = true;
}

void SmashEffect::OnEnd()
{
    // Left blank; nothing to be done
}