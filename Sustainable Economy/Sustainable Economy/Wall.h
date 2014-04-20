//
//  Wall.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 20/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__Wall__
#define __SustainableEconomy__Wall__

#include "Collidable.h"

class Wall : public Collidable {
    
public:
    Wall(int x, int y, SDL_Surface* sheet, SDL_Rect* clip);
    
    void set_skin() { }
};

#endif /* defined(__SustainableEconomy__Wall__) */
