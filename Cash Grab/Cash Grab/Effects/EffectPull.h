//
//  EffectPull.h
//  CashGrab
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __CashGrab__EffectPull__
#define __CashGrab__EffectPull__

#include "Effect.h"

class EffectPull : public Effect {
    
public:
    EffectPull(GameObject* parent) : Effect(parent) {  }
    
    void OnStart() override;
    void OnEnd() override { }
};

#endif /* defined(__CashGrab__EffectPull__) */
