//
//  Effect.h
//  SustainableEconomy
//
//  Base class for effects, such as coin magnetism, icy floor, etc.
//  Contains member functions which are called by EffectManager to
//  implement the effects of powerups.
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__Effect__
#define __SustainableEconomy__Effect__

#include "Player.h"

class Effect {
protected:
    /* Duration of this effect, in ms */
    int m_Duration;
    /* Time elapsed while running: to know when to stop effect */
    int m_ElapsedTime;
    
public:
    bool m_IsDone;
    
	Effect() : m_Duration(0), m_ElapsedTime(0), m_IsDone(false)  {}
    virtual ~Effect() { }
    
    /**
     * Called when an effect is created. Should perform
     * initialisation, and should be used for one-off
     * effects such as toggling magnetism.
     */
    virtual void OnStart() = 0;
    
    /**
     * Used for continuous effects. Called every update
     * of the game loop.
     */
    virtual void OnUpdate(int delta)
    {
        m_ElapsedTime += delta;
        
        if (m_ElapsedTime >= m_Duration) {
            m_ElapsedTime = 0;
            m_IsDone = true;
        }
    }
    
    /**
     * Called when an effect is finished. Should perform
     * any required cleanup at the end of a continuous
     * effect.
     */
    virtual void OnEnd() = 0;
    
};

#endif /* defined(__SustainableEconomy__Effect__) */
