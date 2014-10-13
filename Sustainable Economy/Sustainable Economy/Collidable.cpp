//
//  Collidable.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 18/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Collidable.h"
#include "Game.h"

bool HitTest(SDL_Rect* first, SDL_Rect* second)
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
    
    if (otherBottom <= top)
        collides = false;
    if (otherTop >= bottom)
        collides = false;
    if (otherLeft >= right)
        collides = false;
    if (otherRight <= left)
        collides = false;
    
    return collides;
}

Collidable::Collidable(int x, int y) : Entity(x, y)
{
    m_IsMoveable = true;
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

bool Collidable::CollidesWith(Collidable *other)
{
    return HitTest(m_HitBox, other->m_HitBox);
}

bool Collidable::WillCollideWith(Collidable *other)
{
    return HitTest(m_AABB, other->m_HitBox);
}

void Collidable::update(int delta)
{
    m_HitBox->x = x;
    m_HitBox->y = y;
    
    // Subclasses must set position of AABB themselves
}




















