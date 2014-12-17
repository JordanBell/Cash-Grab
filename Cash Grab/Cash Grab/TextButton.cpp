//
//  TextButton.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "TextButton.h"
#include "Resources.h"

TextButton::TextButton(int x, int y, ClickHandler clickHandler, const char *text) : Button(x, y, clickHandler)
{
    m_color = { 0, 0, 0 };
    m_imageSurface = TTF_RenderText_Solid(g_resources->GetFont(), text, m_color);
    
    m_imageRect = new SDL_Rect();
    m_imageRect->x = x;
    m_imageRect->y = y;
    m_imageRect->w = m_imageSurface->w;
    m_imageRect->h = m_imageSurface->h;
}