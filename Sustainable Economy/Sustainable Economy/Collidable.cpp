//
//  Collidable.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 18/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Collidable.h"
#include "Game.h"

Collidable::Collidable(int x, int y) : Entity(x, y)
{
    m_IsMoveable = true;
    m_HitBox = new SDL_Rect();
    m_HitBox->x = x;
    m_HitBox->y = y;
    
    // assumed to be one tile square
    m_HitBox->w = m_HitBox->h = TILE_SIZE;
}

bool Collidable::CollidesWith(Collidable *other)
{
    int left = m_HitBox->x;
    int right = left + m_HitBox->w;
    int top = m_HitBox->y;
    int bottom = top + m_HitBox->h;
    
    int otherLeft = other->m_HitBox->x;
    int otherRight = otherLeft + other->m_HitBox->w;
    int otherTop = other->m_HitBox->y;
    int otherBottom = otherTop + other->m_HitBox->h;
    
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

void Collidable::update(int delta)
{
    m_HitBox->x = x;
    m_HitBox->y = y;
}