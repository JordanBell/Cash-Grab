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

StartMenu::StartMenu()
{
    m_screen = new StartMenuScreen(this);
    
    next[SETTINGS] = new SettingsMenu(this);
}