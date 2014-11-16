//
//  EffectPull.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__EffectPull__
#define __SustainableEconomy__EffectPull__

#include "Effect.h"

class EffectPull : public Effect {
    
public:
    EffectPull(Entity* parent) : Effect(parent) {  }
    
    void OnStart() override;
    void OnEnd() override { }
};

#endif /* defined(__SustainableEconomy__EffectPull__) */
