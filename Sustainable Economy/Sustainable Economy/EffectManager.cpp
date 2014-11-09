//
//  EffectManager.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "EffectManager.h"

EffectManager::~EffectManager()
{
    for (Effect* e : m_Effects) {
        if (e)
            delete e;
    }
}

void EffectManager::AddEffect(Effect *effect)
{
    effect->OnStart();
    
    m_Effects.push_back(effect);
}

void EffectManager::Update(int delta)
{
    list<Effect*> removeQueue;
    
    for (Effect* e : m_Effects) {
        e->OnUpdate(delta);
        
        if (e->m_IsDone) {
            removeQueue.push_back(e);
        }
    }
    
    for (Effect* e : removeQueue) {
        m_Effects.remove(e);
        delete e;
    }
}