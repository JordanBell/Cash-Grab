//
//  EffectSmash.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__EffectSmash__
#define __SustainableEconomy__EffectSmash__

#include "Effect.h"

class EffectSmash : public Effect {
private:
    int m_SmashRadius;
    
public:
    EffectSmash(Entity* parent, int smashRadius);
    
    void OnStart();
    void OnEnd();
};

#endif /* defined(__SustainableEconomy__EffectSmash__) */
