//
//  ImageButton.h
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#pragma once

#include "Button.h"

class ImageButton : public Button {
    
public:
    ImageButton(int x, int y, SDL_Surface *imageSurface, ClickHandler clickHandler, bool repeatClick = false);
    ~ImageButton();
};
