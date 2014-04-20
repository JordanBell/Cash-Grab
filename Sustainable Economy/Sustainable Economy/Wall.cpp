//
//  Wall.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 20/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Wall.h"

Wall::Wall(int x, int y, SDL_Surface* sheet, SDL_Rect* clip) : Collidable(x, y)
{
    m_IsMoveable = false;
    sprite_sheet = sheet;
    skin = clip;
}