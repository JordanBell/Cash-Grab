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
    for (Button *b : m_Buttons) {
        b->Update(delta);
    }
}

void MenuScreen::Render()
{
    for (Button *b : m_Buttons) {
        b->Render();
    }
}

void MenuScreen::OnEvent(SDL_Event event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN ||
       event.type == SDL_MOUSEBUTTONUP)
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            int x = event.button.x;
            int y = event.button.y;
            
            for (Button *b : m_Buttons) {
                if (event.type == SDL_MOUSEBUTTONDOWN &&
                    b->inBounds(x, y))
                {
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        b->ClickDown();
                    }
                }
                else if (event.type == SDL_MOUSEBUTTONUP) {
                    b->SetHighlight(false);
                    b->ClickUp();
                }
            }
        }
    }
    
    if (event.type == SDL_MOUSEMOTION) {
        //Get the mouse offsets
        int x = event.button.x;
        int y = event.button.y;
        
        // Highlight button mouse is over
        for (Button *b : m_Buttons) {
            if (b->inBounds(x, y))
            {
                b->SetHighlight(true);
            }
            else {
                b->SetHighlight(false);
            }
        }
    }
}