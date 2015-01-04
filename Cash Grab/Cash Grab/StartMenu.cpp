//
//  StartMenu.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "StartMenu.h"
#include "StartMenuScreen.h"
#include "SettingsMenu.h"

#include "StoreMenuScreen.h"

StartMenu::StartMenu()
{
    m_screen = new StartMenuScreen(this);
//    m_screen = new StoreMenuScreen(new Store(0, 0), this);
    
    next[SETTINGS] = new SettingsMenu(this);
}