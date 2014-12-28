//
//  Menu.h
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#pragma once

#include "MenuScreen.h"
#include <map>
#include <string>

using namespace std;

typedef enum {
    NEW_GAME,
    CONTINUE,
    QUIT,
    SETTINGS
} MenuName;

class Menu {
protected:
    MenuScreen* m_screen;
    
    void Init();
    
public:
    SDL_Rect m_Background;
    
    // Menu tree structure
    map<MenuName, Menu*> next;
    Menu* prev;
    
    Menu();
    Menu(Menu* previous);
    virtual ~Menu() { }
    
    virtual void Update(int delta);
    virtual void Render();
    
    void GoToScreen(MenuName screenName);
    void Back();
    
    virtual void OnEvent(SDL_Event event);
};