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
    SDL_Rect* m_AABB;
    
public:
    bool m_IsMoveable; // Walls are not moveable
    
    int m_xVel, m_yVel; // Number of pixels to move next frame (if it can move)
    
    Collidable(int x, int y);
    
    virtual bool CollidesWith(Collidable* other, int &collisionOverlap);
    virtual bool WillCollideWith(Collidable* other, int &collisionOverlap);
    virtual void update(int delta);
    virtual void DoMove();
};

#endif
