//
//  TextButton.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "TextButton.h"
#include "Resources.h"

TextButton::TextButton(int x, int y, ClickHandler clickHandler, const char *text, bool repeatClick) : Button(x, y, clickHandler), m_text(text)
{
	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
    
    m_highlightedColor.r = 140;
    m_highlightedColor.g = 200;
    m_highlightedColor.b = 255;
    
    m_imageSurface = TTF_RenderText_Solid(g_resources->GetFont(), text, m_color);
    
    m_imageRect = new SDL_Rect();
    m_imageRect->x = x;
    m_imageRect->y = y;
    m_imageRect->w = m_imageSurface->w;
    m_imageRect->h = m_imageSurface->h;
}

void TextButton::SetHighlight(bool highlight)
{
    if (highlight != m_highlighted) {
        if (highlight) {
            m_imageSurface = TTF_RenderText_Solid(g_resources->GetFont(), m_text, m_highlightedColor);
        }
        else {
            m_imageSurface = TTF_RenderText_Solid(g_resources->GetFont(), m_text, m_color);
        }
    }
    
    Button::SetHighlight(highlight);
}