//
//  EffectSmash.h
//  CashGrab
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __CashGrab__EffectSmash__
#define __CashGrab__EffectSmash__

#include "Effect.h"

class EffectSmash : public Effect {
private:
    int m_SmashRadius;
    
public:
    EffectSmash(GameObject* parent, int smashRadius);
    
    void OnStart();
    void OnEnd();
};

#endif /* defined(__CashGrab__EffectSmash__) */
