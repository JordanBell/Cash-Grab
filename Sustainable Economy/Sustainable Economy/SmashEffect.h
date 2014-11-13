//
//  SmashEffect.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 08/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__SmashEffect__
#define __SustainableEconomy__SmashEffect__

#include "Effect.h"

class SmashEffect : public Effect {
private:
    int m_SmashRadius;
    
public:
    SmashEffect(int smashRadius);
    
    void OnStart();
    void OnEnd();
};

#endif /* defined(__SustainableEconomy__SmashEffect__) */
