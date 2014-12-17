//
//  Button.h
//  Cash Grab
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __Cash_Grab__Button__
#define __Cash_Grab__Button__

#include "GameObject.h"
#include <functional>

typedef std::function<void ()> ClickHandler;

class Button : public GameObject {    
protected:
    SDL_Color m_color;
    
    ClickHandler m_clickHandler;
    
public:
    Button(int x, int y, ClickHandler clickHandler);
    virtual ~Button() { }
    
    void Click();
    
    bool inBounds(int x, int y);
    
    virtual void Render() override;
};

#endif /* defined(__Cash_Grab__Button__) */
