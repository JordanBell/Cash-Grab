//
//  Coin.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 09/02/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__Coin__
#define __SustainableEconomy__Coin__

#include "SDL.h"
#include "Entity.h"

class Coin : public Entity
{
public:
    Coin(SDL_Surface* sheet);
    
    void update();
    void render();
    
private:
    static SDL_Surface *image;
};

#endif