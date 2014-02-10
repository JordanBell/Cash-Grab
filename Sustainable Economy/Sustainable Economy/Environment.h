//
//  Environment.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 10/02/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__Environment__
#define __SustainableEconomy__Environment__

#include "Entity.h"

/*
 * Maybe do all implementation in here, as it's quite simple?
 */
class Environment : public Entity
{
public:
    Environment(SDL_Surface* sheet) : Entity(sheet) { }
    void update() { /* Nothing to update */ }
    void render();
    
protected:
    void set_skin();
};

#endif
