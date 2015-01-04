//
//  Powerup.h
//  CashGrab
//
//  Base class for powerups.
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __CashGrab__Powerup__
#define __CashGrab__Powerup__

#include <stdio.h>
#include "Throwable.h"
#include "Effect.h"
#include "Game.h"

class Powerup : public Throwable {
public:
    Powerup(int start_x, int start_y, int end_x, int end_y);
    
    virtual void OnCollect(void) override;
    
    virtual void Update(int delta) override;
    
protected:
    Effect *m_Effect;
    SDL_Rect* sprites[ 8 ];

	// TODO: Merge this with coin's UpdateImageRect function
	void UpdateImageRect(void) override { m_imageRect = sprites[m_cycle/GetAnimationSpeed()]; }
};

#endif /* defined(__CashGrab__Powerup__) */
