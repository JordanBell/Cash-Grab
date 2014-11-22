//
//  PowerupSmash.h
//  CashGrab
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __CashGrab__PowerupSmash__
#define __CashGrab__PowerupSmash__

#include "Powerup.h"

#define SMASH_RADIUS 500

class PowerupSmash : public Powerup {
    
public:
    PowerupSmash(int start_x, int start_y, int end_x, int end_y);
};

#endif /* defined(__CashGrab__PowerupSmash__) */
