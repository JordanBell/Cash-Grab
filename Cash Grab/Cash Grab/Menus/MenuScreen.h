//
//  Menu.h
//  Cash Grab
//
//  Base class for menus.
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef Cash_Grab_MenuScreen_h
#define Cash_Grab_MenuScreen_h

#include <vector>
#include "Button.h"

class Menu;

class MenuScreen {
protected:
    Menu* m_ParentMenu;
    std::vector<Button*> m_Buttons;
    
public:
    MenuScreen(Menu* parent) : m_ParentMenu(parent) { }
    
    virtual ~MenuScreen()
    {
        for (Button *b : m_Buttons) {
            delete b;
        }
    }
    
    virtual void Update(int delta);
    
    virtual void Render();
    
    virtual void OnEvent(SDL_Event event);
};

#endif
