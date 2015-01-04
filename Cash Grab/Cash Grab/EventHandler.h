//
//  EventHandler.h
//  Cash Grab
//
//  Created by Tristan Bell on 22/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#pragma once

#include "SDL.h"

class EventHandler {
    
public:
    virtual ~EventHandler() { }
    
    virtual void OnEvent(SDL_Event event) = 0;
};
