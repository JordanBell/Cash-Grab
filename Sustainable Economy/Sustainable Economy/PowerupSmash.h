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
    static int value;
    
    PowerupSmash(int start_x, int start_y, int end_x, int end_y);
    ~PowerupSmash();
    
private:
    void InitSheet(void) override final;
    void set_skin() override { skin = sprites[0]; }
};

#endif /* defined(__SustainableEconomy__PowerupSmash__) */
