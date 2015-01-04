//
//  Button.h
//  Cash Grab
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#pragma once

#include "UIElement.h"
#include <functional>

typedef std::function<void ()> ClickHandler;

#define INITIAL_REPEAT_TIMEOUT 400
#define CONTINUOUS_REPEAT_TIMEOUT 85

class Button : public UIElement {
protected:
    SDL_Color m_color, m_highlightedColor;
    bool m_highlighted;
    bool m_clickedDown;
    bool m_justClicked;
    
    bool m_shouldRepeatClick; // Whether holding down a button repeats the click action
    int m_repeatCounter;
    
    ClickHandler m_clickHandler;
    
    void SetClicked();
    
public:
    Button(int x, int y, ClickHandler clickHandler, bool repeatClick = false);
    virtual ~Button() { }
    
    void ClickDown();
    void ClickUp();
    virtual void SetHighlight(bool highlight) { m_highlighted = highlight; }
    
    bool inBounds(int x, int y);
    
    virtual void Update(int delta) override;
};

