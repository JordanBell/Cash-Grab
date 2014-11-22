//
//  Wall.cpp
//  CashGrab
//
//  Created by Tristan Bell on 20/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Wall.h"

Wall::Wall(int x, int y, SDL_Surface* sheet, SDL_Rect* clip) : Collidable(x, y), GameObject(x, y)
{
    m_IsMoveable = false;
    m_imageSurface = sheet;
    m_imageRect = clip;
}