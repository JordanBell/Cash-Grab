//
//  UIElement.h
//  Cash Grab
//
//  Created by Tristan Bell on 04/01/2015.
//  Copyright (c) 2015 Tristan Bell. All rights reserved.
//

#pragma once

#include "GameObject.h"

class UIElement : public GameObject {
    
public:
    UIElement(int x, int y);
    virtual ~UIElement() { }
    
    virtual void Render();
    
    /* Horizontally centers this element according to supplied width */
    void Center(int width);
    /* Centers according to width of another UIElement */
    void Center(UIElement *other);
    
    virtual int GetWidth();
    virtual int GetHeight();
};
