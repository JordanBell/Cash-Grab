//
//  UIElement.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 04/01/2015.
//  Copyright (c) 2015 Tristan Bell. All rights reserved.
//

#include "UIElement.h"
#include "Resources.h"

UIElement::UIElement(int x, int y) : GameObject(x, y)
{ }

void UIElement::Center(int width)
{
    SDL_Rect centerRect = GetCenter();
    
    int centerX = width / 2;
    
    x += centerX - centerRect.x;
    m_imageRect->x = x;
}

void UIElement::Center(UIElement *other)
{
    SDL_Rect centerRect = GetCenter();
    SDL_Rect otherCenterRect = other->GetCenter();
    
    x += otherCenterRect.x - centerRect.x;
    
    m_imageRect->x = x;
}

void UIElement::Render()
{
    apply_surface(x, y, m_imageSurface, screen);
}

int UIElement::GetWidth()
{
    return m_imageRect->w;
}

int UIElement::GetHeight()
{
    return m_imageRect->h;
}