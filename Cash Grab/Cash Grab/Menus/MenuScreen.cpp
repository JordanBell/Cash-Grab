//
//  Menu.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "MenuScreen.h"

void MenuScreen::Update(int delta)
{
    SDL_Event event;
    
    if (SDL_PollEvent(&event)) {
        if( event.type == SDL_MOUSEBUTTONDOWN )
        {
            //If the left mouse button was pressed
            if( event.button.button == SDL_BUTTON_LEFT )
            {
                //Get the mouse offsets
                int x = event.button.x;
                int y = event.button.y;
                
                for (Button *b : m_Buttons) {
                    if (b->inBounds(x, y)) {
                        b->Click();
                    }
                }
            }
        }
    }
}

void MenuScreen::Render()
{
    for (Button *b : m_Buttons) {
        b->Render();
    }
}