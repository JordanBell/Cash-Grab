//
//  ImageButton.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "ImageButton.h"

ImageButton::ImageButton(int x, int y, SDL_Surface *imageSurface, ClickHandler clickHandler, bool repeatClick) : Button(x, y, clickHandler, repeatClick)
{
    m_imageSurface = imageSurface;
    
    m_imageRect = new SDL_Rect;
    m_imageRect->x = x;
    m_imageRect->y = y;
    m_imageRect->w = m_imageSurface->w;
    m_imageRect->h = m_imageSurface->h;
}

ImageButton::~ImageButton()
{
    SDL_FreeSurface(m_imageSurface);
}