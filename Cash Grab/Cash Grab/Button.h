//
//  Button.h
//  Cash Grab
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __Cash_Grab__Button__
#define __Cash_Grab__Button__

#include "Sprite.h"

class Button : public Sprite {
private:
    SDL_Rect bounds;
    
public:
    Button(int x, int y);
    
    void Clicked();
};

#endif /* defined(__Cash_Grab__Button__) */
