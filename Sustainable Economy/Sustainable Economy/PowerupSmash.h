//
//  PowerupSmash.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__PowerupSmash__
#define __SustainableEconomy__PowerupSmash__

#include "Powerup.h"

#define SMASH_RADIUS 500

class PowerupSmash : public Powerup {
    
public:
    PowerupSmash(int start_x, int start_y, int end_x, int end_y);
};

#endif /* defined(__SustainableEconomy__PowerupSmash__) */
