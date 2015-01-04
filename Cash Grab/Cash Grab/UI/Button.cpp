//
//  Button.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Button.h"
#include "Resources.h"

Button::Button(int x, int y, ClickHandler clickHandler, bool repeatClick) : GameObject(x, y), m_clickHandler(clickHandler), m_highlighted(false), m_clickedDown(false), m_shouldRepeatClick(repeatClick), m_repeatCounter(0)
{
    m_color.r = 0;
    m_color.g = 0;
    m_color.b = 0;
}

void Button::Center(int width)
{
    SDL_Rect centerRect = GetCenterRect();
    
    int centerX = width / 2;
    
    x += centerX - centerRect.x;
    m_imageRect->x = x;
}

bool Button::inBounds(int x, int y)
{
    return (x >= m_imageRect->x && x <= m_imageRect->x + m_imageRect->w &&
            y >= m_imageRect->y && y <= m_imageRect->y + m_imageRect->h);
}

void Button::Update(int delta)
{
    GameObject::Update(delta);
    
    if (m_shouldRepeatClick && m_clickedDown) {
        m_repeatCounter += delta;
        
        if (m_justClicked) {
            if (m_repeatCounter >= INITIAL_REPEAT_TIMEOUT) {
                m_clickHandler();
                m_repeatCounter = 0;
                m_justClicked = false;
            }
        }
        else if (m_repeatCounter >= CONTINUOUS_REPEAT_TIMEOUT) {
            m_clickHandler();
            m_repeatCounter = 0;
        }
    }
}

void Button::Render(void)
{
    apply_surface(x, y, m_imageSurface, screen);
}

void Button::ClickDown()
{
    y += 1;
    SetClicked();
}

void Button::ClickUp()
{
    if (m_clickedDown) {
        y -= 1;
        m_clickHandler();
    }
    
    m_repeatCounter = 0;
    m_clickedDown = false;
}

void Button::SetClicked()
{
    m_clickedDown = true;
    m_justClicked = true;
}