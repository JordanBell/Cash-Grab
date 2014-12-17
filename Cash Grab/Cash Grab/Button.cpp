//
//  Button.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Button.h"
#include "Resources.h"

Button::Button(int x, int y, ClickHandler clickHandler) : GameObject(x, y), m_clickHandler(clickHandler)
{
    m_color = { 0, 0, 0 };
}

bool Button::inBounds(int x, int y)
{
    return (x >= m_imageRect->x && x <= m_imageRect->x + m_imageRect->w &&
            y >= m_imageRect->y && y <= m_imageRect->y + m_imageRect->h);
}

void Button::Render()
{
    apply_surface(x, y, m_imageSurface, screen);
}

void Button::Click()
{
    m_clickHandler();
}