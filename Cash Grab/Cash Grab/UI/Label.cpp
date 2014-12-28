//
//  Label.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Label.h"
#include "Resources.h"

Label::Label(int x, int y, string text, SDL_Color color) : GameObject(x, y), m_Text(text), m_Color(color)
{
    Update(0);
}

void Label::Update(int delta)
{
    GameObject::Update(delta);
    
    if (m_imageSurface) {
        SDL_FreeSurface(m_imageSurface);
    }
    
    m_imageSurface = TTF_RenderText_Solid(g_resources->GetFont(), m_Text.c_str(), m_Color);
    
    if (!m_imageRect) {
        m_imageRect = new SDL_Rect();
    }
    
    m_imageRect->x = x;
    m_imageRect->y = y;
    m_imageRect->w = m_imageSurface->w;
    m_imageRect->h = m_imageSurface->h;
}

void Label::Render()
{
    apply_surface(x, y, m_imageSurface, screen);
}

void Label::SetText(string text)
{
    m_Text = text;
}

void Label::Center(int width)
{
    SDL_Rect centerRect = GetCenter();
    
    int centerX = width / 2;
    
    x += centerX - centerRect.x;
    m_imageRect->x = x;
}