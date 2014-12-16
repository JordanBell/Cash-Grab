//
//  Collidable.cpp
//  CashGrab
//
//  Created by Tristan Bell on 18/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Collidable.h"
#include "Game.h"

bool HitTest(SDL_Rect* first, SDL_Rect* second, int &collisionOverlap)
{
    int left = first->x;
    int right = left + first->w;
    int top = first->y;
    int bottom = top + first->h;
    
    int otherLeft = second->x;
    int otherRight = otherLeft + second->w;
    int otherTop = second->y;
    int otherBottom = otherTop + second->h;
    
    bool collides = true;
    
    if (otherBottom <= top) {
        collides = false;
    }
    else {
        collisionOverlap = otherBottom - top;
    }
    
    if (otherTop >= bottom) {
        collides = false;
    }
    else {
        collisionOverlap = bottom - otherTop;
    }
    
    if (otherLeft >= right) {
        collides = false;
    }
    else {
        collisionOverlap = right - otherLeft;
    }
    
    if (otherRight <= left) {
        collides = false;
    }
    else {
        collisionOverlap = otherRight - left;
    }
    
    return collides;
}

Collidable::Collidable(int x, int y)
{
    m_IsMoveable = true;
	m_Velocities = XY(0, 0);
    
    m_HitBox = new SDL_Rect();
    m_HitBox->x = x;
    m_HitBox->y = y;
    
    // assumed to be one tile square
    m_HitBox->w = m_HitBox->h = TILE_SIZE;
    
    if (m_IsMoveable)
    {
        m_AABB = new SDL_Rect;
        m_AABB->x = x;
        m_AABB->y = y;
        
        // assumed to be one tile square
        m_AABB->w = m_AABB->h = TILE_SIZE;
    }
    else
    {
        m_AABB = nullptr;
    }
}

bool Collidable::CollidesWith(Collidable *other, int &collisionOverlap)
{
    return HitTest(m_HitBox, other->m_HitBox, collisionOverlap);
}

bool Collidable::WillCollideWith(Collidable *other, int &collisionOverlap)
{
    return HitTest(m_AABB, other->m_HitBox, collisionOverlap);
}

void Collidable::UpdateCollidablePos(const int x, const int y)
{
	// Update Hitbox
    m_HitBox->x = x;
    m_HitBox->y = y;
}


void Collidable::DoMove(void)
{
    // Must be implemented by classes that can move
}
















