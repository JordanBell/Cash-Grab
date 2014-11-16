//
//  PowerupMagnetism.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 16/11/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__PowerupMagnetism__
#define __SustainableEconomy__PowerupMagnetism__

#include "Powerup.h"

class PowerupMagnetism : public Powerup {
    
public:
    static int value;
    
    PowerupMagnetism(int start_x, int start_y, int end_x, int end_y);
    ~PowerupMagnetism();
    
    void OnCollect(void) override final;
    
private:
    void InitSheet(void) override final;
};

#endif /* defined(__SustainableEconomy__PowerupMagnetism__) */
