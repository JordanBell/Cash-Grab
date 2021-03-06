//
//  EffectMagnetism.h
//  CashGrab
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __CashGrab__EffectMagnetism__
#define __CashGrab__EffectMagnetism__

#include "Effect.h"

class EffectMagnetism : public Effect {
private:
    static int s_MagnetismDistance;
    static int s_MagnetismSpeed;
    
    /* How long powerups last for */
    const int k_PowerupTimeout;
    
public:
    EffectMagnetism(GameObject* parent) :
		Effect(parent), k_PowerupTimeout(5000) {  }
    
    void OnStart() override;
    void OnUpdate(int delta) override;
    void OnEnd() override;
    
    static void SetMagnetismDistance(int distance) { s_MagnetismDistance = distance; }
    static void SetMagnetismSpeed(int speed) { s_MagnetismSpeed = speed; }
};

#endif /* defined(__CashGrab__EffectMagnetism__) */
