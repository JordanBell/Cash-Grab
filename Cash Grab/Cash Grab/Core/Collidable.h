//
//  Collidable.h
//  CashGrab
//
//  Created by Tristan Bell on 18/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef CashGrab_Collidable_h
#define CashGrab_Collidable_h

#include "Sprite.h"
#include "SDL.h"
#include "XY.h"

class Collidable {
protected:
    SDL_Rect* m_HitBox;
    SDL_Rect* m_AABB;
    
public:
    virtual ~Collidable(void) { }
    
    bool m_IsMoveable; // ie Walls are not moveable
    
    XY m_Velocities; // Number of pixels to move next frame (if it can move)

    Collidable(int x, int y);
    
    virtual bool CollidesWith(Collidable* other, int &collisionOverlap);
    virtual bool WillCollideWith(Collidable* other, int &collisionOverlap);
    virtual void UpdateCollidablePos(const int x, const int y);
    virtual void DoMove(void);
};

#endif
