//
//  Collidable.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 18/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef SustainableEconomy_Collidable_h
#define SustainableEconomy_Collidable_h

#include "Entity.h"
#include "SDL.h"

class Collidable : public Entity {
protected:
    SDL_Rect* m_HitBox;
    
public:
    bool m_IsMoveable; // Walls are not moveable
    
    Collidable(int x, int y);
    
    virtual bool CollidesWith(Collidable* other);
    virtual void update(int delta);
};

#endif
