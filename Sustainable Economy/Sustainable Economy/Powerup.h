//
//  Powerup.h
//  SustainableEconomy
//
//  Base class for powerups.
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__Powerup__
#define __SustainableEconomy__Powerup__

#include <stdio.h>
#include "Throwable.h"
#include "Effect.h"
#include "Game.h"

class Powerup : public Throwable {
protected:
    Effect *m_Effect;
    SDL_Rect* sprites[ 8 ];
    
public:
    Powerup(int start_x, int start_y, int end_x, int end_y);
    
    virtual void OnCollect(void) override;
    
    virtual void update(int delta) override;
    
protected:
    virtual void InitSheet(void) {  }
    void set_skin() { skin = sprites[cycle/LOOP_SPEED]; }
};

#endif /* defined(__SustainableEconomy__Powerup__) */
