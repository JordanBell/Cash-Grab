//
//  Label.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Label.h"

Label::Label(int x, int y, string text, SDL_Color color, TTF_Font *font) : UIElement(x, y), m_Text(text), m_Font(font), m_Color(color)
{
    Update(0);
}

void Label::Update(int delta)
{
    UIElement::Update(delta);
    
    if (m_imageSurface) {
        SDL_FreeSurface(m_imageSurface);
    }
    
    m_imageSurface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);
    
    if (!m_imageRect) {
        m_imageRect = new SDL_Rect();
    }
    
    m_imageRect->x = x;
    m_imageRect->y = y;
    m_imageRect->w = m_imageSurface->w;
    m_imageRect->h = m_imageSurface->h;
}

void Label::SetText(string text)
{
    m_Text = text;
}