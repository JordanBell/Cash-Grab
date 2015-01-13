//
//  EffectSmash.cpp
//  CashGrab
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "EffectSmash.h"
#include "Player.h"

EffectSmash::EffectSmash(GameObject* parent, int smashRadius) : Effect(parent), m_SmashRadius(smashRadius)
{   }

void EffectSmash::OnStart()
{
    g_player->Smash(m_SmashRadius);
}

void EffectSmash::OnEnd()
{
    // Left blank; nothing to be done
}
