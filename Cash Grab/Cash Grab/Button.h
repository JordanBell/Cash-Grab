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

class Button : public GameObject {
protected:
    SDL_Color m_color;
    
public:
    Button(int x, int y, const char *text);
    virtual ~Button() { }
    
    virtual void Click() { printf("Clicked\n"); };
    
    bool inBounds(int x, int y);
    
    virtual void Render() override;
};

#endif /* defined(__Cash_Grab__Button__) */
