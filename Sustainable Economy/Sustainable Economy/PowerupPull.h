//
//  PowerupPull.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__PowerupPull__
#define __SustainableEconomy__PowerupPull__

#include "Powerup.h"

class PowerupPull : public Powerup {
    
public:
    static int value;
    
    PowerupPull(int start_x, int start_y, int end_x, int end_y);
    ~PowerupPull();
    
private:
    void InitSheet(void) override final;
    
};

#endif /* defined(__SustainableEconomy__PowerupPull__) */
