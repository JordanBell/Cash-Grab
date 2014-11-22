//
//  EffectManager.h
//  CashGrab
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __CashGrab__EffectManager__
#define __CashGrab__EffectManager__

#include <list>
#include "Effect.h"

using namespace std;

class EffectManager {
    
private:
    list<Effect*> m_Effects;
    
public:
    EffectManager() { }
    ~EffectManager();
    
    void AddEffect(Effect *effect);
    
    void Update(int delta);
};

#endif /* defined(__CashGrab__EffectManager__) */
